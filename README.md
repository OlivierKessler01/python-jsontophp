# python-jsontophp

This is a pratice CPython extension developmment.
This Python extension provides interface to functions that convert JSON objects to useless PHP objects.

## Installing the extension on your machine : 
```sh
python3 setup.py install
```
### Or if you prefer, using gcc to compile
```sh
CC=gcc python3 setup.py install
```
## Docker container
You can also use the Docker to run it
```sh
docker-compose up -d
docker exec -it python_jsontophp_1 /bin/sh
python3 setup.py install
```

## Usage
```sh
>>> import jsontophp
>>> jsontophp.jsontophp({"title" : "jsonObject"}, "write.php")
```



