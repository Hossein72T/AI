 /*************************************************************************************
 *  file:			CLSystemDateTimeConfigForm.h
 *
 *  Author/Date:	Paolo Menchi marzo 2014
 *
 *  Descrizione:	...
 *
 *************************************************************************************/

#ifndef __CLSystemDateTimeConfigForm_h
#define __CLSystemDateTimeConfigForm_h

#include "CLForm.h"
#include "CLDateTime.h"

CLFormResult CLSystemDateTimeConfigForm_Open( unsigned short options );

// =============================================================================
// CLSystemDateTimeConfigForm [class]
// =============================================================================
// Description: Form per la modifica della data e ora di sistema
// -----------------------------------------------------------------------------
class _PACK CLSystemDateTimeConfigForm
	: public CLForm
{
	public: CLSystemDateTimeConfigForm();

	// Buttons
	public: CLFormResult Open( unsigned short options );
};
// -----------------------------------------------------------------------------
// CLSystemDateTimeConfigForm [class]
// =============================================================================

#endif

