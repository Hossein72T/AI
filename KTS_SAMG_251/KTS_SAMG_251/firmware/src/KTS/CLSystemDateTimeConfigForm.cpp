#include "CLSystemDateTimeConfigForm.h"

#include "CLKTS.h"
#include "CLLocalitation.h"
#include "CLLCDCommon.h"
#include "CLSelectionDateForm.h"
#include "CLSelectionTimeForm.h"

CLFormResult CLSystemDateTimeConfigForm_Open( unsigned short options )
{
	CLSystemDateTimeConfigForm	form;

	return form.Open( options );
}

// =============================================================================
// CLSystemDateTimeConfigForm [class]
// -----------------------------------------------------------------------------
CLSystemDateTimeConfigForm::CLSystemDateTimeConfigForm()
{
}

CLFormResult CLSystemDateTimeConfigForm::Open( unsigned short options )
{
	CLFormResult	formResult;
	CLDateTime		dateTime	= CLDateTime::GetNow();
	CLDateTime		minDate( 1, 1, 2000 );
	CLDateTime		maxDate( 31, 12, 2099 );
	byte			step	= 0;

	while (true)
	{
		if (step == 0)
		{
			formResult	= CLSelectionDateForm_Open( options,
				CLLocalitation::GetText( CLTextId_DATE_SETTINGS ),
				dateTime, &minDate, &maxDate );
		}
		else
		{
			formResult	= CLSelectionTimeForm_Open( options,
				CLLocalitation::GetText( CLTextId_TIME ),
				dateTime );
		}

		switch (formResult)
		{
			case CLFormResult_Back:
				if (step == 0)
					return formResult;
				step--;
				continue;

			case CLFormResult_Home:
				return formResult;
		}

		step++;
		if (step == 2)
			break;
	}

	CLKTS::SetDateTime( dateTime );

	// Visualizza il messaggio di ok
	if (CLFormOption_CanShowWriteMessage_Success( options ))
		CLLCDCommon::WriteDataPanel_DisplaySuccess();

	return formResult;
}
// -----------------------------------------------------------------------------
// CLSystemDateTimeConfigForm [class]
// =============================================================================

