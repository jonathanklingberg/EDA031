#
# Makefile to make the file libclientserver.a, containing
# connection.o and server.o
#
# Define the compiler. g++ can be
# changed to clang++.
CXX = clang++
CC  = clang++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of libstdc++.
CXXFLAGS =  -g -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
CXXFLAGS += -std=c++11 
#CPPFLAGS =  -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS += -stdlib=libc++

all: libclientserver.a sub-make

# Create the library; ranlib is for Darwin and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: connection.o server.o messagehandler.o clientcommandhandler.o servercommandhandler.o article.o newsgroup.o in_memory.o on_disk.o
	ar rv libclientserver.a  connection.o server.o messagehandler.o clientcommandhandler.o servercommandhandler.o article.o newsgroup.o in_memory.o on_disk.o
	ranlib libclientserver.a 

sub-make:
	$(MAKE) -C test

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o libclientserver.a
	$(MAKE) -C test clean
	#cd test && $(MAKE) clean

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)


