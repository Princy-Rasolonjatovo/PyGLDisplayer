#ifndef SHADER_HPP
#define SHADER_HPP

#define SHADERERR_VERTEXSHADER_FILENOTFOUND 512
#define SHADERERR_FRAGMENTSHADER_FILENOTFOUND 512 >> 1
#define SHADERERR_VERTEXSHADER_EXCEPTION 512 >> 2
#define SHADERERR_FRAGMENTSHADER_EXCEPTION 512 >> 3

typedef struct LOADSHADER_RET LOADSHADER_RET;

struct LOADSHADER_RET{
    GLuint programID;
    bool has_err;
    const char* ERR;
    unsigned int ERR_FLAGS;
};

LOADSHADER_RET loadShaders(const char* vertex_file_path,const char* fragment_file_path);

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path, int alien);
#endif
