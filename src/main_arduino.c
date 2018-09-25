//-----------------------------------------------
// Includes
//-----------------------------------------------
#include "app.h"

int
main( int argc, char ** argv )
{

    DBG( "Initializing the app" );
    app_init();

    DBG( "Starting app mainloop" );
    while (1) {
        app_service();
    }

    DBG( "Can't get here" );
    return 0;
}
