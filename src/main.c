//-----------------------------------------------
// Includes
//-----------------------------------------------
#include "app.h"

//-----------------------------------------------
// Main
//-----------------------------------------------
int
main( int argc, char ** argv )
{

    DBG( "Initializing the app" );
    app_init();

    DBG( "Starting app mainloop" );
    while (app_is_running()) {
        app_service();
    }

    DBG( "Cleaning up the app" );
    app_cleanup();

    DBG( "Goodbye" );
    return 0;
}
