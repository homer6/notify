#ifndef INCLUDE_GUARD_INotifyRecursiveListener
#define INCLUDE_GUARD_INotifyRecursiveListener

#include <sys/inotify.h>
#include <stdlib.h>
#include <unistd.h>

#include <map>

#include "jet/Utf8String.h"
#include "jet/Exception.h"
#include "jet/Directory.h"

#include "INotifyEvent.h"

using namespace jet;
using namespace std;

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
        void addListenersRecursively( int inotify_instance, const Utf8String &full_path );

    protected:
        Utf8String full_path;
        Utf8String command;
        map<int, Utf8String> watch_descriptors;

};

#endif //INCLUDE_GUARD_INotifyRecursiveListener
