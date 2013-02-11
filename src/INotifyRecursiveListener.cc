#include "INotifyRecursiveListener.h"

#include <stdlib.h>
#include <unistd.h>


INotifyRecursiveListener::INotifyRecursiveListener()
    :full_path("")
{


}


INotifyRecursiveListener::INotifyRecursiveListener( Utf8String full_path )
    :full_path(full_path)
{


}



INotifyRecursiveListener::~INotifyRecursiveListener(){


}


void INotifyRecursiveListener::setFullPath( Utf8String full_path ){

    this->full_path = full_path;

}


Utf8String INotifyRecursiveListener::getFullPath(){

    return this->full_path;

}



void INotifyRecursiveListener::setCommand( Utf8String command ){

    this->command = command;

}


Utf8String INotifyRecursiveListener::getCommand(){

    return this->command;

}



void INotifyRecursiveListener::listen(){


    int inotify_instance;
    ssize_t read_result;

    INotifyEvent* current_event;

    char *event_read_buffer;
    char *buffer_iterator;

    const size_t READ_BUFFER_SIZE = 4096;

    event_read_buffer = (char*) malloc( READ_BUFFER_SIZE );


    if( (inotify_instance = inotify_init()) == -1 ){
        free( event_read_buffer );
        throw Exception( "inotify_init()" );
    }


    try{

        this->addListenersRecursively( inotify_instance, this->full_path );

    }catch( Exception *exception ){

        free( event_read_buffer );
        throw exception;

    }catch( Exception exception ){

        free( event_read_buffer );
        throw exception;

    }

    Utf8String command_with_arguments;
    Utf8String full_path;

    /*
    uint32_t listening_mask =
            IN_MODIFY |         // File was modified (*).
            IN_DELETE |         // File/directory deleted from watched directory (*).
            IN_MOVED_TO |       // File moved into watched directory (*).
            IN_MOVED_FROM |     // File moved out of watched directory (*).
            IN_CREATE |         // File/directory created in watched directory (*).
            IN_CLOSE_WRITE      // File opened for writing was closed (*).
    ;
    */

    uint32_t listening_mask = IN_ALL_EVENTS;

    uint32_t create_listener_mask =
            IN_MOVED_TO |       // File moved into watched directory (*).
            IN_CREATE           // File/directory created in watched directory (*).
    ;



    bool continue_listening = true;
    int return_value;

    while( continue_listening ){

        read_result = read( inotify_instance, event_read_buffer, READ_BUFFER_SIZE );

        if( read_result < 1 ){
            free( event_read_buffer );
            throw Exception( "read_result()" );
        }

        //cout << "Read " << read_result << " bytes from inotify fd." << endl;

        buffer_iterator = event_read_buffer;

        do{

            //cout << "Event: ";

            current_event = (INotifyEvent*) buffer_iterator;


            full_path = this->watch_descriptors[ current_event->wd ];
            full_path += "/" + current_event->getFilename();


            //Add new listeners to new directories
            if( current_event->mask & create_listener_mask ){

                if( Directory::isDirectory(full_path) ){
                    this->addListenersRecursively( inotify_instance, full_path );
                }

            }

            //Show all events
            //cout << current_event->getDescription() + " " + full_path << endl;


            //Invoke the script if it matches the listening mask
            if( current_event->mask & listening_mask ){

                command_with_arguments = this->command + " " + current_event->getDescription() + " " + full_path.escapeShellArgument();

                return_value = system( command_with_arguments.getCString() );

                //print_as_hex( cout, command_with_arguments );

                //cout << command_with_arguments << endl;

            }

            buffer_iterator += current_event->getSize();

        }while( buffer_iterator < event_read_buffer + read_result );


    }


    free( event_read_buffer );


}



void INotifyRecursiveListener::addListenersRecursively( int inotify_instance, const Utf8String &full_path ){

    if( Directory::isDirectory(full_path) ){

        Directory dir( full_path );

        if( dir.getName() == "." || dir.getName() == ".." ){
            //skip these directories
            return;
        }

        int watch_descriptor;

        if( (watch_descriptor = inotify_add_watch(inotify_instance, full_path.getCString(), IN_ALL_EVENTS)) == -1 ){
            throw Exception( "inotify_add_watch(): " + full_path );
        }

        this->watch_descriptors[ watch_descriptor ] = full_path;

        cout << "Watching: " << full_path << endl;

        vector<Directory*> *subdirectories = dir.getDirectories();
        vector<Directory*>::iterator dir_it;
        Directory *current_directory;

        for( dir_it = subdirectories->begin(); dir_it != subdirectories->end(); dir_it++ ){

            current_directory = *dir_it;

            this->addListenersRecursively( inotify_instance, current_directory->getFullPath() );

            delete current_directory;

        }

        delete subdirectories;


    }else{

        throw Exception( Utf8String(full_path) + " must be a directory." );

    }

}

