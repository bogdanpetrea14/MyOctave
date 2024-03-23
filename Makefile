CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS = my_octave

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) my_octave.c -lm -o my_octave
	
clean:
	rm -f $(TARGETS)
