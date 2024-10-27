all: pride
	@

pride: tools/pride.c rgb_to_xterm256.h
	$(CC) -I. -o $@ tools/pride.c

test: pride
	@for test in $(wildcard tests/*.sh); do sh $$test; done

clear:
	rm pride
