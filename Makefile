CFLAGS ?= -O3 -flto -march=native -Wno-unused-result

all: libaldr.a sample.out
	mkdir -p build/bin
	cp sample.out build/bin/aldr
	mkdir -p build/lib
	cp libaldr.a build/lib
	mkdir -p build/include
	cp *.h build/include
	$(MAKE) clean

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

libaldr.a: flip.o aldr.o
	ar rcs $@ $^

%.out: %.c libaldr.a
	gcc $(CFLAGS) -o $@ $^ -lm

.PHONY: clean
clean:
	rm -rf *.a *.o *.out
