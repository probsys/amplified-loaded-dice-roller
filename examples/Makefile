all: example.out

CFLAGS ?= -O3 -flto -march=native

%.out: %.c
	gcc -o $@ $(CFLAGS) \
		-I ../build/include \
		-L ../build/lib \
		$^ -laldr -lm

.PHONY: clean
clean:
	rm -rf *.out
