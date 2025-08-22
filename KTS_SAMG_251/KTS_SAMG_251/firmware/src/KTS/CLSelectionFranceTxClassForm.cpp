#include "CLSelectionFranceTxClassForm.h"

#ifdef FRANCETX_ENABLED

#include "CLKTS.h"
#include "CLCommunicationManager.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"

#define  CLSelectionFranceTxClassForm_TxButton1Rectangle	20, 60, 99, 99
#define  CLSelectionFranceTxClassForm_TxButton2Rectangle	120, 60, 199, 99
#define  CLSelectionFranceTxClassForm_TxButton3Rectangle	221, 60, 300, 99
#define  CLSelectionFranceTxClassForm_TxButton4Rectangle	69, 120, 148, 159
#define  CLSelectionFranceTxClassForm_TxButton5Rectangle	171, 120, 250, 159

CLFormResult CLSelectionFranceTxClassForm_Open( const char* mainTitle,
	const char* subTitle,
	byte& value )
{
	CLSelectionFranceTxClassForm	form( mainTitle, subTitle );

	return form.Open( value );
}

// =============================================================================
// CLSelectionFranceTxClassForm [class]
// -----------------------------------------------------------------------------
CLSelectionFranceTxClassForm::CLSelectionFranceTxClassForm( const char* mainTitle,
	const char* subTitle )
{
	m_MainTitle	= (char*) mainTitle;
	m_SubTitle	= (char*) subTitle;

	m_BackButtonRectangle.Set( EditForm_BackButtonRectangle );
	m_OkButtonRectangle.Set( EditForm_SaveButtonRectangle );

	m_TxButtonRectangles[ 0 ].Set( CLSelectionFranceTxClassForm_TxButton1Rectangle );
	m_TxButtonRectangles[ 1 ].Set( CLSelectionFranceTxClassForm_TxButton2Rectangle );
	m_TxButtonRectangles[ 2 ].Set( CLSelectionFranceTxClassForm_TxButton3Rectangle );
	m_TxButtonRectangles[ 3 ].Set( CLSelectionFranceTxClassForm_TxButton4Rectangle );
	m_TxButtonRectangles[ 4 ].Set( CLSelectionFranceTxClassForm_TxButton5Rectangle );
}

CLFormResult CLSelectionFranceTxClassForm::Open( byte& value )
{
	int				touchX, touchY;
	CLFormResult	formResult;


	// Inizializza i dati
	SetState( CLState_Initializing );
	SetValue( value );
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
				value		= m_Value;
				formResult	= CLFormResult_Ok;
				break;
			}
			else
			{
				bool	isTxButtonPressed	= false;
				for (int classesCounter = 0; classesCounter < CLFranceApartmentClassCount; classesCounter++)
				{
					if (m_TxButtonRectangles[ classesCounter ].Contains( touchX, touchY ))
					{
						SetValue( classesCounter );
						isTxButtonPressed	= true;
						break;
					}
				}

				if (!isTxButtonPressed)
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

void CLSelectionFranceTxClassForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	// Draw main Frame
	CLGraphics::DrawBox( GenericForm_Data_Rectangle,
		GenericForm_Data_Style );

	// Display Main Title
	RenderFormTitle( m_MainTitle,
		NULL );

	// Display Sub Title
	if (m_SubTitle != NULL)
	{
		CLGraphics::DrawBoxWithText( CLRectangle( 1, 24, 318, 43 ),
			GenericForm_Title_BigFont_Style,
			m_SubTitle );
	}

	// Home Button
	CLLCDCommon::DrawHomeButton( Form_HomeButtonRectangle.GetX1(), Form_HomeButtonRectangle.GetY1() );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Ok Button
    CLLCDCommon::DrawOkButton( m_OkButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );

	RenderClassButtons();
}

void CLSelectionFranceTxClassForm::RenderClassButtons()
{
	char	text[ 10 ];

	for (int classesCounter = 0; classesCounter < CLFranceApartmentClassCount; classesCounter++)
	{
		sprintf( text, "T%d", classesCounter + 2 );
		CLLCDCommon::DrawGenericButton( m_TxButtonRectangles[ classesCounter ],
			(m_Value == classesCounter ? GenericButtonStyle_Selected_BigFont : GenericButtonStyle_Normal_BigFont),
			text );
	}
}

void CLSelectionFranceTxClassForm::SetValue( byte value )
{
	if (value >= CLFranceApartmentClassCount)
		value	= CLFranceApartmentClassCount - 1;

	m_Value	= value;

	if (GetState() == CLState_Running)
		RenderClassButtons();
}

byte CLSelectionFranceTxClassForm::GetValue()
{
	return m_Value;
}
// -----------------------------------------------------------------------------
// CLSelectionFranceTxClassForm [class]
// =============================================================================

#endif

