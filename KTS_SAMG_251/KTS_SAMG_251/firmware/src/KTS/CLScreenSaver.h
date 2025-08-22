#ifndef __CLScreenSaver_h
#define __CLScreenSaver_h

#include "CLCommon.h"
#include "RDEeprom.h"

#define SCREENSAVER_MINUTES_MIN	1
#define SCREENSAVER_MINUTES_MAX	15

enum CLScreenSaverProcessResult
{
	CLScreenSaverProcessResult_Nothing,
	CLScreenSaverProcessResult_ScreenSaverDisabled,
	CLScreenSaverProcessResult_ScreenSaverExecuted,
	CLScreenSaverProcessResult_ScreenSaverExecuting,
	CLScreenSaverProcessResult_ScreenSaverSuspended
};

CLScreenSaverProcessResult ScreenSaver_Process();

#endif

