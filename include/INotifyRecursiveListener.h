#ifndef INCLUDE_GUARD_INotifyRecursiveListener
#define INCLUDE_GUARD_INotifyRecursiveListener

#include <sys/inotify.h>
#include <stdlib.h>
#include <unistd.h>

#include "jet/Utf8String.h"
#include "jet/Exception.h"

#include "INotifyEvent.h"

using namespace jet;

class INotifyRecursiveListener{

    public:
        INotifyRecursiveListener();
        INotifyRecursiveListener( Utf8String full_path );
        ~INotifyRecursiveListener();

        void setFullPath( Utf8String full_path );
        Utf8String getFullPath();

        void setCommand( Utf8String command );
        Utf8String getCommand();

        void listen();

    protected:
        Utf8String full_path;
        Utf8String command;

};

#endif //INCLUDE_GUARD_INotifyRecursiveListener
