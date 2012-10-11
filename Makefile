CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
#OBJS   = main.o 
prog = "build/gamey"
CC = gcc
sources = $(wildcard src/*.c)
objects = $(patsubst %.c,%.o,$(sources))
builds = $(patsubst src/%.o,build/%.o,$(objects))
includes = $(wildcard include/*.h)

all: $(prog)
	rm build/*

# target, uses rules
$(prog): $(builds) $(include)
	echo "Objects: ${builds}"
	$(CC) ${builds} -o ${prog} $(LFLAGS)
	cp build/gamey gamey

# src/main.c 


# rule for building objects
build/%.o : src/%.c
	$(CC) -I./include -c $^ -o $@

# clean up the program
clean :
	rm build/*
	#rm gamey

build : $(builds) $(include)
	# build only
	echo "Objects: ${builds}"
	$(CC) $(LFLAGS) ${builds} -o ${prog}
	cp build/gamey gamey

# here I would like to clean and then build since we getting subtle errors
super :
	
