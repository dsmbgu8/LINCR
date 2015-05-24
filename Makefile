PROGRAM = cr

SOURCES.c = lincr.c cr.c 
SOURCES.h = lincr.h

SOURCES = $(SOURCES.h) $(SOURCES.c) 

OBJECTS = ${SOURCES.c:.c=.o}

INCLUDES = -I$(UTILDIR)

CC = gcc
CFLAGS += -ansi $(INCLUDES) -ggdb -Wall
CTAGS= ctags -x >tags

all: $(PROGRAM)

$(PROGRAM) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 
	chmod o-rwx $@

clean	:
	$(RM) $(OBJECTS) $(PROGRAM)



