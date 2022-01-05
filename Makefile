#Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.o apply.o crop.o exit.o load.o rotate.o save.o select.o utils.o
	$(CC) $(CFLAGS) image_editor.o apply.o crop.o exit.o load.o rotate.o save.o select.o utils.o -o image_editor

image_editor.o: image_editor.c image_editor.h
	$(CC) $(CFLAGS) -c image_editor.c

apply.o: apply.c image_editor.h
	$(CC) $(CFLAGS) -c apply.c

crop.o: crop.c image_editor.h
	$(CC) $(CFLAGS) -c crop.c

exit.o: exit.c image_editor.h
	$(CC) $(CFLAGS) -c exit.c

load.o: load.c image_editor.h
	$(CC) $(CFLAGS) -c load.c

rotate.o: rotate.c image_editor.h
	$(CC) $(CFLAGS) -c rotate.c

save.o: save.c image_editor.h
	$(CC) $(CFLAGS) -c save.c

select.o: select.c image_editor.h
	$(CC) $(CFLAGS) -c select.c

utils.o: utils.c image_editor.h
	$(CC) $(CFLAGS) -c utils.c

pack:
	zip -FSr 311CA_VladNegoita_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
