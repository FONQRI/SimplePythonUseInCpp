#include <Python.h>

int main(int argc, char *argv[])
{
	wchar_t *name = L"shangoll";
	Py_SetProgramName(name); /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("print ('shangoll')");
	Py_Finalize();
	return 0;
}
