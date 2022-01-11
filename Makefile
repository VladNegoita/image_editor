#Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

#define dependencies
DEPS=image_editor.h utils.h

#define object-files
OBJ=image_editor.o apply.o crop.o exit.o load.o rotate.o save.o select.o utils.o

build: $(TARGETS)

image_editor: $(OBJ)
	$(CC) $(CFLAGS) *.o -o image_editor

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_VladNegoita_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
