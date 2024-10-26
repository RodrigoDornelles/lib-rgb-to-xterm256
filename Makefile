all: pride
	@

pride: tools/pride.c rgb_to_xterm256.h
	$(CC) -I. -o $@ tools/pride.c

test: pride
	./tests/*.sh

clear:
	rm pride
