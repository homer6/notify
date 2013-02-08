#include "INotifyEvent.h"



INotifyEvent::INotifyEvent(){



}



INotifyEvent::~INotifyEvent(){


}



uint32_t INotifyEvent::getSize() const{

    return sizeof( struct inotify_event ) + len;

}

Utf8String INotifyEvent::getDescription() const{

    Utf8String result;
    Utf8String filename( this->name );

    if( this->mask & IN_ACCESS ) result += "IN_ACCESS-";
    if( this->mask & IN_ATTRIB ) result += "IN_ATTRIB-";
    if( this->mask & IN_CLOSE_WRITE ) result += "IN_CLOSE_WRITE-";
    if( this->mask & IN_CLOSE_NOWRITE ) result += "IN_CLOSE_NOWRITE-";
    if( this->mask & IN_CREATE ) result += "IN_CREATE-";
    if( this->mask & IN_DELETE ) result += "IN_DELETE-";
    if( this->mask & IN_DELETE_SELF ) result += "IN_DELETE_SELF-";
    if( this->mask & IN_MODIFY ) result += "IN_MODIFY-";
    if( this->mask & IN_MOVE_SELF ) result += "IN_MOVE_SELF-";
    if( this->mask & IN_MOVED_FROM ) result += "IN_MOVED_FROM-";
    if( this->mask & IN_MOVED_TO ) result += "IN_MOVED_TO-";
    if( this->mask & IN_OPEN ) result += "IN_OPEN-";
    //if( this->mask & IN_ALL_EVENTS ) result += "IN_ALL_EVENTS-";
    if( this->mask & IN_MOVE ) result += "IN_MOVE-";
    if( this->mask & IN_CLOSE ) result += "IN_CLOSE-";

    result += " " + filename.escapeShellArgument();

    return result;

}



