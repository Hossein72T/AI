 /*************************************************************************************
 *  file:			CLInfoForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLInfoForm_h
#define __CLInfoForm_h

#include "CLForm.h"
#include "qrcodegen.h"
#include "CLImages.h"
#include <string.h>

CLFormResult CLInfoForm_Open();

const int CLInfoForm_AccessoryPerPage = 24;

// =============================================================================
// CLInfoForm [class]
// =============================================================================
// Description: Form per la visualizzazione delle info
// -----------------------------------------------------------------------------
class _PACK CLInfoForm
	: public CLForm
{
	public: CLInfoForm();

	// Buttons
	private: CLRectangle m_HomeButtonRectangle;
	private: CLRectangle m_NextButtonRectangle;
	private: CLRectangle m_PreviousButtonRectangle;
    private: CLRectangle m_Qr_Code_Rectangle;
    private: CLRectangle m_Avensys_Rectangle;

	private: byte m_AccessoryPageStartIndexes[ 32 / CLInfoForm_AccessoryPerPage + ((32 % CLInfoForm_AccessoryPerPage) > 0 ? 1 : 0) ];

    public: word Measure_CO2_1;
    public: word Measure_VOC_1;
    public: byte Measure_RH_1;
    public: word Measure_CO2_2;
    public: byte Measure_RH_2;
    public: byte Firm_Ver_CO2_1;
    public: byte Firm_Ver_CO2_2;
    public: byte CO2_1_LinkLevel;
    public: byte CO2_2_LinkLevel;
    public: word Measure_IAQ_1;
    public: word Measure_IAQ_2;
    public: byte CO2_1_Status;
	public: byte CO2_2_Status;
    public: byte CO2_1_Accuracy;
    public: byte CO2_2_Accuracy;
    public: byte IAQ_1_Accuracy;
    public: byte IAQ_2_Accuracy;
    
    private: bool m_FirstRequestDebugData;
    
	// Page
	private: CLPage m_Page;

	public: CLFormResult Open();

	private: void RenderPage();
 
};
// -----------------------------------------------------------------------------
// CLInfoForm [class]
// =============================================================================

#endif

