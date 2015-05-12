#ifndef CONVOLVING_AUTOMATON_LOG_H_
#define CONVOLVING_AUTOMATON_LOG_H_

#define CHECK_GL_ERROR(call) { GLenum error = glGetError(); if (error != GL_NO_ERROR) fprintf(stdout, "OpenGL error %d in call to %s\n", (int)error, call); }

#endif  // CONVOLVING_AUTOMATON_LOG_H_