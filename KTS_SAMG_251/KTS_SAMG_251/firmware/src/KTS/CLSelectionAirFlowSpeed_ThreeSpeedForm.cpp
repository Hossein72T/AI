#include "CLSelectionAirFlowSpeed_ThreeSpeedForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLGraphics.h"
#include "CLLCDCommon.h"
#include "CLMessageBoxForm.h"
#include "CLCommunicationManager.h"
#include "CLTouch.h"
#include "CLVentilationControl.h"
#include "CLSpeedMode.h"
#include "CLSelectionSpeedForm.h"

CLFormResult CLSelectionAirFlowSpeed_ThreeSpeedForm_Open( unsigned short options,
	CLVentilationControl ventilationControl, unsigned short* speeds )
{
	CLSelectionAirFlowSpeed_ThreeSpeedForm	form;

	return form.Open( options, ventilationControl, speeds );
}

// =============================================================================
// CLSelectionAirFlowSpeed_ThreeSpeedForm [class]
// -----------------------------------------------------------------------------
CLSelectionAirFlowSpeed_ThreeSpeedForm::CLSelectionAirFlowSpeed_ThreeSpeedForm()
{
}

CLFormResult CLSelectionAirFlowSpeed_ThreeSpeedForm::Open( unsigned short options,
	CLVentilationControl ventilationControl, unsigned short* speeds )
{
	unsigned short	minValue, maxValue, incValue;
	int				currenteSpeedIndex;

	incValue	= SpeedMode_Stepless_GetIncValue( ventilationControl );
	minValue	= SpeedMode_Stepless_GetMinValue( ventilationControl );
	maxValue	= SpeedMode_Stepless_GetMaxValue( ventilationControl );

	currenteSpeedIndex	= 0;
	while (true)
	{
		CLFormResult	selectionSpeedFormFormResult;

		switch (currenteSpeedIndex)
		{
			case 0:
				selectionSpeedFormFormResult	= CLSelectionSpeedForm_Open(
					CLFormOption_Default,
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MODE ),
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MIN ),
					ventilationControl, minValue, maxValue - (incValue * 2), incValue,
					speeds[ 0 ] );
				break;

			case 1:
				selectionSpeedFormFormResult	= CLSelectionSpeedForm_Open(
					CLFormOption_Default,
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MODE ),
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MED ),
					ventilationControl, speeds[ 0 ] + incValue, maxValue - incValue, incValue,
					speeds[ 1 ] );
				break;

			case 2:
				selectionSpeedFormFormResult	= CLSelectionSpeedForm_Open(
					CLFormOption_Default,
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MODE ),
					CLLocalitation::GetText( CLTextId_SELECT_SPEED_MAX ),
					ventilationControl, speeds[ 1 ] + incValue, maxValue, incValue,
					speeds[ 2 ] );
				break;
		}

		if (selectionSpeedFormFormResult == CLFormResult_Back)
		{
			if (currenteSpeedIndex == 0)
				return CLFormResult_None;
			currenteSpeedIndex--;
		}
		else
		{
			if (currenteSpeedIndex == 2)
				break;
			currenteSpeedIndex++;
		}
	}

	return CLFormResult_Ok;
}
// -----------------------------------------------------------------------------
// CLSelectionAirFlowSpeed_ThreeSpeedForm [class]
// =============================================================================

