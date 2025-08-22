#include "CLScreenSaver.h"
#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLogo.h"
#include "CLLCDCommon.h"
#include "CLScreenSaverForm.h"
#include "CLFunction.h"
#include "CLPasswordForm.h"

CLScreenSaverProcessResult ScreenSaver_Process()
{
	if (!gKTSEeprom.GetScreensaverEnabled())
		return CLScreenSaverProcessResult_ScreenSaverDisabled;

	if (gKTSGlobal.ScreenSaverActive)
		return CLScreenSaverProcessResult_ScreenSaverExecuting;

	if (millis() < gKTSGlobal.LastTouchedMilliseconds)
	{
		gKTSGlobal.LastTouchedMilliseconds				= millis();
		gKTSGlobal.ScreenSaver_LastTouchedMilliseconds	= millis();
	}

	if (CLKTS::IsScreenSaverSuspended())
		return CLScreenSaverProcessResult_ScreenSaverSuspended;

	if (millis() - gKTSGlobal.ScreenSaver_LastTouchedMilliseconds >= ((unsigned long) gKTSEeprom.GetScreensaverMinutes() * 60000))
	{
		gKTSGlobal.ScreenSaverActive	= true;

		while (true)
		{
			CLScreenSaverForm_Open();

			// Se abilitata, richiede la password
			if (Function_IsEnabled( ENAB_PASSWORD ))
			{
				char*	validPasswords[ 4 ];
				short	validPasswordIndex;
				
				validPasswords[ 0 ]	= (char*) gRDEeprom.endUserPassword;
				validPasswords[ 1 ]	= (char*) gRDEeprom.servicePassword;
				validPasswords[ 2 ]	= (char*) BackdoorPassword;
				validPasswords[ 3 ]	= (char*) AdminPassword;

				if (CLPasswordForm_CheckOpen( validPasswords, 4, 3, validPasswordIndex, CLLocalitation::GetText( CLTextId_PASSWORD ), CLFormOption_Default ) == CLFormResult_Ok)
					break;
			}
			else
				break;
		}

		gKTSGlobal.ScreenSaverActive	= false;
		return CLScreenSaverProcessResult_ScreenSaverExecuted;
	}

	return CLScreenSaverProcessResult_Nothing;
}

