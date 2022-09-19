/**
 * Author : Eric Rasolonjatovo
 * E-mail : mrasolonjatovo.dev@gmail.com
 * displayer based on GLFW
 * it act like a bridge to the python
 **/
#ifndef __DISPLAYER_INCLUDED__
#define __DISPLAYER_INCLUDED__
#include <Python.h>
#include <structmember.h>
#include <string>
#include <string.h>
#include "displayer_native.hpp"


typedef struct Displayer Displayer;

struct Displayer{
    PyObject_HEAD
    int width;
    int height;
    int antialias;
    float* vbo;
    size_t vboSize;
    float* gridVbo;
    size_t gridVboSize;

    std::string vertexShadPath;
    std::string fragmentShadPath;
    
    
};

/**
 * Methods
 * - Displayer.__new__
 * - Displayer.__init__
 * 
 **/
static void Displayer_dealloc(Displayer* self);
static PyObject* Displayer_new(PyTypeObject* type, PyObject* args, PyObject* kwargs);
static int Displayer_init(Displayer* self, PyObject* args, PyObject* kwargs);
static PyObject* Displayer_display(Displayer* self);
static PyObject* Displayer_setCamera(PyObject* args, PyObject* kwargs);
static PyObject* Displayer_setCameraOrtho(PyObject* args, PyObject* kwargs);
static PyObject* Displayer_setVBO(Displayer* self, PyObject* args);
static PyObject* Displayer_getVBO(Displayer* self);
static PyObject* Displayer_setShaders(PyObject* self, PyObject* args, PyObject* kwargs);
static PyObject* Displayer_setGrid(Displayer* self, PyObject* args);// Temp method
/**
 * Registering members
 **/
static PyMemberDef Displayer_members[] = {
  {NULL}
};

/**
 * Methods Registration
 * 
 **/
static  PyMethodDef Displayer_methods[] = {
    {"display", (PyCFunction)Displayer_display, METH_NOARGS, "display the glWindow"},
    {"setvbo", (PyCFunction)Displayer_setVBO, /*METH_O*/ METH_VARARGS, "Load float32 Data to Vertex Object Buffer"},
    {"getvbo", (PyCFunction)Displayer_getVBO, /*METH_O*/ METH_VARARGS, "return the current vbo used <List>"},
    {"setgrid", (PyCFunction)Displayer_setGrid, /*METH_O*/ METH_VARARGS, "allocate a grid use for reference ?"},
    {"setshaderspaths", (PyCFunction)Displayer_setShaders, METH_KEYWORDS|METH_VARARGS, "load shaders programs paths<vertexshader.glsl, fragmentshader.glsl>"},
    {NULL}
};

/**
 * Displayer Finalization
 **/
static PyTypeObject DisplayerType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "displayer.Displayer", // tp_name
    sizeof(Displayer), // tp_basicsize
    0,
    (destructor)Displayer_dealloc, // tp_dealloc
    0, /* tp_print */
    0, /* tp_getattr */
    0, /* tp_setattr */
    0, /* tp_reserved */
    0, /* tp_repr */
    0, /* tp_as_number */
    0, /* tp_as_sequence */
    0, /* tp_as_mapping */
    0, /* tp_hash */
    0, /* tp_call */
    0, /* tp_str */
    0, /* tp_getattro */
    0, /* tp_setattro */
    0, /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "A Displayer based on GLFW", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    Displayer_methods, /* tp_methods */
    Displayer_members, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    (initproc)Displayer_init, /* tp_init */
    0, /* tp_alloc */
    Displayer_new, /* tp_new */
    // tp_name = "displayer.Displayer",
    // tp_basicsize = sizeof(Displayer),
    // tp_dealloc = (destructor)Displayer_dealloc,
    // tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    // tp_doc = "A Displayer based on GLFW",
    // tp_methods = Displayer_methods,
    // tp_members = Displayer_members,
    // tp_init = (initproc)Displayer_init,
    // tp_new = Displayer_new,
};

/**
 * Module methods
 **/
static PyMethodDef displayer_methods[]={
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef displayerModule = {
    PyModuleDef_HEAD_INIT,
    "displayer",
    "displayer using GLFW(openGL3.3.0 core)",
    -1,
    displayer_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};

PyMODINIT_FUNC PyInit_displayer(void);

#endif