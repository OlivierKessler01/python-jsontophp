CC = gcc
CFLAGS = -Wall 
PY_FLAGS = $(shell python3-config --cflags) $(shell python3-config --ldflags)

DEPS = src/phpgenerator.c

src/jsontophp.so: src/jsontophp.o
	$(CC) --shared $(PY_FLAGS) src/jsontophp.o -o src/jsontophp.so

src/jsontophp.o: src/jsontophp.c $(DEPS)
	$(CC) $(CFLAGS) $(PY_FLAGS) -c -o $@ $<

clean:
	sudo rm -rf src/*.so src/*.o src/*.asm src/build/*

generate_assembly:
	$(CC) -S $(CFLAGS) $(PY_FLAGS) -c -o src/jsontophp.asm src/jsontophp.c
	

