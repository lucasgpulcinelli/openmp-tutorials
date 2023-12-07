CFLAGS  += -std=c11 -fopenmp -Wall -Wextra
LDFLAGS += -fopenmp -lm

EXECUTABLE ?= build/main
CFILES      = $(shell find src/ -type f |grep '\.c')
OFILES      = $(patsubst src/%.c,build/obj/%.o, $(CFILES))


.PHONY: all clean run debug


all: $(EXECUTABLE)

clean:
	@rm -f $(ZIPFILE)
	@rm -rf build/

run: $(EXECUTABLE)
	@./$(EXECUTABLE) $(ARGS)

debug: CFLAGS+=-g -O0
debug: clean
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OFILES)
	@mkdir -p build
	$(CC) $(LDFLAGS) -o $@ $^

build/obj/%.o: src/%.c src/%.h
	@mkdir -p build
	@mkdir -p build/obj
	$(CC) $(CFLAGS) -c -o $@ $<

build/obj/%.o: src/%.c
	@mkdir -p build
	@mkdir -p build/obj
	$(CC) $(CFLAGS) -c -o $@ $<

