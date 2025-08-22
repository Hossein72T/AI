#ifndef __CLBoxInfo_h
#define __CLBoxInfo_h

#include "CLCommon.h"
#include "CLGraphics.h"

enum CLBoxInfo_InfoId
{
	CLBoxInfo_InfoId_TReturn		= 0x01,
	CLBoxInfo_InfoId_TFresh			= 0x02,
	CLBoxInfo_InfoId_Filters		= 0x04,
	CLBoxInfo_InfoId_Accessories	= 0x08,
	CLBoxInfo_InfoId_Defrost		= 0x10,
	CLBoxInfo_InfoId_Bypass			= 0x20,
	CLBoxInfo_InfoId_Probes			= 0x40
};

// =============================================================================
// CLBoxInfo [class]
// =============================================================================
// Description: BoxInfo
// -----------------------------------------------------------------------------
class _PACK CLBoxInfo
{
	private: enum CLShowInfoId
	{
		CLShowInfoId_Boost,
		CLShowInfoId_Temperatures_TReturn,
		CLShowInfoId_Temperatures_TFresh,
		CLShowInfoId_Filters_DPS,
		CLShowInfoId_Accessory_PEHD_PHWD,
		CLShowInfoId_Accessory_HWD_EHD,
		CLShowInfoId_Accessory_CWD,
		CLShowInfoId_Defrost,
		CLShowInfoId_Bypass,
		CLShowInfoId_Probes_RH,
		CLShowInfoId_Probes_CO2,
		CLShowInfoId_Probes_VOC,
		CLShowInfoId_Probes_AWP,
		CLShowInfoId_Fire,

		CLShowInfoId_LASTITEM
	};

	public: CLBoxInfo();

	private: byte m_CurrentShowInfoId;
	private: unsigned long m_Refresh_Timer;

	public: void ClearBox();
	private: bool RenderInfo( CLShowInfoId showInfoId );
	public: void Process();
	public: void ForceRefresh();

	private: CLRectangle m_Rectangle;
	private: CLRectangle m_DataRectangle;
	public: void SetRectangle( short x1, short y1, short x2, short y2 );
	public: CLRectangle& GetRectangle();

	public: static bool IsEnabled( CLBoxInfo_InfoId infoId );
	public: static bool Write( byte value );
    
    private: CLRectangle m_AccuracyRectangle1;
    private: CLRectangle m_AccuracyRectangle2;
    private: CLRectangle m_AccuracyRectangle3;
    
    private: CLRectangle m_Accuracy1Rectangle1;
    private: CLRectangle m_Accuracy1Rectangle2;
    private: CLRectangle m_Accuracy1Rectangle3;
    
    private: CLRectangle m_AccuracynullRectangle1;
    private: CLRectangle m_Accuracy1nullRectangle1;

};
// -----------------------------------------------------------------------------
// CLBoxInfo [class]
// =============================================================================

#endif

