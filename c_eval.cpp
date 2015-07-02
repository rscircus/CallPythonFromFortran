/**
 * @file
 * @author  Roland Siegbert <siegbert@cats.rwth-aachen.de>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * This class eases embedding of Python in C/C++ by managing the
 * creation and destruction of the Python instance and PyObjects.
 *
 */

#include <stdio.h>
#include <Python.h>
#include "pyclass.hpp"

extern struct
{
   double rValue;
} rValue_;

extern "C" int c_eval()
{
  printf("c_eval_pyFunction: Calling Python to evaluate pyFunction\n");

  // Rydberg constant in eV for now
  rValue_.rValue = 13.605692533;

  // Load the Python Environment:
  CPyInstance Instance;
  CPyObject pArgs, pValue;

  // Let Python find modules in the current directory:
  CPyObject sysPath = PySys_GetObject((char*)"path");
  PyList_Append(sysPath, PyString_FromString("."));

  // Load the module:
  CPyObject pName = PyUnicode_FromString("evaluate");
  CPyObject pModule = PyImport_Import(pName);

  // Call module & catch errors
  if(pModule) {
    CPyObject pFunc = PyObject_GetAttrString(pModule, "pyFunction");

    if(pFunc && PyCallable_Check(pFunc)) {
      CPyObject prValue = PyObject_CallObject(pFunc, NULL);

      rValue_.rValue = PyFloat_AsDouble(prValue);
      printf("c_eval_pyFunction: Python returned with = %g\n", rValue_.rValue);

    } else {
      printf("ERROR: In Python function call");
    }

  } else {
    printf("ERROR: Module not imported\n");
  }

  return(0);
}
