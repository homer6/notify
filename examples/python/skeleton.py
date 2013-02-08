#!/usr/bin/env python
import argparse

parser = argparse.ArgumentParser( description = 'Listener Handler' )
parser.add_argument( 'event_types' )
parser.add_argument( 'filename' )
arg_parser = parser.parse_args()

filename = arg_parser.filename
event_types = arg_parser.event_types

def show_usage():
    print "skeleton.py [event_types] [filename]"


def show_error_message( error_message ):
    print error_message
    exit()

event_types_list = event_types.split( '-' )
del event_types_list[ -1 ]
event_types_set = set(event_types_list)
	
log_file = open( 'events.log', 'a' )

log_file.write( "-------------------------------------------------------\n" )
log_file.write( "Event Types: " + repr(event_types_set) + "\n" )
log_file.write( "Filename: " + str(filename) + "\n" )

log_file.close()




