#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include <string>

#include "gl_includes.h"


namespace ca {


class ImageCapture {
 public:
    ImageCapture(GLFWwindow* window);

    void CaptureFrameToFile(const std::string& path);
 private:
    GLFWwindow* window_;
};


}  // namespace ca

#endif