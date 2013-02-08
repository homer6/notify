#include "INotifyRecursiveListener.h"



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


    int inotify_instance, watch_descriptor;
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

    cout << "About to watch: " << this->full_path << endl;


    if( (watch_descriptor = inotify_add_watch( inotify_instance, this->full_path.getCString(), IN_ALL_EVENTS)) == -1 ){
        free( event_read_buffer );
        throw Exception( "inotify_add_watch()" );
    }
    cout << "Watching: " << this->full_path << endl;



    bool continue_listening = true;

    while( continue_listening ){

        read_result = read( inotify_instance, event_read_buffer, READ_BUFFER_SIZE );

        if( read_result < 1 ){
            free( event_read_buffer );
            throw Exception( "inotify_add_watch()" );
        }

        cout << "Read " << read_result << " bytes from inotify fd." << endl;

        buffer_iterator = event_read_buffer;

        do{

            cout << "Event: ";

            current_event = (INotifyEvent*) buffer_iterator;

            cout << current_event->getDescription() << endl;

            buffer_iterator += current_event->getSize();

        }while( buffer_iterator < event_read_buffer + read_result );


    }


    free( event_read_buffer );


}
