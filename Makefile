CXX = gcc
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

LDFLAGS = -std=c11 -O3 -Wall -Werror -Wextra
OSFLAGS = -lpthread

kbdfrq: $(obj)
	@mkdir -p bin
	$(CXX) -o bin/$@ $^ $(LDFLAGS) $(OSFLAGS)

install:
	@cp bin/kbdfrq /usr/local/bin/kbdfrq

uninstall:
	@rm /usr/local/bin/kbdfrq

clean:
	rm $(obj)
