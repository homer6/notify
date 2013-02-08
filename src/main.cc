
#include <iostream>
#include <sys/inotify.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "jet/Directory.h"
#include "jet/Exception.h"
#include "jet/Utf8String.h"

#include "INotifyEvent.h"
#include "INotifyRecursiveListener.h"



using namespace std;
using namespace jet;


void error( Utf8String message ){

    cout << "Error: " << message << endl;

}


void display_usage(){

    cout << "usage: notify <command-file-to-invoke> [<directory-to-listen-recursively>]" << endl;
    cout << "Defaults to the current directory." << endl;

}



int main( int argc, char** argv ){

    try{

        if( argc < 2 ){
            display_usage();
            return 1;
        }

        INotifyRecursiveListener *directory_listener = new INotifyRecursiveListener();

        Utf8String command( argv[1] );
        Utf8String full_path;
        if( argc > 2 ){
            full_path += Utf8String( argv[2] );
        }
        Directory directory( full_path );

        directory_listener->setFullPath( directory.getFullPath() );
        directory_listener->setCommand( command );
        directory_listener->listen();

        delete directory_listener;


    }catch( Exception e ){

        error( e.message );

    }catch( Exception *e ){

        error( e->message );

    };

    return 0;

}
