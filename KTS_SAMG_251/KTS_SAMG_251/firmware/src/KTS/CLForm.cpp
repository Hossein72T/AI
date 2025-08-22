#include "CLForm.h"
#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"

// =============================================================================
// CLPage [class]
// -----------------------------------------------------------------------------
CLPage::CLPage()
{
	m_PageCount	= 0;
	m_Value		= 0;
}

CLPage::CLPage( byte pageCount )
{
	m_PageCount	= pageCount;
	m_Value		= 0;
}

CLPage::CLPage( byte pageCount, byte initialValue )
{
	m_PageCount	= pageCount;
	Go( initialValue );
}

byte CLPage::GetValue()
{
	return m_Value;
}

byte CLPage::GetPageCount()
{
	return m_PageCount;
}

void CLPage::SetPageCount( byte value )
{
	if (m_Value >= value)
		m_Value	= value - 1;
	m_PageCount	= value;
}

bool CLPage::GoNext()
{
	byte	currentValue	= m_Value;
	if (++m_Value == m_PageCount)
		m_Value	= 0;

	return (m_Value != currentValue);
}

bool CLPage::GoPrevious()
{
	byte	currentValue	= m_Value;
	if (m_Value == 0)
		m_Value	= m_PageCount - 1;
	else
		m_Value--;

	return (m_Value != currentValue);
}

bool CLPage::Go( byte value )
{
	if (value <= m_PageCount && value != m_Value)
	{
		m_Value	= value;
		return true;
	}

	return false;
}
// -----------------------------------------------------------------------------
// CLPage [class]
// =============================================================================

// =============================================================================
// CLProgressiveTouchUpDown [class static]
// -----------------------------------------------------------------------------
CLProgressiveTouchUpDown::CLProgressiveTouchUpDown()
{
	m_StepCount		= 0;
	m_CurrentStep	= -1;
}

CLProgressiveTouchUpDown::CLProgressiveTouchUpDown( byte stepDelay, byte stepCounter )
{
	Set( stepDelay, stepCounter );
}

CLProgressiveTouchUpDown::CLProgressiveTouchUpDown( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2 )
{
	Set( stepDelay1, stepCounter1,
		stepDelay2, stepCounter2 );
}

CLProgressiveTouchUpDown::CLProgressiveTouchUpDown( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2,
		byte stepDelay3, byte stepCounter3 )
{
	Set( stepDelay1, stepCounter1,
		stepDelay2, stepCounter2,
		stepDelay3, stepCounter3 );
}

void CLProgressiveTouchUpDown::Set( byte stepDelay, byte stepCounter )
{
	m_StepCount				= 1;
	m_CurrentCounter		= 0;
	m_CurrentStep			= -1;
	m_StepDelays[ 0 ]		= stepDelay;
	//m_StepIncrements[ 0 ]	= stepIncrement;
	m_StepCounters[ 0 ]		= stepCounter;
}

void CLProgressiveTouchUpDown::Set( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2 )
{
	m_StepCount				= 2;
	m_CurrentCounter		= 0;
	m_CurrentStep			= -1;
	m_StepDelays[ 0 ]		= stepDelay1;
	//m_StepIncrements[ 0 ]	= stepIncrement1;
	m_StepCounters[ 0 ]		= stepCounter1;
	m_StepDelays[ 1 ]		= stepDelay2;
	//m_StepIncrements[ 1 ]	= stepIncrement2;
	m_StepCounters[ 1 ]		= stepCounter2;
}

void CLProgressiveTouchUpDown::Set( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2,
		byte stepDelay3, byte stepCounter3 )
{
	m_StepCount				= 3;
	m_CurrentCounter		= 0;
	m_CurrentStep			= -1;
	m_StepDelays[ 0 ]		= stepDelay1;
	//m_StepIncrements[ 0 ]	= stepIncrement1;
	m_StepCounters[ 0 ]		= stepCounter1;
	m_StepDelays[ 1 ]		= stepDelay2;
	//m_StepIncrements[ 1 ]	= stepIncrement2;
	m_StepCounters[ 1 ]		= stepCounter2;
	m_StepDelays[ 2 ]		= stepDelay3;
	//m_StepIncrements[ 2 ]	= stepIncrement3;
	m_StepCounters[ 2 ]		= stepCounter3;
}

//short CLProgressiveTouchUpDown::GetIncrement()
//{
//	return (m_CurrentStep == -1 ? 0 : m_StepIncrements[ m_CurrentStep ]);
//}

void CLProgressiveTouchUpDown::Reset()
{
	m_CurrentStep		= 0;
	m_CurrentCounter	= 0;
	m_CurrentMillis		= millis();
}

bool CLProgressiveTouchUpDown::InWhile()
{
	if (m_StepCount == 0)
		return false;

	if (!Touched())
		return false;

	CLKTS::Process();
	CLKTS::Pir_Process();

	return true;
}

bool CLProgressiveTouchUpDown::CanIncrement()
{
	if (m_StepCount == 0)
		return false;

	if (millis() - m_CurrentMillis >= m_StepDelays[ m_CurrentStep ] ||
		millis() < m_CurrentMillis)
	{
		m_CurrentMillis	= millis();

		if (m_CurrentStep < m_StepCount - 1)
		{
			m_CurrentCounter++;

			if (m_CurrentCounter == m_StepCounters[ m_CurrentStep ])
			{
				m_CurrentStep++;
				m_CurrentCounter	= 0;
			}
		}

		return true;
	}
	return false;
}
// -----------------------------------------------------------------------------
// CLProgressiveTouchUpDown [class static]
// =============================================================================

// =============================================================================
// CLForm [class]
// -----------------------------------------------------------------------------
CLForm::CLForm()
{
	m_State	= CLState_None;
}

void CLForm::SetState( CLState state )
{
	m_State	= state;
}

CLForm::CLState CLForm::GetState()
{
	return (CLForm::CLState) m_State;
}

//void CLForm::BuildFormTitle( char* title,
//	int maxTitleLength,
//	const char* pageTitle,
//	CLPage* page )
//{
//	int		availableLength	= maxTitleLength;
//	char	pageText[ 10 ];
//
//	if (availableLength <= 0 || (page != NULL && page->GetPageCount() > 100))
//	{
//		*title	= '\0';
//		return;
//	}
//
//	if (page != NULL)
//	{
//		sprintf( pageText, " %d/%d", page->GetValue() + 1, page->GetPageCount() );
//		availableLength	-= strlen( pageText );
//
//		if (availableLength < 0)
//		{
//			*title	= '\0';
//			return;
//		}
//	}
//	else
//		pageText[ 0 ]	= '\0';
//
//	if (strlen( pageTitle ) > availableLength)
//	{
//		strncpy( title, pageTitle, availableLength );
//		title[ availableLength ]	= '\0';
//	}
//	else
//	{
//		strcpy( title, pageTitle );
//		while (strlen( title ) < availableLength)
//			strcat( title, " " );
//	}
//
//	if (*pageText)
//		strcat( title, pageText );
//}

void CLForm::RenderFormTitle( const char* pageTitle, CLPage* page )
{
	char			title[ GenericForm_Title_SmallFont_MaxLength + 1 ];
	char			pageText[ 10 ];
	int				titleWidth;
	CLGraphicStyle*	style;

	if (page == NULL)
		*pageText	= '\0';
	else
		sprintf( pageText, " %d/%d", page->GetValue() + 1, page->GetPageCount() );

	if (strlen( pageText ) + strlen( pageTitle ) <= GenericForm_Title_BigFont_MaxLength)
	{
		strcpy( title, pageTitle );
		titleWidth	= GenericForm_Title_BigFont_MaxLength;
		style		= &GenericForm_Title_BigFont_Style;
	}
	else
	if (strlen( pageText ) + strlen( pageTitle ) <= GenericForm_Title_SmallFont_MaxLength)
	{
		strcpy( title, pageTitle );
		titleWidth	= GenericForm_Title_SmallFont_MaxLength;
		style		= &GenericForm_Title_SmallFont_Style;
	}
	else
	{
		strncpy( title, pageTitle, GenericForm_Title_SmallFont_MaxLength - strlen( pageText ) );
		title[ GenericForm_Title_BigFont_MaxLength - strlen( pageText ) ]	= '\0';
		titleWidth															= GenericForm_Title_SmallFont_MaxLength;
		style																= &GenericForm_Title_SmallFont_Style;
	}

	while (strlen( title ) < titleWidth - strlen( pageText ))
		strcat( title, " " );
	strcat( title, pageText );

	CLGraphics::DrawBoxWithText( GenericForm_Title_Rectangle, *style, title );
}
// -----------------------------------------------------------------------------
// CLForm [class]
// =============================================================================

