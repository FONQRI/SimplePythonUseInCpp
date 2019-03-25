#include <Python.h>
#include <iostream>

int sym_ex(const char *input_expression, const char *output_expression)
{

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	const char *file = "sympy";
	const char *function = "simplify";

	Py_Initialize();
	// PyRun_SimpleString("from sympy import *\n");
	pName = PyUnicode_FromString(file);
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, function);
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc))
		{

			pArgs = PyTuple_New(1);
			pValue = PyUnicode_FromString(input_expression);
			printf("the string passed %s\n", input_expression);
			if (!pValue)
			{
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				fprintf(stderr, "Cannot convert argument\n");
				return 1;
			}
			/* pValue reference stolen here: */
			PyTuple_SetItem(pArgs, 0, pValue);

			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				std::clog << PyLong_AsLong(pValue) << std::endl;

				Py_DECREF(pValue);
			}
			else
			{
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 1;
			}
		}
		else
		{
			if (PyErr_Occurred()) PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", function);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else
	{
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", file);
		return 1;
	}
	Py_Finalize();
	return 0;
}

int main(int argc, char *argv[])
{
	wchar_t *name = L"ProgramName";
	Py_SetProgramName(name); /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");
	PyRun_SimpleString("print(sys.version)");
	Py_Finalize();

	/// uncomment if you want to test importing sympy
	/// Note for running this code you need to install sympy in python that
	/// library is using you can get that version by running top code

	// *************************************** using sympy
	//	char *input_expression = "2 + 2";
	//	char *output_expression = new char[250];
	//	sym_ex(input_expression, output_expression);

	return 0;
}
