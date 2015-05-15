#ifndef CONVOLVING_AUTOMATON_LOG_H_
#define CONVOLVING_AUTOMATON_LOG_H_

#include <iostream>

#define LOGFILE stdout

#define CHECK_GL_ERROR(call) { GLenum error = glGetError(); if (error != GL_NO_ERROR) fprintf(LOGFILE, "%s:%s():%d - OpenGL error %d in call to %s\n", __FILE__, __func__, __LINE__, (int)error, call); }

#define LOG_ERROR(message) { fprintf(LOGFILE, "%s:%s():%d - %s\n", __FILE__, __func__, __LINE__,  message); }

#endif  // CONVOLVING_AUTOMATON_LOG_H_