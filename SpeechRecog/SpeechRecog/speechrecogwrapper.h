#ifndef SPEECHRECOGWRAPPER_H
#define SPEECHRECOGWRAPPER_H

#include <Python.h>
#include <string>

// Note: https://github.com/pypa/virtualenv/issues/410
// Soft linking if initalize error
class SpeechRecogWrapper
{
private:
    PyObject *pName, *pModule, *pDict, *pFunc, *pValue;

    PyObject *pArg, *pResult;


public:
    SpeechRecogWrapper();

    char* transcribe(std::string filename);
};

#endif // SPEECHRECOGWRAPPER_H
