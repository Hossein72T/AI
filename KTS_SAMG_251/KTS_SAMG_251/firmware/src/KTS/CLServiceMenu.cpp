#include "CLServiceMenu.h"

#include "CLLCDCommon.h"
#include "CLGraphics.h"
#include "CLKTS.h"
#include "CLPasswordForm.h"
#include "RDEeprom.h"
#include "CLLocalitation.h"
#include "CLTouch.h"

CLFormResult CLServiceMenu_Open()
{
	CLServiceMenu	form;

	char*	validPasswords[ 3 ];
	short	validPasswordIndex;

	validPasswords[ 0 ]	= (char*) gRDEeprom.servicePassword;
	validPasswords[ 1 ]	= (char*) BackdoorPassword;
	validPasswords[ 2 ]	= (char*) AdminPassword;

	if (CLPasswordForm_CheckOpen( validPasswords, 3, 3, validPasswordIndex,
		CLLocalitation::GetText( CLTextId_SERVICE ), CLFormOption_Default ) != CLFormResult_Ok)
	{
		return CLFormResult_Home;
	}

	return form.Open( validPasswordIndex == 2 );
}

// =============================================================================
// CLServiceMenu [class]
// -----------------------------------------------------------------------------
CLServiceMenu::CLServiceMenu()
	: m_HomeButtonRectangle( Form_HomeButtonRectangle )
{
	m_ItemButtonRectangles[ 0 ].Set( 70, 32, 250, 69 );
	m_ItemButtonRectangles[ 1 ].Set( 70, 83, 250, 120 );
	m_ItemButtonRectangles[ 2 ].Set( 70, 135, 250, 172 );
	m_ItemButtonRectangles[ 3 ].Set( 70, 186, 250, 223 );

	m_PreviousButtonRectangle.Set( 13, 83, 52, 136 );
	m_NextButtonRectangle.Set( 267, 83, 306, 136 );
}

CLFormResult CLServiceMenu::Open( bool adminMode )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_AdminMode	= adminMode;

	// Impostiamo gli items del menu'
	SetMenuItems( m_Items, CLServiceMenu_ItemCount, m_DisplayedItems, 4 );
	SetMenuItem(  0, CLProcedureId_AccessoryManagerForm );
	SetMenuItem(  1, CLProcedureId_SelectionVentilationControlForm );
	SetMenuItem(  2, CLProcedureId_SpeedModeConfigForm );
	SetMenuItem(  3, CLProcedureId_InputConfigForm );
	SetMenuItem(  4, CLProcedureId_OutputConfigForm );
	SetMenuItem(  5, CLProcedureId_BypassConfigForm );
	SetMenuItem(  6, CLProcedureId_UnbalanceConfigForm );
	SetMenuItem(  7, CLProcedureId_FilterConfigForm );
	SetMenuItem(  8, CLProcedureId_RHConfigForm );
	SetMenuItem(  9, CLProcedureId_CO2ConfigForm );
	SetMenuItem( 10, CLProcedureId_VOCConfigForm );
	SetMenuItem( 11, CLProcedureId_HysteresisTemperatureConfigForm );
	if (m_AdminMode)
		SetMenuItem( 12, CLProcedureId_ReportDebugDataAdminForm );
	else
		SetMenuItem( 12, CLProcedureId_ReportDebugDataForm );
	SetMenuItem( 13, CLProcedureId_UpgradeForm );
	SetMenuItem( 14, CLProcedureId_ServicePasswordChangeForm );
	SetMenuItem( 15, CLProcedureId_ProbesSettingsForm, m_AdminMode );
	SetMenuItem( 16, CLProcedureId_ModBusConfigForm );
	SetMenuItem( 17, CLProcedureId_TestUnitForm, m_AdminMode );
	SetMenuItem( 18, CLProcedureId_EepromResetForm, m_AdminMode );
	SetMenuItem( 19, CLProcedureId_ReferenceTSetting );
	
	#if KTS_SHOWFONTSFORM == 1
	SetMenuItem( 20, CLProcedureId_ShowFontsForm );
	#endif
	
	SetMenuItem( 21, CLProcedureId_DSCUpdateDelay );
	SetMenuItem( 22, CLProcedureId_PIRUpdateDelay );
    SetMenuItem( 23, CLProcedureId_CleanEventForm );
	
	RebuildItems();

	RenderPage();

	while (true)
	{
		// Processa le funzionalitÃ  del KTS
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
			// Next Button
			if (GetPageCount() > 1 && m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );
				GoNextPage();
				RebuildItems();
				RenderPage();
			}
			else
			// Previous Button
			if (GetPageCount() > 1 && m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );
				GoPreviousPage();
				RebuildItems();
				RenderPage();
			}
			else
			// Check Menu Items Button
			{
				CLProcedureId	selectedProcedureId	= CLProcedureId_None;

				for (short menuItemsCounter = 0; menuItemsCounter < 4; menuItemsCounter++)
				{
					if (m_DisplayedItems[ menuItemsCounter ] == 0xFF)
						break;

					if (m_Items[ m_DisplayedItems[ menuItemsCounter ] ].Enabled &&
						m_ItemButtonRectangles[ menuItemsCounter ].Contains( touchX, touchY ))
					{
						CLLCDCommon::WaitButton( m_ItemButtonRectangles[ menuItemsCounter ] );

						selectedProcedureId	= (CLProcedureId) m_Items[ m_DisplayedItems[ menuItemsCounter ] ].ProcedureId;
						break;
					}
				}

				if (selectedProcedureId != CLProcedureId_None)
				{
					formResult	= ExecuteProcedure( selectedProcedureId );
					if (formResult == CLFormResult_Home)
						break;
					RebuildItems();
					RenderPage();


				}
				else
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

CLFormResult CLServiceMenu::ExecuteProcedure( CLProcedureId procedureId )
{
	if (m_AdminMode)
		return Procedure_Execute( procedureId, CLFormOption_ShowWriteMesssages_All | CLFormOption_GoBackAfterWrite | CLFormOption_AdminMode );
	return Procedure_Execute( procedureId, CLFormOption_ShowWriteMesssages_All | CLFormOption_GoBackAfterWrite );
}

void CLServiceMenu::RenderPage()
{
	char	text[ 30 ];

	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 239 ),
		GenericForm_Data_Style );

	// Display Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Display Title
	if (m_AdminMode)
		sprintf( text, "%s (+)", CLLocalitation::GetText( CLTextId_SERVICE ) );
	else
		strcpy( text, CLLocalitation::GetText( CLTextId_SERVICE ) );
	
	CLForm::RenderFormTitle( text,
		(GetPageCount() > 1 ? &m_Page : NULL) );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	if (GetPageCount() > 1)
	{
		CLLCDCommon::DrawArrowButton( m_PreviousButtonRectangle.GetX1(), m_PreviousButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Left );

		CLLCDCommon::DrawArrowButton( m_NextButtonRectangle.GetX1(), m_NextButtonRectangle.GetY1(),
			CLDrawArrowButtonDirection_Right );
	}

	RenderItems();
}

void CLServiceMenu::RebuildItems()
{
	CLMenu::RebuildItems();
}

void CLServiceMenu::RenderItems()
{
	CLMenu::RenderItems( m_ItemButtonRectangles );
}
// -----------------------------------------------------------------------------
// CLServiceMenu [class]
// =============================================================================

