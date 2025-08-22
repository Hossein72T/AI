#include "CLPasswordForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLTouch.h"
#include "CLMessageBoxForm.h"

#define	CLPasswordForm_DigitsFrame				144, 28, 313, 235
#define	CLPasswordForm_Digit1ButtonRectangle	153, 35, 192, 74
#define	CLPasswordForm_Digit2ButtonRectangle	210, 35, 249, 74
#define	CLPasswordForm_Digit3ButtonRectangle	267, 35, 306, 74
#define	CLPasswordForm_Digit4ButtonRectangle	153, 86, 192, 125
#define	CLPasswordForm_Digit5ButtonRectangle	210, 86, 249, 125
#define	CLPasswordForm_Digit6ButtonRectangle	267, 86, 306, 125
#define	CLPasswordForm_Digit7ButtonRectangle	153, 137, 192, 176
#define	CLPasswordForm_Digit8ButtonRectangle	210, 137, 249, 176
#define	CLPasswordForm_Digit9ButtonRectangle	267, 137, 306, 176
#define	CLPasswordForm_Digit0ButtonRectangle	210, 188, 249, 227
#define	CLPasswordForm_BackspaceButtonRectangle	153, 188, 192, 227
#define	CLPasswordForm_OkButtonRectangle		267, 188, 306, 227

#define	CLPasswordForm_BackButtonRectangle		39, 188, 109, 227
#define	CLPasswordForm_PasswordTexRectangle		2, 28, 141, 67
#define	CLPasswordForm_PasswordRectangle		29, 79, 116, 101

CLFormResult CLPasswordForm_RequestOpen( char* resultPassword,
	const char* title, unsigned short options )
{
	CLPasswordForm	form;
	CLFormResult	formResult;

	if ((formResult = form.RequestOpen( title, options )) == CLFormResult_Ok)
		strcpy( resultPassword, form.GetPassword() );

	return formResult;
}

CLFormResult CLPasswordForm_CheckOpen( char** validPasswords, byte validPasswordCount,
	byte retryCount,
	short& validPasswordIndex,
	const char* title, unsigned short options )
{
	CLPasswordForm	form;

	return form.CheckOpen( validPasswords, validPasswordCount, retryCount,
		validPasswordIndex, title, options );
}

CLFormResult CLPasswordForm_ChangeOpen( char* oldPassword, char* newPassword,
	const char* title, unsigned short options )
{
	CLPasswordForm	form;

	return form.ChangeOpen( oldPassword, newPassword, title, options );
}

// =============================================================================
// CLAlarmsReportForm [class]
// -----------------------------------------------------------------------------
CLPasswordForm::CLPasswordForm()
{
	m_BackButtonRectangle.Set( CLPasswordForm_BackButtonRectangle );

	m_DigitButtonRectangles[ 0 ].Set( CLPasswordForm_Digit0ButtonRectangle );
	m_DigitButtonRectangles[ 1 ].Set( CLPasswordForm_Digit1ButtonRectangle );
	m_DigitButtonRectangles[ 2 ].Set( CLPasswordForm_Digit2ButtonRectangle );
	m_DigitButtonRectangles[ 3 ].Set( CLPasswordForm_Digit3ButtonRectangle );
	m_DigitButtonRectangles[ 4 ].Set( CLPasswordForm_Digit4ButtonRectangle );
	m_DigitButtonRectangles[ 5 ].Set( CLPasswordForm_Digit5ButtonRectangle );
	m_DigitButtonRectangles[ 6 ].Set( CLPasswordForm_Digit6ButtonRectangle );
	m_DigitButtonRectangles[ 7 ].Set( CLPasswordForm_Digit7ButtonRectangle );
	m_DigitButtonRectangles[ 8 ].Set( CLPasswordForm_Digit8ButtonRectangle );
	m_DigitButtonRectangles[ 9 ].Set( CLPasswordForm_Digit9ButtonRectangle );

	m_OKButtonRectangle.Set( CLPasswordForm_OkButtonRectangle );
	m_BackspaceButtonRectangle.Set( CLPasswordForm_BackspaceButtonRectangle );
}

CLFormResult CLPasswordForm::RequestOpen( const char* title, unsigned short options )
{
	m_Mode	= CLMode_Request;
	return Open( title, options );
}

CLFormResult CLPasswordForm::CheckOpen( char** validPasswords, byte validPasswordCount,
	byte retryCount,
	short& validPasswordIndex,
	const char* title, unsigned short options )
{
	CLFormResult	formResult;
	
	m_Mode					= CLMode_Check;
	m_ValidPasswords		= validPasswords;
	m_ValidPasswordCount	= validPasswordCount;
	m_RetryCount			= retryCount;

	formResult	= Open( title, options );
	
	if (formResult == CLFormResult_Ok)
		validPasswordIndex	= m_ValidPasswordIndex;

	return formResult;
}

CLFormResult CLPasswordForm::ChangeOpen( char* oldPassword, char* newPassword,
	const char* title, unsigned short options )
{
	m_Mode			= CLMode_Change;
	m_OldPassword	= oldPassword;
	m_NewPassword	= newPassword;

	return Open( title, options  );
}

CLFormResult CLPasswordForm::Open( const char* title, unsigned short options )
{
	int				touchX, touchY;
	CLFormResult	formResult;

	// Reset password
	memset( m_Password, /*NULL*/ 0, sizeof(m_Password) );
	m_RetriesCounter	= 
	m_Step				= 0;

	RenderPage( title );

	while (true)
	{
		// Processa le funzionalità del KTS
		if (CLKTS::Process() == CLKTSProcessResult_ScreenSaverExecuted)
			RenderPage( title );
		
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
			// Backspace Button
			if (m_BackspaceButtonRectangle.Contains( touchX, touchY ))
			{
				CLLCDCommon::WaitButton( m_BackspaceButtonRectangle );
				if (strlen(m_Password) > 0)
				{
					m_Password[ strlen(m_Password) - 1 ]	= '\0';
					RenderTextPassword();
					RenderOKButton();
				}
			}
			else
			// OK Button
			if (m_OKButtonRectangle.Contains( touchX, touchY ) && strlen(m_Password) == 5)
			{
				CLLCDCommon::WaitButton( m_OKButtonRectangle );

				if (m_Mode == CLMode_Request)
				{
					formResult	= CLFormResult_Ok;
					break;
				}

				if (m_Mode == CLMode_Change)
				{
					if (m_Step == 0)
					{
						if (strncmp( m_OldPassword, m_Password, 5 ) != 0)
						{
							CLMessageBoxForm::RenderPanel( CLMessageBoxGravity_Error,
								CLLocalitation::GetText( CLTextId_PASSWORD ),
								CLLocalitation::GetText( CLTextId_PASSWORD_INCORRECT ) );

							CLKTS::Delay( 2000 );

							formResult	= CLFormResult_Cancel;
							m_Password[ 0 ]	= '\0';
							break;
						}
						m_Step++;
						m_Password[ 0 ]	= '\0';
						RenderPage( title );
					}
					else
					if (m_Step == 1)
					{
						strcpy( m_ChangeNewPassword, m_Password );
						m_Step++;
						m_Password[ 0 ]	= '\0';
						RenderPage( title );
					}
					else
					{
						if (strcmp( m_ChangeNewPassword, m_Password ) != 0)
						{
							CLMessageBoxForm::RenderPanel( CLMessageBoxGravity_Error,
								CLLocalitation::GetText( CLTextId_PASSWORD ),
								CLLocalitation::GetText( CLTextId_PASSWORD_INCORRECT ) );

							CLKTS::Delay( 2000 );

							formResult	= CLFormResult_Cancel;
							break;
						}

						memcpy( m_NewPassword, m_Password, 5 );
						formResult	= CLFormResult_Ok;
						break;
					}

				}
				else
				if (m_Mode == CLMode_Check)
				{
					bool	passwordIsValid	= false;
				
					m_ValidPasswordIndex	= -1;
					for (int passwordsCounter = 0; passwordsCounter < m_ValidPasswordCount; passwordsCounter++)
					{
						if (strncmp( m_ValidPasswords[ passwordsCounter ], m_Password, 5 ) == 0)
						{
							m_ValidPasswordIndex	= passwordsCounter;
							passwordIsValid			= true;
							break;
						}
					}

					if (passwordIsValid)
					{
						formResult	= CLFormResult_Ok;
						break;
					}

					CLMessageBoxForm::RenderPanel( CLMessageBoxGravity_Error,
						CLLocalitation::GetText( CLTextId_PASSWORD ),
						CLLocalitation::GetText( CLTextId_PASSWORD_INCORRECT ) );

					CLKTS::Delay( 2000 );

					if (++m_RetriesCounter == m_RetryCount)
					{
						formResult	= CLFormResult_Cancel;
						break;
					}
					m_Password[ 0 ]	= '\0';
					RenderPage( title );
				}
			}
			else
			// Digit Buttons
			{
				bool	inDigitButton	= false;
				for (int digitsCounter = 0; digitsCounter < 10; digitsCounter++)
				{
					if (m_DigitButtonRectangles[ digitsCounter ].Contains( touchX, touchY ))
					{
						int	passwordLength	= strlen(m_Password);

						CLLCDCommon::WaitButton( m_DigitButtonRectangles[ digitsCounter ] );

						if (passwordLength < 5)
                        {
							m_Password[ passwordLength++ ]	= '0' + digitsCounter;
							m_Password[ passwordLength ]	= '\0';
							RenderTextPassword();
                        }
						inDigitButton	= true;
						RenderOKButton();
					}
				}

				if (!inDigitButton)
					WaitForTouchRelease();
			}
		}
    }

	return formResult;
}

void CLPasswordForm::RenderPage( const char* title )
{
	// Clear screen
	gLCD.clrScr();

	// Draw Main Frame
	CLGraphics::DrawBox( CLRectangle( 0, 0, 319, 239 ),
		GenericForm_Data_Style );

	// Back Button
	CLLCDCommon::DrawBackButton( m_BackButtonRectangle,
		GenericButtonStyle_Normal_BigFont );

	// Display Title
	RenderFormTitle( title,
		NULL );

	// Display Digit Buttons
	for (int digitsCounter = 0; digitsCounter < 10; digitsCounter++)
	{
		char	digitText[ 2 ];

		digitText[ 1 ]	= '\0';
		digitText[ 0 ]	= '0' + digitsCounter;

		CLLCDCommon::DrawGenericButton( m_DigitButtonRectangles[ digitsCounter ],
			GenericButtonStyle_Normal_BigFont,
			digitText );
	}

	CLLCDCommon::DrawGenericButton( m_BackspaceButtonRectangle,
		GenericButtonStyle_Normal_BigFont,
		"<-" );

	// Render OK Button
	RenderOKButton();

	// Display PasswordText
	RenderTextPassword();

	gLCD.setRGBBackColor( RGBColor_Black );
	gLCD.setRGBColor( RGBColor_White );
}

void CLPasswordForm::RenderTextPassword()
{
	int		passwordLength	= strlen( m_Password );
	char	textMask[ sizeof(m_Password) ];

	memset( textMask, '*', passwordLength );
	textMask[ passwordLength ]	= '\0';

	switch (m_Mode)
	{
		case CLMode_Request:
		case CLMode_Check:
			CLGraphics::DrawBoxWithText( CLRectangle( CLPasswordForm_PasswordTexRectangle ), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center,
				RGBColor_Black, RGBColor_White,
				CLLocalitation::GetText( CLTextId_PASSWORD ) );
			break;

		case CLMode_Change:
		{
			char*	text	= NULL;

			switch (m_Step)
			{
				case 0:
					text	= (char*) CLLocalitation::GetText( CLTextId_OLD_PASSWORD );
					break;
				case 1:
					text	= (char*) CLLocalitation::GetText( CLTextId_NEW_PASSWORD );
					break;
				case 2:
					text	= (char*) CLLocalitation::GetText( CLTextId_REPEAT_NEW_PASSWORD );
					break;
			}
			if (text)
			{
				CLGraphics::DrawBoxWithText( CLRectangle( CLPasswordForm_PasswordTexRectangle ), CLGraphicStyleOptions_Font_Small | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_Text_MultiLine,
					RGBColor_Black, RGBColor_White,
					text );
			}
			break;
		}
	}

	CLGraphics::DrawBoxWithText( CLRectangle( CLPasswordForm_PasswordRectangle ), CLGraphicStyleOptions_HVAlign_Center | CLGraphicStyleOptions_TextAlignBy_Pixel | CLGraphicStyleOptions_Font_Big,
		RGBColor_White, RGBColor_Black,
		textMask );
}

void CLPasswordForm::RenderOKButton()
{
	CLLCDCommon::DrawGenericButton( m_OKButtonRectangle,
		(strlen( m_Password ) == 5 ? GenericButtonStyle_Normal_BigFont : GenericButtonStyle_Disabled_BigFont),
		CLFixedText_OK );
}

char* CLPasswordForm::GetPassword()
{
	return m_Password;
}
// -----------------------------------------------------------------------------
// CLAlarmsReportForm [class]
// =============================================================================

