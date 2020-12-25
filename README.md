# python-jsontophp

This Python extension provides interface to functions that convert JSON objects to PHP objects.

#To install the extension on yoyr machine : 
python3 setup.py install
#Or if you prefer, using gcc to compile
CC=gcc python3 setup.py install
#Or, isolated in a Docker contianer
docker-compose up -d
docker exec -it python_jsontophp_1 /bin/sh
python3 setup.py install


#usage
>>> import jsontophp
>>> jsontophp.jsontophp({"title" : "jsonObject"}, "write.php")
