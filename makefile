RM := rm -vf
CC := clang
CFLAGS := -Wall -O3 -std=c17
SOURCE := src/cstring.c src/allocator.c
INCLUDE := -I./src/ -I./include/
OBJECT := $(patsubst src/%, %, $(patsubst %.c, %.o, $(SOURCE)))
BINPATH := ./bin/
PROGNAME := libcstr.a

### rules

all: compile lib clean

compile:
	$(CC) -c $(SOURCE) $(CFLAGS) $(INCLUDE)

lib:
	ar -rc $(BINPATH)$(PROGNAME) $(OBJECT)
	ranlib $(BINPATH)$(PROGNAME)

clean:
	$(RM) $(OBJECT)
