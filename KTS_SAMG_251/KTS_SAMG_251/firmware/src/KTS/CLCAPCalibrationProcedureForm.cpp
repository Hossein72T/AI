#include "CLCAPCalibrationProcedureForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLVentilationControl.h"
#include "CLFunction.h"
#include "CLAccessory.h"

#define CLCAPCalibrationProcedureForm_CalibrationDataRectangle				12, 31, 306, 173
#define CLCAPCalibrationProcedureForm_ButtonsRectangle						0, 182, 319, 239

// Ready state
#define CLCAPCalibrationProcedureForm_Ready_MessageRectangle						12, 31, 306, 173
#define CLCAPCalibrationProcedureForm_Ready_ResetButtonRectangle					159, 190, 260, 229

// Measuring state
#define CLCAPCalibrationProcedureForm_Measuring_MessageRectangle					12, 31, 306, 104
#define CLCAPCalibrationProcedureForm_Measuring_PressureRectangle					12, 107, 306, 147
#define CLCAPCalibrationProcedureForm_Measuring_MeasurePressure_Caption_Rectangle	35, 112, 283, 125 // 18, 112, 300, 125
#define CLCAPCalibrationProcedureForm_Measuring_MeasurePressure_Value_Rectangle		18, 127, 300, 144
#define CLCAPCalibrationProcedureForm_Measuring_TimeRectangle						12, 150, 306, 173
#define CLCAPCalibrationProcedureForm_Measuring_CancelButtonRectangle				0, 190, 150, 229

// ConfirmMeasure state
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_MessageRectangle				12, 31, 306, 104
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_PressureRectangle				12, 107, 306, 171
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_CaptionPoint			18, 117
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_CaptionLength			35
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_ValuePoint			18, 138
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_ValueLength			17
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_YesButtonRectangle				0, 190, 70, 229
#define CLCAPCalibrationProcedureForm_ConfirmMeasure_NoButtonRectangle				80, 190, 150, 229

// Completed or Error state
#define CLCAPCalibrationProcedureForm_CompletedOrError_MessageRectangle		12, 31, 306, 167

const unsigned long CAPCalibrationMaxTime = 2 * 60 * 1000;
const unsigned long DataDebug_RequestMilliseconds = 2500;

CLFormResult CLCAPCalibrationProcedureForm_Open( unsigned short options )
{
	CLCAPCalibrationProcedureForm	form;

	return form.Open( options );
}

void CLCAPCalibrationProcedureForm_ResponseDebugDataCallback( byte* rxBuffer, void* userData )
{
	CLCAPCalibrationProcedureForm*	capCalibrationProcedureForm	= (CLCAPCalibrationProcedureForm*) userData;

	if (capCalibrationProcedureForm == NULL)
		return;
    
    if(Accessory_IsPresent( ACC_EEP_FLW1 )) // check if CAPS is present
        capCalibrationProcedureForm->SetMeasurePressure( (unsigned short)
            (((int) rxBuffer[ IRSD_MEASUR_PA_CAPS_HI ] << 8) +  rxBuffer[IRSD_MEASUR_PA_CAPS_LO]) );
    
    if(Accessory_IsPresent( ACC_EEP_PCAP )) // check if CAP is present
        capCalibrationProcedureForm->SetMeasurePressure( (unsigned short)
            (((int) rxBuffer[ IRSD_MEASUR_PA_HI ] << 8) +  rxBuffer[IRSD_MEASUR_PA_LO]) );
    
    capCalibrationProcedureForm->SetMeasurePressure1( (unsigned short)
		(((int) rxBuffer[ IRSD_MEASUR_PA_CAPR_HI ] << 8) +  rxBuffer[IRSD_MEASUR_PA_CAPR_LO]) );
}

// =============================================================================
// CLCAPCalibrationProcedureForm [class]
// -----------------------------------------------------------------------------
CLCAPCalibrationProcedureForm::CLCAPCalibrationProcedureForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
	m_CancelButtonRectangle.Set( CLCAPCalibrationProcedureForm_Measuring_CancelButtonRectangle );
	m_YesButtonRectangle.Set( CLCAPCalibrationProcedureForm_ConfirmMeasure_YesButtonRectangle );
	m_NoButtonRectangle.Set( CLCAPCalibrationProcedureForm_ConfirmMeasure_NoButtonRectangle );
	m_ResetButtonRectangle.Set( CLCAPCalibrationProcedureForm_Ready_ResetButtonRectangle );
}

CLFormResult CLCAPCalibrationProcedureForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;
	unsigned long	dataDebugRequestMilliseconds	= 0;
	int				dataDebugRequestQueueIndex		= -1;
	ComQueue_Status	dataDebugRequestStatus;
    ComQueue_Status	writeEeprom_Status;
    unsigned short Old_CAF3;
    byte Old_Idx_Motor;

	m_Options	= options;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetCalibrationState( CLCalibrationState_Ready, CLCalibrationSubState_None );
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		Render_DinamycObject();

		if (m_CalibrationState == CLCalibrationState_Measuring)
		{
			bool	expiredCalibrationTime = CLKTS::MillisDiff( m_CalibrationStartMillis, millis() ) >= CAPCalibrationMaxTime;
			
			// Se esiste una richiesta pendente, controlla se è ancora in esecuzione
			if (dataDebugRequestQueueIndex != -1)
			{
				if (!COM_REQUEST_ISRUNNING( dataDebugRequestStatus ))
					dataDebugRequestQueueIndex	= -1;
			}

			// Se scade il tempo di attesa, accoda la richiesta di dati di debug
			if (!expiredCalibrationTime
				&& (millis() - dataDebugRequestMilliseconds >= DataDebug_RequestMilliseconds
				|| millis() < dataDebugRequestMilliseconds))
			{
				// Se non e' gia' accodata, accoda la richiesta di Debug Data
				if (dataDebugRequestQueueIndex == -1)
				{
					dataDebugRequestQueueIndex	= ComQueue_AddDataDebugRequest( &dataDebugRequestStatus,
						CLCAPCalibrationProcedureForm_ResponseDebugDataCallback );
					if (dataDebugRequestQueueIndex != -1)
						gComQueueRequests[ dataDebugRequestQueueIndex ].UserData	= this;
				}

				dataDebugRequestMilliseconds	= millis();
			}

			if (expiredCalibrationTime
				&& dataDebugRequestQueueIndex == -1)
			{
				MeasureEnd();
                Function_SetEnabled( ENAB_FSC, false );
                Function_SetEnabled( ENAB_CAP, true );
                gRDEeprom.Set_StepMotorsFSC_CAF[3] = Old_CAF3;
                gRDEeprom.sel_idxStepMotors = Old_Idx_Motor;

                // Accoda la richiesta di WriteEeprom
                KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
                    sizeof(gRDEeprom.Enab_Fuction),
                    &writeEeprom_Status );
                // Accoda la richiesta di WriteEeprom
                KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_StepMotorsFSC_CAF[3] ),
                    sizeof(gRDEeprom.Enab_Fuction),
                    &writeEeprom_Status );
                // Accoda la richiesta di WriteEeprom
                KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
                    sizeof(gRDEeprom.Enab_Fuction),
                    &writeEeprom_Status );
				if (m_MeasurePressureCount == 0)
					SetCalibrationState( CLCalibrationState_Error, CLCalibrationSubState_ErrorWritingData );
				else
					SetCalibrationState( CLCalibrationState_ConfirmMeasure, CLCalibrationSubState_Ok );
			}
		}

		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			if (m_CalibrationState == CLCalibrationState_Ready)
			{
				// Home Button
				if (!(m_Options & CLFormOption_HideButton_Home)
					&& m_HomeButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_HomeButtonRectangle );
					formResult	= CLFormResult_Home;
					break;
				}
				else
				// Back Button
				if (!(m_Options & CLFormOption_HideButton_Back)
					&& m_BackButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_BackButtonRectangle );
					formResult	= CLFormResult_Back;
					break;
				}
				else
				// Ok Button
				if (m_OkButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_OkButtonRectangle );
					if (!MeasureStart())
						SetCalibrationState( CLCalibrationState_Error, CLCalibrationSubState_ErrorWritingData );
					else
                    {
						SetCalibrationState( CLCalibrationState_Measuring, CLCalibrationSubState_None );
                        //Imposta il nuovo valore
                        Function_SetEnabled( ENAB_FSC, true );
                        Function_SetEnabled( ENAB_CAP, false );
                        Old_CAF3 = gRDEeprom.Set_StepMotorsFSC_CAF[3];
                        Old_Idx_Motor = gRDEeprom.sel_idxStepMotors;
                        gRDEeprom.sel_idxStepMotors = gRDEeprom.sel_idxStepMotors | 3;
                        gRDEeprom.Set_StepMotorsFSC_CAF[3] = 0x3E8;

                        // Accoda la richiesta di WriteEeprom
                        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
                            sizeof(gRDEeprom.Enab_Fuction),
                            &writeEeprom_Status );
                        // Accoda la richiesta di WriteEeprom
                        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_StepMotorsFSC_CAF[3] ),
                            sizeof(gRDEeprom.Enab_Fuction),
                            &writeEeprom_Status );
                        // Accoda la richiesta di WriteEeprom
                        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
                            sizeof(gRDEeprom.Enab_Fuction),
                            &writeEeprom_Status );
                    }
				}
				else
				// RESET Button
				if ((m_Options & CLFormOption_AdminMode) && m_ResetButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_ResetButtonRectangle );
					
					if (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNo, CLMessageBoxGravity_Question,
						"QUESTION", "DO YOU WANT TO RESET MAX PRESSURE WITH FACTORY VALUE?") == CLMessageBoxResult_Yes)
					{
						CLLCDCommon::WriteDataPanel_DisplayWriting();
						if (CalibrationSave( 0 , 0))
							CLLCDCommon::WriteDataPanel_DisplaySuccess();
						else
							CLLCDCommon::WriteDataPanel_DisplayError();
					}
					RenderPage();
				}
				else

					WaitForTouchRelease();
			}
			else
			if (m_CalibrationState == CLCalibrationState_Measuring)
			{
				// Cancel Button
				if (m_CancelButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_CancelButtonRectangle );
					MeasureEnd();
					SetCalibrationState( CLCalibrationState_Ready, CLCalibrationSubState_None );
                    Function_SetEnabled( ENAB_FSC, false );
                    Function_SetEnabled( ENAB_CAP, true );
                    gRDEeprom.Set_StepMotorsFSC_CAF[3] = Old_CAF3;
                    gRDEeprom.sel_idxStepMotors = Old_Idx_Motor;

                    // Accoda la richiesta di WriteEeprom
                    KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Enab_Fuction ),
                        sizeof(gRDEeprom.Enab_Fuction),
                        &writeEeprom_Status );
                    // Accoda la richiesta di WriteEeprom
                    KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Set_StepMotorsFSC_CAF[3] ),
                        sizeof(gRDEeprom.Enab_Fuction),
                        &writeEeprom_Status );
                    // Accoda la richiesta di WriteEeprom
                    KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, sel_idxStepMotors ),
                        sizeof(gRDEeprom.Enab_Fuction),
                        &writeEeprom_Status );
				}
				else
					WaitForTouchRelease();
			}
			else
			if (m_CalibrationState == CLCalibrationState_ConfirmMeasure)
			{
				// Yes Button
				if (m_YesButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_YesButtonRectangle );
					if (CalibrationSave( m_MeasurePressure , m_MeasurePressure1))
						SetCalibrationState( CLCalibrationState_Completed, CLCalibrationSubState_Ok );
					else
						SetCalibrationState( CLCalibrationState_Error, CLCalibrationSubState_ErrorWritingData );
				}
				else
				// No Button
				if (m_NoButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_NoButtonRectangle );
                    if (CLMessageBoxForm::Open( CLMessageBoxButtons_YesNo, CLMessageBoxGravity_Question,
						"QUESTION", "DO YOU WANT TO SKIP SAVING CALIBRATION DATA?") == CLMessageBoxResult_Yes)
                    {
                        SetCalibrationState( CLCalibrationState_Ready, CLCalibrationSubState_None );
                    }
                    else
                    {
                        SetCalibrationState( CLCalibrationState_ConfirmMeasure, CLCalibrationSubState_None );
                        //RenderPage();
                    }
				}
				else
					WaitForTouchRelease();
			}
			else
			if (m_CalibrationState == CLCalibrationState_Error
				|| m_CalibrationState == CLCalibrationState_Completed)
			{
				// Ok Button
				if (m_OkButtonRectangle.Contains( touchX, touchY ))
				{
					CLLCDCommon::WaitButton( m_OkButtonRectangle );

					if (m_CalibrationState == CLCalibrationState_Completed)
					{
						formResult	= CLFormResult_Ok;
						break;
					}

					SetCalibrationState( CLCalibrationState_Ready, CLCalibrationSubState_None );
				}
				else
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

void CLCAPCalibrationProcedureForm::SetCalibrationState( CLCalibrationState state,
	CLCalibrationSubState subState )
{
	m_CalibrationState		= state;
	m_CalibrationSubState	= subState;

	if (GetState() == CLState_Running)
	{
		// Clear CalibrationData area
		CLGraphics::DrawBox( CLRectangle( CLCAPCalibrationProcedureForm_CalibrationDataRectangle ), CLGraphicStyleOptions_Default,
			RGBColor_Black );
		// Clear Buttons area
		CLGraphics::DrawBox( CLRectangle( CLCAPCalibrationProcedureForm_ButtonsRectangle ), CLGraphicStyleOptions_Default,
			RGBColor_Black );
	}

	Render_StaticObject();
	Render_DinamycObject();
}

void CLCAPCalibrationProcedureForm::RenderPage()
{
	if (GetState() != CLState_Running)
		return;

	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_CAP_CALIBRATION_PROCEDURE ),
		NULL );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	Render_StaticObject();
	Render_DinamycObject();
}

void CLCAPCalibrationProcedureForm::Render_StaticObject()
{
	char	text[ 20 ];

	if (GetState() != CLState_Running)
		return;

	switch (m_CalibrationState)
	{
		case CLCalibrationState_Ready:
			// Home Button
			if (!(m_Options & CLFormOption_HideButton_Home))
				CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

			// Back Button
			if (!(m_Options & CLFormOption_HideButton_Back))
				CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
					GenericButtonStyle_Normal_BigFont );

			// Ok Button
			CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
				GenericButtonStyle_Normal_BigFont );

			if (m_Options & CLFormOption_AdminMode)
			{
				// Ok Button
				CLLCDCommon::DrawGenericButton( m_ResetButtonRectangle,
					GenericButtonStyle_Normal_BigFont, "RESET" );
			}


			// Testo di inizio calibrazione
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_Ready_MessageRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				(byte) 1, RGBColor_White, CLLocalitation::GetText( CLTextId_CAP_CALIBRATION_START_MESSAGE ) );
			break;

		case CLCalibrationState_Measuring:
			// Display Cancel Button
			CLLCDCommon::DrawGenericButton( m_CancelButtonRectangle, GenericButtonStyle_Normal_BigFont, CLLocalitation::GetText( CLTextId_CANCEL ) );

			// Testo calibrazione in corso
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_Measuring_MessageRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				(byte) 1, RGBColor_White, CLLocalitation::GetText( CLTextId_CAP_CALIBRATION_RUNNING_MESSAGE ) );

			// Box Pressure
			CLGraphics::DrawBox( CLRectangle( CLCAPCalibrationProcedureForm_Measuring_PressureRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black,
				(byte) 1, RGBColor_White );
            
			break;

		case CLCalibrationState_ConfirmMeasure:
			// Testo Conferma dati
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_ConfirmMeasure_MessageRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				(byte) 1, RGBColor_White, CLLocalitation::GetText( CLTextId_CAP_CALIBRATION_CONFIRMDATA_MESSAGE ) );

			// Box Pressure
			CLGraphics::DrawBox( CLRectangle( CLCAPCalibrationProcedureForm_ConfirmMeasure_PressureRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black,
				(byte) 1, RGBColor_White );

			// Render Measure Pressure
			CLGraphics::DrawText( CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_CaptionPoint, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_MEASURE_PRESSURE ), CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_CaptionLength );
            
            if (Accessory_IsPresent( ACC_EEP_FLW1 ) && Accessory_IsPresent( ACC_EEP_FLW2 )) // CAPS and CAPR
                {
                    CLGraphics::DrawText( 25,118, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
                    CLGraphics::DrawText( 285,118, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );
                    sprintf( text, "%u (%s) %u (%s)", m_MeasurePressure, CLFixedText_PA , m_MeasurePressure1, CLFixedText_PA);
                }
            else
                sprintf( text, "%u (%s)", m_MeasurePressure, CLFixedText_PA );
            
			CLGraphics::DrawText( CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_ValuePoint, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				text, CLCAPCalibrationProcedureForm_ConfirmMeasure_Pressure_ValueLength );

			// Display Yes Button
			CLLCDCommon::DrawGenericButton( m_YesButtonRectangle, GenericButtonStyle_Normal_BigFont, CLLocalitation::GetText( CLTextId_YES ) );

			// Display No Button
			CLLCDCommon::DrawGenericButton( m_NoButtonRectangle, GenericButtonStyle_Normal_BigFont, CLLocalitation::GetText( CLTextId_NO ) );

			break;

		case CLCalibrationState_Completed:
		case CLCalibrationState_Error:
		{
			char*	statusText;

			switch (m_CalibrationSubState)
			{
				case CLCalibrationSubState_Ok:
					statusText	= (char*) CLLocalitation::GetText( CLTextId_WRITING_DATA_COMPLETED );
					break;

				case CLCalibrationSubState_ErrorWritingData:
					statusText	= (char*) CLLocalitation::GetText( CLTextId_WRITING_DATA_ERROR );
					break;

				default:
					statusText	= NULL;
					break;
			}

			// Testo Status
			if (statusText != NULL)
			{
				CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_CompletedOrError_MessageRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
					RGBColor_Black, (m_CalibrationSubState == CLCalibrationSubState_Ok ? RGBColor_White : RGBColor_Red),
					(byte) 1, RGBColor_White, statusText );
			}

			// Ok Button
			CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
				GenericButtonStyle_Normal_BigFont );
			break;
		}
	}
}

void CLCAPCalibrationProcedureForm::Render_DinamycObject()
{
	if (GetState() != CLState_Running)
		return;

	switch (m_CalibrationState)
	{
		case CLCalibrationState_Measuring:
		{
			char	textTemp[ 20 ];
			char	text[ 50 ];

			// Time (MM:SS / MM:SS)
			CLKTS::MillisToText( textTemp, CLKTS::MillisDiff( m_CalibrationStartMillis, millis() ), false );
			strcpy( text,  textTemp );
			strcat( text, " / " );
			CLKTS::MillisToText( textTemp, CAPCalibrationMaxTime, false );
			strcat( text,  textTemp );
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_Measuring_TimeRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine,
				RGBColor_Black, RGBColor_White,
				(byte) 1, RGBColor_White, text );

			// Measure Pressure
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_Measuring_MeasurePressure_Caption_Rectangle ), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_MEASURE_PRESSURE ) );
            if (Accessory_IsPresent( ACC_EEP_FLW1 ) && Accessory_IsPresent( ACC_EEP_FLW2 )) // CAPS and CAPR
                {
                    CLGraphics::DrawText( 25,112, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
                        RGBColor_Black, RGBColor_White,
                        "S", 1 );
                    CLGraphics::DrawText( 285,112, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Small,
                        RGBColor_Black, RGBColor_White,
                        "R", 1 );
                    sprintf( text, "%u (%s) %u (%s)", m_MeasurePressure, CLFixedText_PA , m_MeasurePressure1, CLFixedText_PA);
                }
            else
                sprintf( text, "%u (%s)", m_MeasurePressure, CLFixedText_PA );
			CLGraphics::DrawBoxWithText( CLRectangle( CLCAPCalibrationProcedureForm_Measuring_MeasurePressure_Value_Rectangle ), CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel,
				RGBColor_Black, RGBColor_White,
				text );

			break;
		}
	}
}

bool CLCAPCalibrationProcedureForm::CalibrationSave( unsigned short value , unsigned short value1)
{
	ComQueue_Status	writeEeprom_Status;
	unsigned short	saveCalibra_CAP; // CAP or CAPR
    unsigned short	saveCalibra_CAP1; // CAPS

	// Salva temporaneamente i dati prima del salvataggio
	saveCalibra_CAP	= gRDEeprom.calibra_CAP;
    if(Accessory_IsPresent( ACC_EEP_FLW2 )) // check if CAPR is present)
        saveCalibra_CAP1	= gRDEeprom.calibra_CAP1;
	//Imposta i nuovi dati
	gRDEeprom.calibra_CAP	= value;
    if(Accessory_IsPresent( ACC_EEP_FLW2 )) // check if CAPR is present)
        gRDEeprom.calibra_CAP1	= value1;
	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, calibra_CAP ),
		sizeof(gRDEeprom.calibra_CAP),
		&writeEeprom_Status );
    if(Accessory_IsPresent( ACC_EEP_FLW2 )) // check if CAPR is present)
        KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, calibra_CAP1 ),
		sizeof(gRDEeprom.calibra_CAP1),
		&writeEeprom_Status );
    
	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.calibra_CAP	= saveCalibra_CAP;
        if(Accessory_IsPresent( ACC_EEP_FLW2 )) // check if CAPR is present)
            gRDEeprom.calibra_CAP1	= saveCalibra_CAP1;

		return false;
	}

	return true;
}

bool CLCAPCalibrationProcedureForm::MeasureStart()
{
	unsigned short stepMotors[ sizeof(gRDEeprom.Set_StepMotors_CAP) / sizeof(unsigned short) ];

	if (m_CalibrationState != CLCalibrationState_Ready)
		return false;

	m_CalibrationStartMillis	= millis();
	m_MeasurePressureCount		= 0;
	m_MeasurePressure			= 0;
    m_MeasurePressure1			= 0;

	// Salva i dati correnti
	m_SaveVentilationControl	= VentilationControl_Get();
	m_SaveSpeedMode				= SpeedMode_GetType();
	m_SaveStepMotorCAP_2		= SpeedMode_Speed_GetValue( CLVentilationControl_CAP, 2 );
	m_SaveIdxStepMotors			= SpeedMode_Speed_GetIndex();
	m_SaveCalibra_CAP			= gRDEeprom.calibra_CAP;
    m_SaveCalibra_CAP1			= gRDEeprom.calibra_CAP1;

	SpeedMode_Speed_GetValues( CLVentilationControl_CAP, stepMotors );
	stepMotors[ 2 ]	= CLKTS::Pressure_GetMaxCalculated();

	// Imposta Three Speed Mode, con la terza velocità sul massimo e seleziono la terza velocità
	if (!CalibrationSave( 0 , 0))
		return false;

	if (!SpeedMode_Speed_Write( CLVentilationControl_CAP, CLSpeedModeType_ThreeSpeed, stepMotors, 2 ))
	{
		CalibrationSave( m_SaveCalibra_CAP , m_SaveCalibra_CAP1);
		return false;
	}

	if (!VentilationControl_Write( CLVentilationControl_CAP ))
	{
		stepMotors[ 2 ]	= m_SaveStepMotorCAP_2;
		SpeedMode_Speed_Write( m_SaveVentilationControl, m_SaveSpeedMode, stepMotors, m_SaveIdxStepMotors );
		CalibrationSave( m_SaveCalibra_CAP , m_SaveCalibra_CAP1);
		return false;
	}

	return true;
}

void CLCAPCalibrationProcedureForm::MeasureEnd()
{
	unsigned short stepMotors_CAP[ sizeof(gRDEeprom.Set_StepMotors_CAP) / sizeof(unsigned short) ];

	if (m_CalibrationState != CLCalibrationState_Measuring)
		return;

	SpeedMode_Speed_GetValues( CLVentilationControl_CAP, stepMotors_CAP );
	stepMotors_CAP[ 2 ]	= m_SaveStepMotorCAP_2;

	// Ripristina Three Speed Mode, con la terza velocità sul massimo e seleziono la terza velocità
	SpeedMode_Speed_Write( CLVentilationControl_CAP, m_SaveSpeedMode, stepMotors_CAP, m_SaveIdxStepMotors );
	VentilationControl_Write( m_SaveVentilationControl );
	CalibrationSave( m_SaveCalibra_CAP , m_SaveCalibra_CAP1);
}

void CLCAPCalibrationProcedureForm::SetMeasurePressure( unsigned short value ) // CAP or CAPS
{
	m_MeasurePressure	= value;
	m_MeasurePressureCount++;
}

void CLCAPCalibrationProcedureForm::SetMeasurePressure1( unsigned short value ) // CAPR
{
	m_MeasurePressure1	= value;
	m_MeasurePressureCount++;
}
// -----------------------------------------------------------------------------
// CLCAPCalibrationProcedureForm [class]
// =============================================================================


