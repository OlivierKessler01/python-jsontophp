# python-jsontophp

This is a pratice CPython extension developmment.
This Python extension provides interface to functions that convert JSON objects to useless PHP objects.

## Running it in a Docker container
```sh
docker-compose up -d
docker exec -it python_jsontophp_1 /bin/sh
cd src/
python3 setup.py install
```
### Or if you prefer, using gcc to compile
```sh
CC=gcc python3 setup.py install
```

## Usage
```sh
python3
>>> import jsontophp
>>> jsontophp.jsontophp({"class" : "WhateverClassName", "methods" : [ "method1", "method2"], "members" ["member1", "member2", "member3"]}, "output/write.php")
```

## Testing 
I'm running tests on a dynamic library (.so file) (compiled from the .c file) in Linux using python and python's unit-testing library unittest located in tests/.

## Compile locally
Run :
```sh
make clean
make
```
Generate Assembly code (.asm file generated in the src/ folder):
```sh
make clean
make generate_assembly
```

