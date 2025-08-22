 /*************************************************************************************
 *  file:			CLWeeklyMainForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLWeeklyConfigForm_h
#define __CLWeeklyConfigForm_h

#include "CLForm.h"

CLFormResult CLWeeklyMainForm_Open( unsigned short options );

// =============================================================================
// CLWeeklyMainForm [class]
// =============================================================================
// Description: Form principale per la configurazione della weekly program
// -----------------------------------------------------------------------------
class _PACK CLWeeklyMainForm
	: public CLForm
{
	public: CLWeeklyMainForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_BackButtonRectangle;
	private: CLRectangle m_OkButtonRectangle;

	private: CLRectangle m_OnOffButtonRectangle;
	private: CLRectangle m_ProgramButtonRectangle;
	private: CLRectangle m_ViewButtonRectangle;
	private: CLRectangle m_SetTemperatureButtonRectangle;
	private: CLRectangle m_SetSpeedButtonRectangle;

	private: bool m_Enabled;
	public: void SetEnabled( bool value );

	public: CLFormResult Open( unsigned short options );
	private: bool Save( unsigned short options );

	private: void RenderPage();
	private: void RenderButtons();

	private: bool CanConfigThreeSpeed();
	private: bool ConfigThreeSpeed( unsigned short options );
};
// -----------------------------------------------------------------------------
// CLWeeklyMainForm [class]
// =============================================================================

// =============================================================================
// CLWeeklySupport [class]
// =============================================================================
// Description: Funzioni di supporto per la gestione del weekly program
// -----------------------------------------------------------------------------
class CLWeeklySupport
{
	public: static void RenderSelectedDays( short x, short y, byte value );
	public: static void RenderHoursAxis( short x, short y,
		RGBColor backgroundColor, RGBColor foregroundColor );
};
// -----------------------------------------------------------------------------
// CLWeeklySupport [class]
// =============================================================================

#endif

