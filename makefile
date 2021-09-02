MAINPROG=vmemman

SOURCES:=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
FLAGS=-fsanitize=address,leak,undefined -Wall -Wextra -fuse-ld=gold -lm

all: $(SOURCES) $(MAINPROG)

$(MAINPROG): $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -o $@

.cpp.o:
	gcc $(FLAGS) -c $< -o $@

tidy:
	rm *.o
clean:
	rm *.o $(MAINPROG)