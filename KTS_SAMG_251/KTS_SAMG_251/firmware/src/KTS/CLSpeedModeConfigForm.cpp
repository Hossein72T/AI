#include "CLSpeedModeConfigForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLFunction.h"
#include "CLTouch.h"
#include "CLSelectionSpeedForm.h"
#include "CLSelectionFranceTxClassForm.h"
#include "CLFranceTX.h"
#include "CLVentilationControl.h"
#include "CLSelectionAirFlowSpeed_ThreeSpeedForm.h"

#ifdef FRANCETX_ENABLED
#define CLSpeedModeConfigForm_ThreeSpeedButtonRectangle	47, 32, 266, 66
#define CLSpeedModeConfigForm_SteplessButtonRectangle		47, 80, 266, 114
#define CLSpeedModeConfigForm_FranceTxButtonRectangle		47, 130, 266, 164
#else
#define CLSpeedModeConfigForm_ThreeSpeedButtonRectangle	47, 49, 266, 83
#define CLSpeedModeConfigForm_SteplessButtonRectangle		47, 113, 266, 147
#endif

CLFormResult CLSpeedModeConfigForm_Open( unsigned short options )
{
	CLSpeedModeConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLSpeedModeConfigForm [class]
// -----------------------------------------------------------------------------
CLSpeedModeConfigForm::CLSpeedModeConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	#ifdef FRANCETX_ENABLED
	m_ThreeSpeedButtonRectangle.Set( CLSpeedModeConfigForm_ThreeSpeedButtonRectangle );
	m_SteplessButtonRectangle.Set( CLSpeedModeConfigForm_SteplessButtonRectangle );
	m_FranceTxButtonRectangle.Set( CLSpeedModeConfigForm_FranceTxButtonRectangle );
	#else
	m_ThreeSpeedButtonRectangle.Set( CLSpeedModeConfigForm_ThreeSpeedButtonRectangle );
	m_SteplessButtonRectangle.Set( CLSpeedModeConfigForm_SteplessButtonRectangle );
	#endif
}

CLFormResult CLSpeedModeConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetSpeedModeType( SpeedMode_GetType() );
	SetState( CLState_Running );

	// Visualizza il form
	RenderPage();

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
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

				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage();
			}
			else
			// ThreeSpeed Button
			if (m_ThreeSpeedButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_ThreeSpeedButtonRectangle );
				SetSpeedModeType( CLSpeedModeType_ThreeSpeed );
			}
			else
			// Stepless Button
			if (m_SteplessButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_SteplessButtonRectangle );
				SetSpeedModeType( CLSpeedModeType_Stepless );
			}
			#ifdef FRANCETX_ENABLED
			else
			// FranceTx Button
			if (m_FranceTxButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_FranceTxButtonRectangle );
				SetSpeedModeType( CLSpeedModeType_FranceTx );
			}
			#endif
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLSpeedModeConfigForm::Save( unsigned short options )
{
	switch (m_SpeedMode)
	{
		case CLSpeedModeType_ThreeSpeed:
		{
			unsigned short	values[ 3 ];

			// Preleva i dati correnti
			CLKTS::Write_GetCurrentStepMotors( VentilationControl_Get(), values, 0, 2 );

			if (CLSelectionAirFlowSpeed_ThreeSpeedForm_Open( CLFormOption_Default,
				VentilationControl_Get(), values ) != CLFormResult_Ok)
			{
				return false;
			}

			// Visualizza il messaggio di scrittura in corso
			if (CLFormOption_CanShowWriteMessage_Starting( options ))
				CLLCDCommon::WriteDataPanel_DisplayWriting();

			if (!CLKTS::WriteThreeSpeed( VentilationControl_Get(), values, 0 ))
			{
				// Visualizza il messaggio di errore
				if (CLFormOption_CanShowWriteMessage_Error( options ))
					CLLCDCommon::WriteDataPanel_DisplayError();

				return false;
			}

			// Visualizza il messaggio di ok
			if (CLFormOption_CanShowWriteMessage_Success( options ))
				CLLCDCommon::WriteDataPanel_DisplaySuccess();

			return true;
		}

		case CLSpeedModeType_Stepless:
			// Visualizza il messaggio di scrittura in corso
			if (CLFormOption_CanShowWriteMessage_Starting( options ))
				CLLCDCommon::WriteDataPanel_DisplayWriting();

			if (!CLKTS::WriteStepless( VentilationControl_Get(), SpeedMode_Stepless_GetMinValue( VentilationControl_Get() ) ))
			{
				// Visualizza il messaggio di errore
				if (CLFormOption_CanShowWriteMessage_Error( options ))
					CLLCDCommon::WriteDataPanel_DisplayError();

				return false;
			}

			// Visualizza il messaggio di ok
			if (CLFormOption_CanShowWriteMessage_Success( options ))
				CLLCDCommon::WriteDataPanel_DisplaySuccess();

			return true;

#ifdef FRANCETX_ENABLED
		case CLSpeedModeType_FranceTx:
		{
			CLFormResult	selectionFranceTxClassFormResult;
			byte			classIndex;

			// Impostiamo di default T2
			classIndex		= 0;

			selectionFranceTxClassFormResult	= CLSelectionFranceTxClassForm_Open(
				CLLocalitation::GetText( CLTextId_SELECT_SPEED_MODE ),
				CLLocalitation::GetText( CLTextId_SELECT_FRANCE_CLASSTX ),
				classIndex );

			if (selectionFranceTxClassFormResult != CLFormResult_Ok)
				return false;

			// Visualizza il messaggio di scrittura in corso
			if (CLFormOption_CanShowWriteMessage_Starting( options ))
				CLLCDCommon::WriteDataPanel_DisplayWriting();

			if (!CLKTS::WriteFranceTX( classIndex ))
			{
				// Visualizza il messaggio di errore
				if (CLFormOption_CanShowWriteMessage_Error( options ))
					CLLCDCommon::WriteDataPanel_DisplayError();

				return false;
			}

			// Visualizza il messaggio di ok
			if (CLFormOption_CanShowWriteMessage_Success( options ))
				CLLCDCommon::WriteDataPanel_DisplaySuccess();

			return true;
		}
#endif
	}

	return false;
}

void CLSpeedModeConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SELECT_SPEED_MODE ), NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	RenderAirFlowTypeButtons();
}

void CLSpeedModeConfigForm::RenderAirFlowTypeButtons()
{
	CLLCDCommon::DrawGenericButton( m_ThreeSpeedButtonRectangle,
		(m_SpeedMode == CLSpeedModeType_ThreeSpeed ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		CLLocalitation::GetText( CLTextId_THREE_SPEED ) );
	CLLCDCommon::DrawGenericButton( m_SteplessButtonRectangle,
		(m_SpeedMode == CLSpeedModeType_Stepless ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		CLLocalitation::GetText( CLTextId_STEPLESS ) );

	#ifdef FRANCETX_ENABLED
	CLLCDCommon::DrawGenericButton( m_FranceTxButtonRectangle,
		(m_SpeedMode == CLSpeedModeType_FranceTx ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		CLLocalitation::GetText( CLTextId_FRANCE_CLASSTX ) );
	#endif
}

void CLSpeedModeConfigForm::SetSpeedModeType( CLSpeedModeType value )
{
	m_SpeedMode	= value;
	
	if (GetState() == CLState_Running)
		RenderAirFlowTypeButtons();
}
// -----------------------------------------------------------------------------
// CLSpeedModeConfigForm [class]
// =============================================================================

