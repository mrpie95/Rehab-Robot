#include "speechrecogwrapper.h"

SpeechRecogWrapper::SpeechRecogWrapper()
{
    printf("Python Wrapper\n");
    Py_Initialize();
    printf("Initialized...\n");

//    PyObject *sysPath = PySys_GetObject("path");
//    PyObject *programName = PyString_FromString("/home/nao/Test/SpeechRecog/");
//    PyList_Append(sysPath, programName);
//    Py_DecRef(programName);

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\"/home/nao/Test/SpeechRecog/\")");
//    PyRun_SimpleString("sys.path.append(\"/usr/lib/python2.7/dist-packages/twisted/logger\")");
//    PyRun_SimpleString("import _collections");
//    PyRun_SimpleString("import google_transcribe");

    pName = PyString_FromString("google_transcribe");
    pModule = PyImport_Import(pName);
    if (pModule == NULL) {
        printf("Python module cannot be found\n");
        PyErr_Print();
        return;
    } else {
        printf("Python module found\n");
    }
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, "call_transcribe");
    if (!PyCallable_Check(pFunc)) {
        printf("Function is not callable!\n");
        return;
    }

}

char* SpeechRecogWrapper::transcribe(std::string filename)
{
    printf("Transcribing...\n");
    pArg = PyTuple_New(1);
    PyTuple_SetItem(pArg, 0, PyString_FromString(filename.c_str()));

    if (PyCallable_Check(pFunc)) {
        pResult = PyObject_CallObject(pFunc, pArg);
        if (pResult != NULL) {
            char* result;

            result = PyString_AsString(pResult);

            if (result == nullptr) {
                printf("Transcription result is empty\n");
                return "";
            }

            printf("Trascription done\n");
            printf("Transcriber: %s\n", result);
            return result;
        }
        else {
            printf("Result is null\n");
        }
    }


    return "No respond from trasncriber...";
}

