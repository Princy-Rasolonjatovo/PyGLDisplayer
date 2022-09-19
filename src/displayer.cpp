#include <Python.h>
#include "displayer.hpp"
#include "shader.hpp"
#include "handlers_keyboard_mouse.hpp"
#include "viewport.hpp"
#include <vector>



static void
Displayer_dealloc(Displayer* self){
    //disp_deallocAllAndTerminate();
    free(self->vbo);
    free(self->gridVbo);
    Py_TYPE(self)->tp_free((PyObject*) self);

}


// Displayer.__new__(base, *args, **kwargs)
static PyObject* 
Displayer_new(PyTypeObject* type, PyObject* args, PyObject* kwargs){
    Displayer* self;
    self = (Displayer*)type->tp_alloc(type, 0);
    if (self != NULL){
        self->width = 0;
        self->height = 0;
        self->antialias = 4;
        //self->glWindow = NULL;
        self->vbo = NULL;
        self->vboSize = 0;
    }

    return (PyObject*) self;
}


// Displayer.__init__(self, *args, **kwargs)
static int
Displayer_init(Displayer* self, PyObject* args, PyObject* kwargs){
    static char* keywords_list[] = {"width", "height", "antialias", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii", keywords_list, &self->width, &self->height, &self->antialias)){
        return -1;
    }
    // [NB] Antialias max value 4x

    return 0;
}


static PyObject* 
Displayer_display(Displayer* self){
    int ERROR_CODE;
    // Py_BEGIN_ALLOW_THREADS
    
    // ERROR_CODE = disp_initConfigureWindow(
    //     self->glWindow, self->width, self->height, self->antialias);
    // switch (ERROR_CODE)
    // {
    // case GLFW_INIT_ERROR:
    //     return PyErr_Format(PyExc_Exception, "[GLFWErr] Cannot initialize GLFW\nIntel GPU are not 3.3 compatible", NULL);
    //     break;
    // case GLFW_WINDOW_CREATE_ERROR:
    //     return PyErr_Format(PyExc_Exception, "[GLFWErr] Cannot create Window of size (%d, %d)", self->width, self->height);
    //     break;
    // case GLEW_INIT_FAILED:
    //     return PyErr_Format(PyExc_Exception, "[GLEWErr] Cannot initialize GLEW", NULL);
    //     break;
    // default:
    //     break;
    // }
    // Displayer

    if (!glfwInit())
        return PyErr_Format(PyExc_Exception, "[GLFWErr] Cannot initialize GLFW\n\tIntel GPU are not 3.3 compatible", NULL);

    glfwWindowHint(GLFW_SAMPLES, self->antialias);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    
    GLFWwindow* glWindow = NULL;
    glWindow = glfwCreateWindow(self->width, self->height, "GLWindow", NULL, NULL);
    if (glWindow == NULL){
        return PyErr_Format(PyExc_Exception, "[GLFWErr] Cannot create Window of size (%d, %d)", self->width, self->height);
    }

    manage_keyboard_mouse(glWindow);

    glfwMakeContextCurrent(glWindow);
    glewExperimental = true;
    glewInit();
    glfwSetInputMode(glWindow, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(.21f, .22f, .23f, 1.0f);

    // Tests
    GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

    LOADSHADER_RET ret = loadShaders(self->vertexShadPath.c_str(), self->fragmentShadPath.c_str());
    if (ret.has_err){
        glfwTerminate();
        return PyErr_Format(PyExc_Exception, "%s\n", ret.ERR);
    }
    GLuint glProgramId = ret.programID;

    // GLuint matrixID = glGetUniformLocation(self->shader_programId, "MVP");
    GLuint matrixID = glGetUniformLocation(glProgramId, "MVP");

    printf("[DumyDebug] Shader_programId : %u \n", glProgramId);

    viewport_vars::Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	viewport_vars::View       = glm::lookAt(
								glm::vec3(0, .5, 5), // eye (Position of the camera)
								glm::vec3(0, 0, 0), // center (Position where the camera is looking at)
								glm::vec3(0, 1, 0)  // up (normalize vector)
						   );
    
    

    glm::quat gOrientation;
    glm::vec3 gOrientation1;
    //glm::mat4 rotationMatrix = glm::eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z);
    viewport_vars::cameraPosition = glm::vec3(0, 0.5, 5);
    // Camera rotation
    // rotate_camera(viewport_vars::rotationAngle, glm::vec3(0, 1, 0), viewport_vars::cameraPosition);
    // viewport_vars::View = glm::lookAt(
    //     viewport_vars::cameraPosition,
    //     viewport_vars::cameraEyeLook,
    //     viewport_vars::cameraVecNormal
    // );
    viewport_vars::MVP = viewport_vars::Projection * viewport_vars::View * viewport_vars::Model;
    
    
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, self->vboSize * sizeof(GLfloat), &self->vbo[0], GL_STATIC_DRAW);

    // End Tests
    // Tokony refa misy Event vo manao update fa anjary minana res be
    // Le Event resahako ohatra: EventTransform(scale, rotate, translate), ...
    // manao IDLE refa tsis nin nin (mode Listening)
    glm::mat4 _View = glm::lookAt(
        glm::vec3(0, .5, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    do{
        // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear( GL_COLOR_BUFFER_BIT);
        glUseProgram(glProgramId);

        glm::vec3 _camerapos(0, .5, 3);
        gOrientation1.y = gOrientation1.y > glm::radians(360.0f) ?  0: gOrientation1.y + glm::radians(1.0f);
        // GL Test
        glm::mat4 _Model = glm::eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z) * glm::mat4(1.0f);
        // viewport_vars::rotationAngle++;
        // viewport_vars::rotationAngle = viewport_vars::rotationAngle > 360 ? 0 : viewport_vars::rotationAngle;
        // rotate_camera(viewport_vars::rotationAngle, glm::vec3(0, 1, 0), _camerapos);
        
        //glm::mat4 _MVP = viewport_vars::Projection * viewport_vars::View * viewport_vars::Model;



        glm::mat4 _Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        glm::mat4 _MVP = _Projection * _View * _Model;
        
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &_MVP[0][0]);
        

        // 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, self->vboSize);
        // glDrawArrays(GL_POINTS, 0, self->vboSize);
        // DRAW_MODE  = GL_TRIANGLES | GL_POINTS | GL_QUADS | GL_LINES_ADJACENCY; // options
		glDisableVertexAttribArray(0);

        // End GL Test

        glfwSwapBuffers(glWindow);
        // glfwPollEvents();
        glfwWaitEvents();
    }while (
        glfwGetKey(glWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
        glfwWindowShouldClose(glWindow) == 0
    );

    // Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(glProgramId);
	glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();
    // Py_END_ALLOW_THREADS
    Py_RETURN_NONE;
}

/**
 * Load float32 Data to Vertex Object Buffer
 * - no vbo indexing
 **/
static PyObject* Displayer_setVBO(Displayer* self, PyObject* args){
    PyObject* in_vbo;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &in_vbo)){
        return PyErr_Format(PyExc_TypeError, "expected type <List>", NULL);
    }
    Py_ssize_t vboSize = PyList_Size(in_vbo);
    if (!(vboSize % 3 == 0)){
        return PyErr_Format(PyExc_Exception, "[VBOInputError] cannot use non triangle based data. check(list.size % 3 == 0)!", NULL);
    }
    if (self->vbo != NULL){
        // Clear actual data
        free(self->vbo);
        self->vbo = NULL;
        self->vboSize = 0;
    }
    self->vbo = (float*)calloc((size_t)vboSize, sizeof(float));
    if (self->vbo == NULL){
        return PyErr_Format(PyExc_Exception, "[MemoryError] cannot allocate anymore. please free some memory by closing applications", NULL);
    }
    for(Py_ssize_t i =0; i < vboSize; i++){
        float val;
        PyObject* pyval = PyList_GetItem(in_vbo, i);
        PyArg_Parse(pyval, "f", &val);
        *(self->vbo + i) = val;
    }
    self->vboSize = vboSize;
    Py_RETURN_NONE;
}


static PyObject* Displayer_getVBO(Displayer* self){
    PyObject* list = NULL;
    list = PyList_New(0);
    if (list == NULL){
        return PyErr_Format(PyExc_Exception, "[RuntimeError] cannot create list in method: Displayer_getVBO", NULL);
    }
    for (size_t i = 0; i < self->vboSize; i++){
        PyList_Append(list, Py_BuildValue("f", *(self->vbo + i)));
    }
    return list;
}


static PyObject* 
Displayer_setShaders(PyObject* self, PyObject* args, PyObject* kwargs){
    const char *c_vertexShadPath, *c_fragmentShadPath;
    static char* keywords_list[] = {"vertexShaderPath", "fragmentShaderPath", NULL};

    if(!PyArg_ParseTupleAndKeywords(args, kwargs, "ss", 
        keywords_list, 
        &c_vertexShadPath, 
        &c_fragmentShadPath)){
        return PyErr_Format(PyExc_Exception, "[ArgumentError] expected <str> for paths", NULL);
    }

    Displayer* d_self = (Displayer*) self;
    d_self->vertexShadPath = std::string(c_vertexShadPath);
    d_self->fragmentShadPath = std::string(c_fragmentShadPath);
    
    Py_RETURN_NONE;
}


PyMODINIT_FUNC PyInit_displayer(void){
    PyObject* m;
    if (PyType_Ready(&DisplayerType) < 0)
        return NULL;
    m  = PyModule_Create(&displayerModule);
    if (m == NULL)
        return NULL;
    Py_INCREF(&DisplayerType);
    PyModule_AddObject(m, "Displayer", (PyObject*) &DisplayerType);
    return m;
}


static PyObject* 
Displayer_setGrid(Displayer* self, PyObject* args){
    PyObject* in_vbo;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &in_vbo)){
        return PyErr_Format(PyExc_TypeError, "expected type <List>", NULL);
    }
    Py_ssize_t vboSize = PyList_Size(in_vbo);
    if (!(vboSize % 3 == 0)){
        return PyErr_Format(PyExc_Exception, "[VBOInputError] cannot use non triangle based data. check(list.size % 3 == 0)!", NULL);
    }
    if (self->vbo != NULL){
        // Clear actual data
        free(self->gridVbo);
        self->gridVbo = NULL;
        self->gridVboSize = 0;
    }
    self->gridVbo = (float*)calloc((size_t)vboSize, sizeof(float));
    if (self->gridVbo == NULL){
        return PyErr_Format(PyExc_Exception, "[MemoryError] cannot allocate anymore. please free some memory by closing applications", NULL);
    }
    for(Py_ssize_t i =0; i < vboSize; i++){
        float val;
        PyObject* pyval = PyList_GetItem(in_vbo, i);
        PyArg_Parse(pyval, "f", &val);
        *(self->gridVbo + i) = val;
    }
    self->gridVboSize = vboSize;
    Py_RETURN_NONE;
}