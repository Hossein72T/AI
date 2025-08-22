 /*************************************************************************************
 *  file:			CLSelectionTimeForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSelectionTimeForm_h
#define __CLSelectionTimeForm_h

#include "CLForm.h"
#include "CLDateTime.h"

CLFormResult CLSelectionTimeForm_Open( unsigned short options,
	const char* mainTitle, CLDateTime& time );

// =============================================================================
// CLSelectionTimeForm [class]
// =============================================================================
// Description: Form per la selezione dell'ora
// -----------------------------------------------------------------------------
class _PACK CLSelectionTimeForm
	: public CLForm
{
	public: CLSelectionTimeForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_HourUpButtonRectangle;
	private: CLRectangle m_HourDownButtonRectangle;
	private: CLRectangle m_MinuteUpButtonRectangle;
	private: CLRectangle m_MinuteDownButtonRectangle;
	private: CLRectangle m_SecondUpButtonRectangle;
	private: CLRectangle m_SecondDownButtonRectangle;

	private: CLProgressiveTouchUpDown m_ProgressiveTouchUpDown;

	private: CLDateTime m_Value;
	public: void SetValue( CLDateTime value );
	public: void SetHour( short value );
	public: void SetMinute( short value );
	public: void SetSecond( short value );

	public: CLFormResult Open( unsigned short options, const char* mainTitle,
		CLDateTime& time );

	private: void RenderPage( unsigned short options, const char* mainTitle );
	private: void RenderTime();
};
// -----------------------------------------------------------------------------
// CLSelectionTimeForm [class]
// =============================================================================

#endif

