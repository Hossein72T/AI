#include "CLTestUnitForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"
#include "CLMessageBoxForm.h"
#include "RDProtocol.h"
#include "CLCommunicationManager.h"

#define	CLTestForm_BackButtonRectangle	2, 190, 72, 229
#define	CLTestForm_StartTestRectangle	15, 35, 304, 67
#define	CLTestForm_StatusRectangle		15, 76, 304, 163
#define	CLTestForm_StatusTextRectangle	18, 119, 301, 156
#define	CLTestForm_StatusLabelPoint		18, 91
#define	CLTestForm_StatusLabelLength	17

#define CLTestForm_SendMessagePanelRectangle 15, 85, 304, 144

CLFormResult CLTestUnitForm_Open( unsigned short options )
{
	CLTestUnitForm	form;

	return form.Open( options );
}

// =============================================================================
// CLTestUnitForm [class]
// -----------------------------------------------------------------------------
CLTestUnitForm::CLTestUnitForm()
{
	m_BackButtonRectangle.Set( CLTestForm_BackButtonRectangle );
	m_StartTestButtonRectangle.Set( CLTestForm_StartTestRectangle );
}

CLFormResult CLTestUnitForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	RenderPage();

	while (true)
	{
		// Processa le funzionalitï¿½ del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage();
		
		CLKTS::Pir_Process();
		
		RenderData();

		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Back Button
			if (m_BackButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			else
			// Home Button
			if (Form_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( Form_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// StartTest Button
			if (m_StartTestButtonRectangle.Contains( touchX, touchY ) &&
				gKTSGlobal.DisableTX != 'D')
			{
				CLLCDCommon::WaitButton( m_StartTestButtonRectangle );
				
				SendTestMessage( options );
				RenderPage();
			}
		}
    }

	return formResult;
}

void CLTestUnitForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw Main Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 239 ),
		GenericForm_Data_Style );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );
		
	// Display Title
	RenderFormTitle( "TEST UNIT",
		NULL );

	CLLCDCommon::DrawGenericButton( m_StartTestButtonRectangle,
		(gKTSGlobal.DisableTX == 'D' ? GenericButtonStyle_On_BigFont : GenericButtonStyle_Off_BigFont),
		(gKTSGlobal.DisableTX == 'D' ? "TEST RUNNING" : "START TEST") );

	// Render Status Box
	CLGraphics::DrawBox( CLRectangle( CLTestForm_StatusRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big,
		RGBColor_Black,
		1, 0xA9A9A9 );
	CLGraphics::DrawText( CLTestForm_StatusLabelPoint, CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
		RGBColor_Black, RGBColor_White,
		"STATUS", CLTestForm_StatusLabelLength );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );
}

void CLTestUnitForm::RenderData()
{
	RGBColor	backColor	= RGBColor_Black;
	RGBColor	foreColor	= RGBColor_White;
	char		text[ 40 ];

	switch (gKTSGlobal.DataTest[ 0 ])
	{
		case TEST_BYPASS:
			strcpy( text, (gKTSGlobal.DataTest[ 1 ] == 'o' ? "BYPASS OPEN" : "BYPASS CLOSE") );
			break;
			
		case TEST_OUTPUT:
			strcpy( text, (gKTSGlobal.DataTest[ 1 ] == 'A' ? "OUTPUT CLOSE" : "OUTPUT OPEN") );
			break;

		case TEST_BUZZER:
			strcpy( text, "BUZZER" );
			break;

		case TEST_IPEHD:
			strcpy( text, (gKTSGlobal.DataTest[ 1 ] == 'A' ? "IPEHD ON" : "IPEHD OFF") );
			break;

		case TEST_LEDS:
			strcpy( text, (gKTSGlobal.DataTest[ 1 ] == 'C' ? "ALL LED LIGHT ON" : "ALL LED LIGHT OFF") );
			break;
		
		case TEST_RESULT:
			if (gKTSGlobal.DataTest[ 1 ] == 'S')
			{
				foreColor	= RGBColor_Green;
				strcpy( text, "TEST SUCCESSFUL" );
			}
			else
			{
				foreColor	= RGBColor_Red;
				strcpy( text, "TEST FAULT!" );
			}
			break;
		
		case TEST_BURN_IN:
			sprintf( text, "BURN IN SINCE:\n%d min.",
				gKTSGlobal.DataTest[ 1 ] );
            break;		
		
		case TEST_CHANGE_SPEED:
			sprintf( text, "CHANGE SPEED: %d%",
				gKTSGlobal.DataTest[ 1 ] );
            break;

		default:
			strcpy( text, (gKTSGlobal.DisableTX == 'D' ? "RUNNING" : "NOT RUNNING") );
			break;
	}
	
	CLGraphics::DrawBoxWithText( CLRectangle( CLTestForm_StatusTextRectangle ), CLGraphicStyleOptions_VAlign_Middle | CLGraphicStyleOptions_HAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big,
		backColor, foreColor,
		text );
}

bool CLTestUnitForm::SendTestMessage( unsigned short options )
{
	ComQueue_Status	testMessage_Status;

	// Visualizza il messaggio di scrittura in corso
	if (CLFormOption_CanShowWriteMessage_Starting( options ))
	{
		CLGraphics::DrawBoxWithText( CLRectangle( CLTestForm_SendMessagePanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
			0x778899, RGBColor_White,
			1, RGBColor_Black,
			"SEND START TEST MESSAGE" );
	}

	// Accoda la richiesta di WriteEeprom
	ComQueue_AddTestRequest( &testMessage_Status, NULL );

	// Aspetta l'elaborazione della richiesta
	while (COM_REQUEST_ISRUNNING(testMessage_Status))
		CLKTS::Process();
	
	CLKTS::Pir_Process();
	
	// Se non e' andata a buon fine, message + home
	if (testMessage_Status.Status != COM_REQUEST_STATUS_COMPLETED)
	{
		// Visualizza il messaggio di errore
		if (CLFormOption_CanShowWriteMessage_Error( options ))
		{
			CLGraphics::DrawBoxWithText( CLRectangle( CLTestForm_SendMessagePanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
				0xDA5757, RGBColor_White,
				1, RGBColor_Black,
				"SEND MESSAGE ERROR!" );
			delay( 3000 );
		}

		return false;
	}

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
	{
		CLGraphics::DrawBoxWithText( CLRectangle( CLTestForm_SendMessagePanelRectangle ), CLGraphicStyleOptions_BorderRound_Yes | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine | CLGraphicStyleOptions_Font_Big | CLGraphicStyleOptions_TextAlignBy_Pixel,
			0x65b483, RGBColor_White,
			1, RGBColor_Black,
			"STARTING TEST..." );
		delay( 3000 );
	}

	return true;
}
// -----------------------------------------------------------------------------
// CLTestUnitForm [class]
// =============================================================================

