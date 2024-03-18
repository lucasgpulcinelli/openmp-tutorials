CFLAGS  += -std=c11 -fopenmp -Wall -Wextra
LDFLAGS += -fopenmp -lm

PROJECT ?= main
EXECUTABLE = build/$(PROJECT)

.PHONY: all clean run debug $(PROJECT)


all: $(EXECUTABLE)

clean:
	@rm -f $(ZIPFILE)
	@rm -rf build/

run: $(EXECUTABLE)
	@./$(EXECUTABLE) $(ARGS)

debug: CFLAGS+=-g -O0
debug: clean
debug: $(EXECUTABLE)

$(EXECUTABLE): build/obj/$(PROJECT).o
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

