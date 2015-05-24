#ifndef CONVOLVING_AUTOMATON_LOG_H_
#define CONVOLVING_AUTOMATON_LOG_H_

#include <iostream>

#define LOGFILE stdout

// Log an openGL error
#define CHECK_GL_ERROR(call) { GLenum error = glGetError(); if (error != GL_NO_ERROR) fprintf(LOGFILE, "%s:%s():%d - OpenGL error %d in call to %s\n", __FILE__, __func__, __LINE__, (int)error, call); }

// If an error occurred, and return value if an error occurred
#define RCHECK_GL_ERROR(call, value) { GLenum error = glGetError(); if (error != GL_NO_ERROR) fprintf(LOGFILE, "%s:%s():%d - OpenGL error %d in call to %s\n", __FILE__, __func__, __LINE__, (int)error, call); return value; }

#define LOG_ERROR(message) { fprintf(LOGFILE, "%s:%s():%d - %s\n", __FILE__, __func__, __LINE__,  message); }

#endif  // CONVOLVING_AUTOMATON_LOG_H_