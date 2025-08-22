#include "CLSelectionLanguageForm.h"

#include "CLKTS.h"
#include "CLLCDCommon.h"
#include "CLLocalitation.h"
#include "CLTouch.h"

#define CLSelectionLanguageForm_Flag1Button				33, 44, 92, 93
#define CLSelectionLanguageForm_Flag2Button				130, 44, 189, 93
#define CLSelectionLanguageForm_Flag3Button				226, 44, 285, 93
#define CLSelectionLanguageForm_Flag4Button				33, 114, 92, 163
#define CLSelectionLanguageForm_Flag5Button				130, 114, 189, 163
#define CLSelectionLanguageForm_Flag6Button				226, 114, 285, 163
#define	CLSelectionLanguageForm_PreviousButtonRectangle	161, 190, 204, 229
#define	CLSelectionLanguageForm_NextButtonRectangle		215, 190, 258, 229

const byte Flag_NoSelected = 0xFF;

CLFormResult CLSelectionLanguageForm_Open( unsigned short options )
{
	CLSelectionLanguageForm	form;

	return form.Open( options );
}

// =============================================================================
// CLSelectionLanguageForm [class]
// =============================================================================
CLSelectionLanguageForm::CLSelectionLanguageForm()
	: m_FlagButtonStyle_Selected(), m_FlagButtonStyle_Normal()
{
	m_HomeButtonRectangle.Set( Form_HomeButtonRectangle );
	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_OkButtonRectangle );
	m_PreviousButtonRectangle.Set( CLSelectionLanguageForm_PreviousButtonRectangle );
	m_NextButtonRectangle.Set( CLSelectionLanguageForm_NextButtonRectangle );

	m_FlagButtonStyle_Normal.Set( CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White );
	m_FlagButtonStyle_Selected.Set( CLGraphicStyleOptions_Default, RGBColor_Black, RGBColor_White, 1, RGBColor_White );

	m_FlagsButtons[ 0 ].Set( CLSelectionLanguageForm_Flag1Button );
	m_FlagsButtons[ 1 ].Set( CLSelectionLanguageForm_Flag2Button );
	m_FlagsButtons[ 2 ].Set( CLSelectionLanguageForm_Flag3Button );
	m_FlagsButtons[ 3 ].Set( CLSelectionLanguageForm_Flag4Button );
	m_FlagsButtons[ 4 ].Set( CLSelectionLanguageForm_Flag5Button );
	m_FlagsButtons[ 5 ].Set( CLSelectionLanguageForm_Flag6Button );

	m_FlagCount	= 0;
	switch (CLKTS::GetCustomerId())
	{
		case CUSTOMERID_SIG:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_NL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_DE;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_PL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_HU;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_RO;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_BG;
			//m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_TR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_IT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_SL;
			break;
			
		case CUSTOMERID_IN:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_NL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_DE;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_PL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_HU;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_RO;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_BG;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_IT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_SL;
			break;
		

		case CUSTOMERID_AL:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_DE;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_IT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			break;

		case CUSTOMERID_FA:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_PT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			break;

		case CUSTOMERID_FAI:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_IT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			break;

		case CUSTOMERID_NL:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_DE;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			break;

		case CUSTOMERID_CL:
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_EN;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_FR;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_DE;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_IT;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_NL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_PL;
			m_FlagsLanguagesIds[ m_FlagCount++ ]	= CLLanguageId_SL;
			break;

		default:
			for (int languagesCounter = 0; languagesCounter < CLLanguageId__COUNT; languagesCounter++)
			{
				if (LANGUAGE_ENABLED & (1 << languagesCounter))
				{
					m_FlagsLanguagesIds[ m_FlagCount++ ]	= languagesCounter;
					//if (m_FlagCount == 6)
					//	break;
				}
			}
	}
}

CLFormResult CLSelectionLanguageForm::Open( unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	m_CurrentFlagsIndex	= Flag_NoSelected;
	for (int flagsCounter = 0; flagsCounter < m_FlagCount; flagsCounter++)
	{
		if (m_FlagsLanguagesIds[ flagsCounter ] == gKTSGlobal.LanguageId)
		{
			m_CurrentFlagsIndex	= flagsCounter;
			break;
		}
	}

	m_Page.SetPageCount( (m_FlagCount / 6) + (m_FlagCount % 6 ? 1 : 0) );
	m_Page.Go( m_CurrentFlagsIndex != Flag_NoSelected ? m_CurrentFlagsIndex / 6 : 0 );

	RenderPage( options );

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage( options );
		
		CLKTS::Pir_Process();
		
		if (Touched())
		{
			touchX	= ReadX();
			touchY	= ReadY();

			// Home Button
			if (CLFormOption_IsHomeButtonShow( options ) && m_HomeButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_HomeButtonRectangle );
				formResult	= CLFormResult_Home;
				break;
			}
			else
			// Back Button
			if (CLFormOption_IsBackButtonShow( options ) && m_BackButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackButtonRectangle );
				formResult	= CLFormResult_Back;
				break;
			}
			else
			// Next Button
			if (m_NextButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_NextButtonRectangle );

				if (m_Page.GoNext())
					RenderPage( options );
			}
			else
			// Previous Button
			if (m_PreviousButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_PreviousButtonRectangle );

				if (m_Page.GoPrevious())
					RenderPage( options );
			}
			else
			// Ok Button
			if (m_CurrentFlagsIndex != Flag_NoSelected && m_OkButtonRectangle.Contains( touchX, touchY ))
			{
				if (Save( options ))
				{
					if (CLFormOption_CanExitAfterWrite( options ))
					{
						formResult	= CLFormOption_GetHomeOrBackAfterWrite( options );
						break;
					}
				}
				RenderPage( options );
			}
			else
			{
				bool	isFlagSelected	= false;
				for (int flagsCounter = 0; flagsCounter < 6; flagsCounter++)
				{
					if (m_FlagsButtons[ flagsCounter ].Contains( touchX, touchY ))
					{
						isFlagSelected	= true;
						SelectFlag( m_Page.GetValue() * 6 + flagsCounter );
						break;
					}
				}

				if (!isFlagSelected)
					WaitForTouchRelease();
			}
		}
    }

	CLLocalitation::SetPrimaryLanguage( gKTSGlobal.LanguageId );

	return formResult;
}

bool CLSelectionLanguageForm::Save( unsigned short options )
{
	CLKTS::SetLanguage( m_FlagsLanguagesIds[ m_CurrentFlagsIndex ] );

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return true;
}

void CLSelectionLanguageForm::RenderPage( unsigned short options )
{
	// Clear screen
	gLCD.clrScr();

	// Draw Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Home Button
	if (CLFormOption_IsHomeButtonShow( options ))
		CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Testo del tasto Back
	if (CLFormOption_IsBackButtonShow( options ))
		CLLCDCommon::DrawBackButton( m_BackButtonRectangle, GenericButtonStyle_Normal_BigFont );

	// Tasto Previous
	CLLCDCommon::DrawPreviousButton( m_PreviousButtonRectangle,
		(m_Page.IsFirst() ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont) );

	// Tasto Next
	CLLCDCommon::DrawNextButton( m_NextButtonRectangle,
		(m_Page.IsLast() ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont) );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	SelectFlag( m_CurrentFlagsIndex );

	RenderMainTitle();
	RenderOkButton();

	for (int flagsCounter = 0; flagsCounter < 6; flagsCounter++)
	{
		int	flagIndex	= (m_Page.GetValue() * 6) + flagsCounter;
		if (flagIndex >= m_FlagCount)
			break;
		RenderFlagButton( flagIndex, (m_CurrentFlagsIndex == flagIndex ? true : false) );
	}
}

void CLSelectionLanguageForm::RenderFlagButton( byte index, bool selected )
{
	if (index == Flag_NoSelected ||
		index < m_Page.GetValue() * 6 ||
		index > m_Page.GetValue() * 6 + 5)
		return;

	int	diplayIndex	= index % 6;

	CLGraphics::DrawBox( m_FlagsButtons[ diplayIndex ],
		(selected ? m_FlagButtonStyle_Selected : m_FlagButtonStyle_Normal) );
	
	switch (m_FlagsLanguagesIds[ index ])
	{
		case CLLanguageId_NL:
			CLLCDCommon::DrawFlag_Netherlands( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_EN:
			CLLCDCommon::DrawFlag_UnitedKingdom( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_FR:
			CLLCDCommon::DrawFlag_France( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_DE:
			CLLCDCommon::DrawFlag_Germany( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_IT:
			CLLCDCommon::DrawFlag_Italy( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_PT:
			CLLCDCommon::DrawFlag_Portughese( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_PL:
			CLLCDCommon::DrawFlag_Polish( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_SL:
			CLLCDCommon::DrawFlag_Slovenia( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_RO:
			CLLCDCommon::DrawFlag_Romania( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_BG:
			CLLCDCommon::DrawFlag_Bulgaria( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;

		case CLLanguageId_HU:
			CLLCDCommon::DrawFlag_Hungary( m_FlagsButtons[ diplayIndex ].GetX1() + 6, m_FlagsButtons[ diplayIndex ].GetY1() + 6 );
			break;
	}
}

void CLSelectionLanguageForm::RenderMainTitle()
{
	byte	languageId;

	languageId	= (m_CurrentFlagsIndex == Flag_NoSelected ? CLLanguageId_EN : m_FlagsLanguagesIds[ m_CurrentFlagsIndex ]);

	CLLocalitation::SetPrimaryLanguage( languageId );
	RenderFormTitle( CLLocalitation::GetText( CLTextId_SELECT_LANGUAGE ),
		&m_Page );
}

void CLSelectionLanguageForm::RenderOkButton()
{
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		(m_CurrentFlagsIndex == Flag_NoSelected ? GenericButtonStyle_Disabled_BigFont : GenericButtonStyle_Normal_BigFont) );
}

void CLSelectionLanguageForm::SelectFlag( byte flagIndex )
{
	if (flagIndex >= m_FlagCount && flagIndex != Flag_NoSelected)
		return;

	RenderFlagButton( m_CurrentFlagsIndex, false );
	m_CurrentFlagsIndex	= flagIndex;
	RenderFlagButton( m_CurrentFlagsIndex, true );

	// Update Display
	RenderMainTitle();
	RenderOkButton();
}


