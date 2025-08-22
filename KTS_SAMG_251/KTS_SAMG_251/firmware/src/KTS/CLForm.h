 /*************************************************************************************
 *  file:			CLForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLForm_h
#define __CLForm_h

#include "CLCommon.h"
#include "CLGraphics.h"

enum CLFormResult
{
	CLFormResult_Back	= 0,
	CLFormResult_Home	= 1,
	CLFormResult_None	= 3,
	CLFormResult_Ok		= 4,
	CLFormResult_Cancel	= 5
};

#define CLFormOption_CanShowWriteMessage_Starting( options ) (options & CLFormOption_ShowWriteMesssages_Starting)
#define CLFormOption_CanShowWriteMessage_Error( options ) (options & CLFormOption_ShowWriteMesssages_Error)
#define CLFormOption_CanShowWriteMessage_Success( options ) (options & CLFormOption_ShowWriteMesssages_Success)
#define CLFormOption_CanExitAfterWrite( options ) (options & CLFormOption_GoHomeAfterWrite || options & CLFormOption_GoBackAfterWrite)
#define CLFormOption_GetHomeOrBackAfterWrite( options ) (options & CLFormOption_GoHomeAfterWrite ? CLFormResult_Home : CLFormResult_Back)
#define CLFormOption_IsHomeButtonShow( options ) (options & CLFormOption_HideButton_Home ? false : true)
#define CLFormOption_IsBackButtonShow( options ) (options & CLFormOption_HideButton_Back ? false : true)

enum CLFormOption
{	
	CLFormOption_Default						= 0x00,
	CLFormOption_GoHomeAfterWrite				= 0x01,
	CLFormOption_GoBackAfterWrite				= 0x02,
	CLFormOption_ShowWriteMesssages_None		= 0x00,
	CLFormOption_ShowWriteMesssages_All			= 0x1C,
	CLFormOption_ShowWriteMesssages_Starting	= 0x04,
	CLFormOption_ShowWriteMesssages_Error		= 0x08,
	CLFormOption_ShowWriteMesssages_Success		= 0x10,
	CLFormOption_HideButton_Home				= 0x20,
	CLFormOption_HideButton_Back				= 0x40,
	CLFormOption_AdminMode						= 0x80
};

struct _PACK CLPage
{
	public: CLPage();
	public: CLPage( byte pageCount );
	public: CLPage( byte pageCount, byte initialValue );

	private: byte m_Value;
	public: byte GetValue();

	private: byte m_PageCount;
	public: byte GetPageCount();
	public: void SetPageCount( byte value );

	public: bool GoNext();
	public: bool GoPrevious();
	public: bool Go( byte value );

	public: inline bool IsFirst()
	{
		return !m_Value;
	}

	public: inline bool IsLast()
	{
		return m_Value == m_PageCount - 1;
	}
};

// =============================================================================
// CLProgressiveTouchUpDown [class static]
// =============================================================================
// Description: Classe di support per il ProgressiveTouchUpDown
// -----------------------------------------------------------------------------
class _PACK CLProgressiveTouchUpDown
{
	private: byte m_StepCount;
	private: byte m_CurrentCounter;
	private: byte m_CurrentStep;
	private: byte m_StepDelays[ 3 ];
	//private: short m_StepIncrements[ 3 ];
	private: byte m_StepCounters[ 3 ];
	private: unsigned long m_CurrentMillis;

	public: CLProgressiveTouchUpDown();
	public: CLProgressiveTouchUpDown( byte stepDelay, byte stepCounter );
	public: CLProgressiveTouchUpDown( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2 );
	public: CLProgressiveTouchUpDown( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2,
		byte stepDelay3, byte stepCounter3 );

	public: void Set( byte stepDelay, byte stepCounter );
	public: void Set( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2 );
	public: void Set( byte stepDelay1, byte stepCounter1,
		byte stepDelay2, byte stepCounter2,
		byte stepDelay3, byte stepCounter3 );

	public: void Reset();
	public: bool InWhile();
	public: bool CanIncrement();
	//public: short GetIncrement();
};
// -----------------------------------------------------------------------------
// CLProgressiveTouchUpDown [class static]
// =============================================================================

// =============================================================================
// CLForm [class]
// =============================================================================
// Description: Classe base per i form
// -----------------------------------------------------------------------------
class _PACK CLForm
{
	protected: enum CLState
	{
		CLState_None			= 0,
		CLState_Initializing	= 1,
		CLState_Running			= 2
	};

	public: CLForm();
	private: byte m_State;

	protected: void SetState( CLState state );
	protected: CLState GetState();

	//public: static void BuildFormTitle( char* title,
	//	int maxTitleLength,
	//	const char* pageTitle,
	//	CLPage* page );

	public: static void RenderFormTitle( const char* pageTitle,
		CLPage* page );
};
// -----------------------------------------------------------------------------
// CLForm [class]
// =============================================================================

#endif

