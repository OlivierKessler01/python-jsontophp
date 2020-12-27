#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include "phpgenerator.h"

void jsontophp(char *json, size_t size_json, char *result);

static PyObject *method_jsontophp(PyObject *self, PyObject *args) {
	char *str, *filename = NULL;
	char *conversion_result;
	conversion_result = (char*)malloc(sizeof(char));

	int bytes_copied = -1;

	/*  Parse arguments the Python program receives into local variables*/
	if(!PyArg_ParseTuple(args, "ss", &str, &filename)){
		return NULL;
	}

	jsontophp(str, sizeof(str), conversion_result);

	FILE *fp = fopen(filename, "w");
	bytes_copied = fputs(conversion_result, fp);
	fclose(fp);
	free(conversion_result);

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
