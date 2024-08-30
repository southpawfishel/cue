CC=clang
CFLAGS=-Wall -Wextra -Werror -Wno-gnu-anonymous-struct -Wno-nested-anon-types -std=c11
DEPS = cue.h list.h
OBJ = cue.o list.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cue: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
