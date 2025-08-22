 /*************************************************************************************
 *  file:			CLPasswordForm.h
 *
 *  Author/Date:
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLPasswordForm_h
#define __CLPasswordForm_h

#include "CLForm.h"

CLFormResult CLPasswordForm_RequestOpen( char* resultPassword,
	const char* title, unsigned short options );
CLFormResult CLPasswordForm_CheckOpen( char** validPasswords, byte validPasswordCount,
	byte retryCount, short& validPasswordIndex,
	const char* title, unsigned short options );
CLFormResult CLPasswordForm_ChangeOpen( char* oldPassword, char* newPassword,
	const char* title, unsigned short options );

// =============================================================================
// CLPasswordForm [class]
// =============================================================================
// Description: Form per la gestione della/e password
// -----------------------------------------------------------------------------
class _PACK CLPasswordForm
	: public CLForm
{
	private: enum CLMode
	{
		CLMode_Request,
		CLMode_Check,
		CLMode_Change
	};

	public: CLPasswordForm();

	// Buttons
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_DigitButtonRectangles[ 10 ];
	private: CLRectangle m_BackspaceButtonRectangle;
	private: CLRectangle m_OKButtonRectangle;

	private: CLMode m_Mode;

	// Mode Check
	private: char** m_ValidPasswords;
	private: byte m_ValidPasswordCount;
	private: byte m_RetryCount;
	private: byte m_RetriesCounter;
	private: short m_ValidPasswordIndex;

	// Mode Change
	private: char* m_OldPassword;
	private: char* m_NewPassword;
	private: char m_ChangeNewPassword[ 6 ];
	private: byte m_Step;

	private: char m_Password[ 6 ];
	public: char* GetPassword();

	public: CLFormResult RequestOpen( const char* title, unsigned short options );
	public: CLFormResult CheckOpen( char** validPasswords, byte validPasswordCount,
		byte retryCount,
		short& validPasswordIndex,
		const char* title, unsigned short options );
	public: CLFormResult ChangeOpen( char* oldPassword, char* newPassword,
		const char* title, unsigned short options );

	private: CLFormResult Open( const char* title, unsigned short options );

	private: void RenderPage( const char* title );
	private: void RenderTextPassword();
	private: void RenderOKButton();
};
// -----------------------------------------------------------------------------
// CLRequestPasswordForm [class]
// =============================================================================

#endif

