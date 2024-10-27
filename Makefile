all: pride
	@

pride: tools/pride.cpp rgb_to_xterm256.h
	$(CXX) -std=c++23 -O0 -I. -o $@ tools/pride.cpp

test: pride
	@for test in $(wildcard tests/*.sh); do sh $$test; done

clear:
	rm pride
