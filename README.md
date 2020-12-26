# python-jsontophp

This is a pratice CPython extension developmment.
This Python extension provides interface to functions that convert JSON objects to useless PHP objects.

## Running it in a Docker container
```sh
docker-compose up -d
docker exec -it python_jsontophp_1 /bin/sh
cd src/
python3 src/setup.py install
```
### Or if you prefer, using gcc to compile
```sh
CC=gcc python3 src/setup.py install
```

## Usage
```sh
python3
>>> import jsontophp
>>> jsontophp.jsontophp({"title" : "jsonObject"}, "output/write.php")
```

## Testing 
I'm running tests on a dynamic library (.so file) (compiled from the .c file) in Linux using python and python's unit-testing library unittest located in tests/.




