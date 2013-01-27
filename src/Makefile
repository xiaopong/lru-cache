##
## Copyright (C) 2011, xp@renzhi.ca
## All rights reserved.
##

CC=g++
CFLAGS=-g -std=c++11
LIBS=-lboost_system 

SRC= test_lru.cpp

OBJS=$(SRC:.cpp=.o)

# include directories
INCLUDES = -I.

EXE=test_lru

all: $(EXE)

test_lru: test_lru.o
	@echo Linking $<
	@$(CC) $^ $(LIBS) -o $@

.cpp.o:
	@echo Compiling $<
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE) Makefile.bak 
