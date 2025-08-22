#include "CLUpgradeForm.h"

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLTouch.h"
#include "CLPasswordForm.h"

#define	CLUpgradeForm_SubTitleTextPoint			1, 39
#define	CLUpgradeForm_SubTitleTextLength		19
#define	CLUpgradeForm_KeygenTextPoint			1, 159
#define	CLUpgradeForm_KeygenTextLength			19
#define	CLUpgradeForm_DINExtraButtonRectangle	91, 97, 220, 131

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

CLFormResult CLUpgradeForm_Open( unsigned short options )
{
	CLUpgradeForm	form;

	return form.Open( options );
}

// =============================================================================
// CLUpgradeForm [class]
// -----------------------------------------------------------------------------
CLUpgradeForm::CLUpgradeForm()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );

	m_DINExtraButtonRectangle.Set( CLUpgradeForm_DINExtraButtonRectangle );
}

CLFormResult CLUpgradeForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_KeygenPassword	= GeneratePassword( m_Password );

	// Inizializza i dati
	SetState( CLState_Initializing );
	SetKTSType( CLKTSType_EXTRA );
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
			// Extra Button
			if (m_DINExtraButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_DINExtraButtonRectangle );
				SetKTSType( CLKTSType_EXTRA );
			}
			else
			// Ok Button
			if (m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				char*	passwords[ 1 ];
				short	validPasswordIndex;
				
				passwords[ 0 ]	= m_Password;

				if (CLPasswordForm_CheckOpen( passwords, 1, 3, validPasswordIndex,
					CLLocalitation::GetText( CLTextId_UPGRADE ), CLFormOption_Default ) == CLFormResult_Ok)
				{
					if (Save( options ))
					{
						if (CLFormOption_CanExitAfterWrite( options ))
						{
							formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
							break;
						}
					}
				}
				RenderPage();
			}
			else
				WaitForTouchRelease();
		}
    }

	return formResult;
}

bool CLUpgradeForm::Save( unsigned short options )
{
	ComQueue_Status	writeEeprom_Status;
	byte			saveType_func;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
		CLLCDCommon::WriteDataPanel_DisplayWriting();

	// Salva temporaneamente i dati correnti
	saveType_func	= gRDEeprom.Type_func;

	// Imposta i nuovi dati
	gRDEeprom.Type_func	= m_KTSType;

	// Accoda la richiesta di WriteEeprom
	KTS_QueueWriteEepromRequest( offsetof( S_EEPROM, Type_func ),
		sizeof(gRDEeprom.Type_func),
		&writeEeprom_Status );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(writeEeprom_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (writeEeprom_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Rispristina valore precedente
		gRDEeprom.Type_func	= saveType_func;

		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
			CLLCDCommon::WriteDataPanel_DisplayError();

		return false;
	}

	if (saveType_func == CLKTSType_DEMO)
		gRDEeprom.Type_func	= CLKTSType_DEMO;

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();
	return true;
}

long CLUpgradeForm::GeneratePassword( char* password )
{
	unsigned long	keyGenUpgrade;
	unsigned long	passwUpgrade;
	unsigned int	temp;

	//keyGenUpgrade	= random1( 10000, 99999 );
    keyGenUpgrade = random_int ( 10000, 99999 );
	passwUpgrade	= (keyGenUpgrade * keyGenUpgrade +
		7 * keyGenUpgrade + 
		21) % 90000 + 10000;

	temp			= passwUpgrade / 10000;
	password[ 0 ]	= 48 + temp;
	passwUpgrade	= passwUpgrade - temp * 10000;

	temp			= passwUpgrade / 1000;
	password[ 1 ]	= 48 + temp;
	passwUpgrade	= passwUpgrade - temp * 1000;

	temp			= passwUpgrade / 100;
	password[ 2 ]	= 48 + temp;
	passwUpgrade	= passwUpgrade - temp * 100;

	temp			= passwUpgrade / 10;
	password[ 3 ]	= 48 + temp;
	passwUpgrade	= passwUpgrade - temp * 10;

	temp			= passwUpgrade;
	password[ 4 ]	= 48 + temp;

	return keyGenUpgrade;
}

void CLUpgradeForm::RenderPage()
{
	char	text[ 20 ];

	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Title
	RenderFormTitle( CLLocalitation::GetText( CLTextId_UPGRADE_ACTIVATION ),
		NULL );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Draw SubTitle
	CLGraphics::DrawText( CLUpgradeForm_SubTitleTextPoint, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
		RGBColor_Black, RGBColor_White,
		CLLocalitation::GetText( CLTextId_SELECT_KTS ), CLUpgradeForm_SubTitleTextLength );

	// Draw Keygen
	sprintf( text, "KEYGEN: %d", m_KeygenPassword );
	CLGraphics::DrawText( CLUpgradeForm_KeygenTextPoint, CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HAlign_Center,
		RGBColor_Black, RGBColor_White,
		text, CLUpgradeForm_KeygenTextLength );

	RenderButtons();
}

void CLUpgradeForm::RenderButtons()
{
	CLLCDCommon::DrawGenericButton( m_DINExtraButtonRectangle,
		(m_KTSType == CLKTSType_EXTRA ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
		"EXTRA" );
}

void CLUpgradeForm::SetKTSType( CLKTSType value )
{
	m_KTSType	= value;

	if (GetState() == CLState_Running)
		RenderButtons();
}
// -----------------------------------------------------------------------------
// CLVOCConfigForm [class]
// =============================================================================


