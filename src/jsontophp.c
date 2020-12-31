#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include "phpgenerator.h"

static PyObject *method_jsontophp(PyObject *self, PyObject *args) {
	char *str, *filename = NULL;
	char conversion_result[1000];

	int bytes_copied = -1;

	/*  Parse arguments the Python program receives into local variables*/
	if(!PyArg_ParseTuple(args, "ss", &str, &filename)){
		return NULL;
	}

	//Prevent buffer overflow
	if(strlen(str) < MAX_JSON_CHARACTERS) {
		jsontophp(str, conversion_result);
	} else {
		sprintf(conversion_result, "JSON input is too long, max number of characters is %d", MAX_JSON_CHARACTERS);
	}

	FILE *fp = fopen(filename, "w");
	bytes_copied = fputs(conversion_result, fp);
	fclose(fp);

	return PyLong_FromLong(bytes_copied);
}

static PyMethodDef JsonToPhpMethods[] = {
	{
		"jsontophp",
		method_jsontophp,
		METH_VARARGS,
		"Python interface to convert JSON objects into PHP Objects",

	},
	{
		NULL,
		NULL,
		0,
		NULL
	}
};

static struct PyModuleDef jsontophpmodule = {
	PyModuleDef_HEAD_INIT,
	"jsontophp",
	"Python interface to convert JSON objects into PHP Objects",
	-1,
	JsonToPhpMethods
};

PyMODINIT_FUNC PyInit_jsontophp(void) {
	return PyModule_Create(&jsontophpmodule);
}
