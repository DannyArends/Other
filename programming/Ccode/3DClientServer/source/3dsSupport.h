#include "includes.h"
#include "DataStructures.h"
#include "Error.h"
#include "FileIO.h"

// VBO Extension Definitions, From glext.h
#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_STATIC_DRAW_ARB 0x88E4
typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);


bool Load3DS(model_3ds* model,const char *filename);
void loadModels(ApplicationInfo *application);
void cleanBuffers(ApplicationInfo *application);
bool Buffer3DS(model_3ds* model);
bool Unbuffer3DS(const unsigned int buffer_num);
bool Clean3DS(model_3ds* model);
