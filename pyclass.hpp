/**
 * @file
 * @author  Roland Siegbert <roland@siegbert.info>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * This class eases embedding of Python in C/C++ by managing the
 * creation and destruction of the Python instance and PyObjects.
 *
 *
 */

#ifndef PYCLASS_HPP
#define PYCLASS_HPP
#pragma once

#include <Python.h>

// Manage Python environment
class CPyInstance
{
	public:
		CPyInstance() {
			Py_Initialize();

			// Add current dir to system path
			PyObject* sysPath = PySys_GetObject((char*)"path");
			PyList_Append(sysPath, PyString_FromString("."));

		}

		~CPyInstance() {
			Py_Finalize();
		}
};


class CPyObject
{
	private:
		PyObject *p;
	public:
		// Lifetime
		CPyObject() : p(NULL) {}

		CPyObject(PyObject* _p) : p(_p) {}

		~CPyObject() {
			if(p) {
				Py_DECREF(p);
			}

			p= NULL;
		}

		PyObject* getObject() {
			return p;
		}

		PyObject* setObject(PyObject* _p) {
			return (p=_p);
		}

		PyObject* AddRef() {
			if(p) {
				Py_INCREF(p);
			}
			return p;
		}

		PyObject* operator ->() {
			return p;
		}

		bool is() {
			return p ? true : false;
		}

		operator PyObject*() {
			return p;
		}

		PyObject* operator = (PyObject* pp) {
			p = pp;
			return p;
		}

		operator bool() {
			return p ? true : false;
		}
};

#endif
