 /*************************************************************************************
 *  file:			CLAccessoryManagerForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLMessageBoxForm_h
#define __CLMessageBoxForm_h

#include "CLForm.h"

enum CLMessageBoxButtons
{
	CLMessageBoxButtons_Ok,
	CLMessageBoxButtons_YesNo,
	CLMessageBoxButtons_YesNoCancel
};

enum CLMessageBoxGravity
{
	CLMessageBoxGravity_Info,
	CLMessageBoxGravity_Question,
	CLMessageBoxGravity_Error,
	CLMessageBoxGravity_Warning
};

enum CLMessageBoxResult
{
	CLMessageBoxResult_Yes,
	CLMessageBoxResult_No,
	CLMessageBoxResult_Ok,
	CLMessageBoxResult_Cancel
};

// =============================================================================
// CLMessageBoxForm [class]
// =============================================================================
// Description: Form che visualizza un messaggio e pulsanti
// -----------------------------------------------------------------------------
class CLMessageBoxForm
{
	public: static void Open_Render( CLMessageBoxButtons buttons, CLMessageBoxGravity gravity,
	const char* title, const char* message,
	CLRectangle& buttonRectangle1, CLRectangle& buttonRectangle2, CLRectangle& buttonRectangle3 );

	public: static CLMessageBoxResult Open( CLMessageBoxButtons buttons, CLMessageBoxGravity gravity,
		const char* title, const char* message );

	public: static void RenderPanel( CLMessageBoxGravity gravity,
		const char* title, const char* message );
};
// -----------------------------------------------------------------------------
// CLMessageBoxForm [class]
// =============================================================================

#endif

