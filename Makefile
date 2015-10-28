# edit this makefile so that running make compiles your enigma program
CC = g++
CFLAGS = -Wall -std=c++11
SRCDIR = src
#JUNK := $(COMPONENT_DIR)/junk
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = compiler

all : $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

#pull the depenecies for the existing object files
-include $(OBJS:.o=.d)

$(SRCDIR)%.o: $(SRCDIR)%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

clean:
	rm -rf enigma *.o *.d

srcs:
	echo $(SRCS)

.PHONY: all clean srcs
