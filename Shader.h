#ifndef CONVOLVING_AUTOMATON_SHADER_H_
#define CONVOLVING_AUTOMATON_SHADER_H_

#include <string>
#include "gl_includes.h"

namespace ca {

class Shader {
  public:
	/**
	 * Load a shader from shaders directory by name.
	 */
    Shader(const std::string& name);

    /**
     * Link and compile the shader program.
     * On error, logs error to the console and returns false.
     */
    bool Init();

	const GLuint program();

  private:
	bool Load();
	bool Compile();
	
	std::string name_;
	std::string vert_src_;
	std::string frag_src_;
	GLuint vertex_shader_;
	GLuint fragment_shader_;
	GLuint program_;
};

}

#endif  // CONVOLVING_AUTOMATON_SHADER_H_
