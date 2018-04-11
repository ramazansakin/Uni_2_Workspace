#########################################################################
#  BIL 244 System Programming LECTURE 01 Hands on the System            #
#  partly from the examples of "Advanced Linux Programming" Book        #
#  EZ: is my initials 2012                                              #
# another Makefile example, this one is much nicer                      #
#########################################################################

OBJECTS		= main.o operations.o
LIBRARIES	=
PROGRAMS	= main

.PHONY:         all clean

# Default target: build everything. 
# !!! Normally  the order is obj libraries then programs but gcc 4.6 on ubuntu wants it this way  !!!
all:            $(OBJECTS) $(PROGRAMS) $(LIBRARIES)

# Clean up build products.
clean:
	rm -f *.o $(LIBRARIES) $(PROGRAMS)

# Additional dependencies.
main:		main.o  operations.o
