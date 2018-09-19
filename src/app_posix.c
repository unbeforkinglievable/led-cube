//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <signal.h>

//-----------------------------------------------
// Local method declarations
//-----------------------------------------------
static void
app_interrupt_handler( int code );

//-----------------------------------------------
// "global"-er method definitions
//-----------------------------------------------
static int16_t
app_platform_init( void )
{
    signal(SIGINT, app_interrupt_handler );
    return 0;
}

//-----------------------------------------------
// Local method definitions
//-----------------------------------------------
static void
app_interrupt_handler( int code )
{
    DBG( "caught ctrl-c.  setting flag to stop the app" );
    g_app.running = 0;
}
