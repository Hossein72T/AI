#include "CLModBusConfigForm.h"

#include "CLKTS.h"
#include "CLImages.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLAccessory.h"

#define	CLModBusConfigForm_AddressLabel_Point			10, 119
#define	CLModBusConfigForm_AddressLabel_Length			10
#define	CLModBusConfigForm_AddressValue_Point			180, 119
#define	CLModBusConfigForm_AddressValue_Length			2
#define	CLModBusConfigForm_AddressUpButtonRectangle		242, 86, 281, 115
#define	CLModBusConfigForm_AddressDownButtonRectangle	242, 131, 281, 160
#define	CLModBusConfigForm_StatusLabel_Point			10, 60
#define	CLModBusConfigForm_StatusLabel_Length			20
#define	CLModBusConfigForm_StatusValue_Point			180, 60
#define	CLModBusConfigForm_StatusValue_Length			16
#define	CLModBusConfigForm_VersionLabel_Point			10, 34
#define	CLModBusConfigForm_VersionLabel_Length			20
#define	CLModBusConfigForm_VersionValue_Point			179, 34
#define	CLModBusConfigForm_VersionValue_Length			16

CLFormResult CLModBusConfigForm_Open( unsigned short options )
{
	CLModBusConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLModBusConfigForm [class]
// -----------------------------------------------------------------------------
CLModBusConfigForm::CLModBusConfigForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_AddressUpButtonRectangle.Set( CLModBusConfigForm_AddressUpButtonRectangle );
	m_AddressDownButtonRectangle.Set( CLModBusConfigForm_AddressDownButtonRectangle );

	m_Address_ProgressiveTouchUpDown.Set( 120, 10, 50, 8, 3, 1 );
}

CLFormResult CLModBusConfigForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetAddress( gRDEeprom.AddrUnit );
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
			// Up Button
			if (m_AddressUpButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_AddressUpButtonRectangle );

				m_Address_ProgressiveTouchUpDown.Reset();
				while (m_Address_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Address_ProgressiveTouchUpDown.CanIncrement())
						SetAddress( m_Address + 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_AddressUpButtonRectangle );
			}
			else
			// Down Button
			if (m_AddressDownButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton_Pressed( m_AddressDownButtonRectangle );

				m_Address_ProgressiveTouchUpDown.Reset();
				while (m_Address_ProgressiveTouchUpDown.InWhile())
				{
					if (m_Address_ProgressiveTouchUpDown.CanIncrement())
						SetAddress( m_Address - 1 );
				}

				CLLCDCommon::WaitButton_Unpressed( m_AddressDownButtonRectangle );
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLModBusConfigForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveAddrUnit;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveAddrUnit	= gRDEeprom.AddrUnit;

	// Imposta i nuovi dati
	gRDEeprom.AddrUnit	= m_Address;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, AddrUnit ),
		sizeof(gRDEeprom.AddrUnit),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.AddrUnit	= saveAddrUnit;

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

void CLModBusConfigForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_MODBUS_SETTINGS ),
		NULL );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Testo del tasto Ok
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display 'ADDRESS'
	CLGraphics::DrawText( CLModBusConfigForm_AddressLabel_Point, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, CLLocalitation::GetText( CLTextId_MODBUS_ADDRESS ), CLModBusConfigForm_AddressLabel_Length );

	// Display 'STATUS'
	CLGraphics::DrawText( CLModBusConfigForm_StatusLabel_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, CLLocalitation::GetText( CLTextId_MODBUS_STATUS ), CLModBusConfigForm_StatusLabel_Length );

	// Display 'VERSION'
	CLGraphics::DrawText( CLModBusConfigForm_VersionLabel_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, CLLocalitation::GetText( CLTextId_FIRMWARE_VERSION ), CLModBusConfigForm_VersionLabel_Length );

	RenderDynamicObjects();
}

void CLModBusConfigForm::RenderDynamicObjects()
{
	char	text[ 30 ];

	CLLCDCommon::DrawGenericButton( m_AddressUpButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &UpMonoImage );
	CLLCDCommon::DrawGenericButton( m_AddressDownButtonRectangle,
		GenericButtonStyle_Normal_UpDown, &DownMonoImage );

	// Display 'ADDRESS' Value
	sprintf( text, "%2d", m_Address );
	CLGraphics::DrawText( CLModBusConfigForm_AddressValue_Point, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, text, CLModBusConfigForm_AddressValue_Length );

	// Display 'STATUS' Value
	if (Accessory_IsPresent( ACC_EEP_MBUS ))
		sprintf( text, "%s", CLLocalitation::GetText( CLTextId_CONNECTED ) );
	else
		sprintf( text, "%s", CLLocalitation::GetText( CLTextId_DISCONNECTED ) );

	CLGraphics::DrawText( CLModBusConfigForm_StatusValue_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, text, CLModBusConfigForm_StatusValue_Length );

	// Display 'VERSION' Value
	sprintf( text, "%d.%02d", gRDEeprom.swVer_ModBus[ 0 ], gRDEeprom.swVer_ModBus[ 1 ] );
	CLGraphics::DrawText( CLModBusConfigForm_VersionValue_Point, CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_HAlign_Left,
		RGBColor_Black, RGBColor_White, text, CLModBusConfigForm_VersionValue_Length );
}

void CLModBusConfigForm::SetAddress( short value )
{
	if (value < 1)
		value	= 63;
	else
	if (value > 63)
		value	= 1;

	m_Address	= value;
	if (GetState() == CLState_Running)
		RenderDynamicObjects();
}
// -----------------------------------------------------------------------------
// CLCO2ConfigForm [class]
// =============================================================================

