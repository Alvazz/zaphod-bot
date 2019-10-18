#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
status_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_red( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_red_toggle( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_yellow( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_yellow_toggle( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_green( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_green_toggle( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_external( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_external_toggle( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_external_override( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_external_resume( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* STATUS_H */
