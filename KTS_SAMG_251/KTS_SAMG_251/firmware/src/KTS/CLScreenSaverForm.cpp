#include "CLScreenSaverForm.h"

#include "CLKTS.h"
#include "CLTouch.h"
#include "CLLCDCommon.h"
#include "CLLogo.h"

CLFormResult CLScreenSaverForm_Open()
{
	CLScreenSaverForm	form;

	return form.Open();
}

// =============================================================================
// CLScreenSaverForm [class]
// -----------------------------------------------------------------------------
CLScreenSaverForm::CLScreenSaverForm()
{
}

CLFormResult CLScreenSaverForm::Open()
{
	CLFormResult	formResult;
	int				count_Move_Logo	= 0;

	RenderPage();
	//analogWrite( pBACKLIGHT, LOW_BRIGHTESS );
    TC0_CH1_CompareASet (LOW_BRIGHTESS);

	while (true)
	{
		CLKTS::Process();
		
		CLKTS::Pir_Process();
		
		if (count_Move_Logo % 5000 == 0)
		{
			gLCD.setColor(255, 255, 255);
			gLCD.fillScr(255, 255, 255);
               
			logo( 0, 0, MOVE_LOGO_XY );      
		}
   
		count_Move_Logo++;

		if (Touched())
		{
			WaitForTouchRelease();

			formResult	= CLFormResult_Ok;
			break;
		}
    }

	//analogWrite(pBACKLIGHT, HIGH_BRIGHTESS);
    TC0_CH1_CompareASet (HIGH_BRIGHTESS);

	return formResult;
}

void CLScreenSaverForm::RenderPage()
{
	// Clear screen
	gLCD.clrScr();

	gLCD.setColor(255, 255, 255);
	gLCD.fillScr(255, 255, 255);
}
// -----------------------------------------------------------------------------
// CLPowerOffForm [class]
// =============================================================================

