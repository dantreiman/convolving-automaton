#include "ImageCapture.h"

#include <cstdlib>
#include <memory>

#include "image_includes.h"
#include "log.h"
#include "utils.h"

namespace ca {

ImageCapture::ImageCapture(GLFWwindow* window) : window_(window) {}

void ImageCapture::CaptureFrameToFile(const std::string& path) {
    Size framebuffer_size;
    glfwGetFramebufferSize(window_, &framebuffer_size.w, &framebuffer_size.h);
    GLubyte* buffer = (GLubyte*)malloc(framebuffer_size.w * framebuffer_size.h * 4 * sizeof(GLubyte));
    // glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(0, 0, framebuffer_size.w, framebuffer_size.h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    CHECK_GL_ERROR("glReadPixels");
    // glReadPixels gives interleaved color data
    // CImg expects ordered non-interleaved planes.
    GLubyte* channels = (GLubyte*)malloc(framebuffer_size.w * framebuffer_size.h * 4 * sizeof(GLubyte));
    const int pixel_count = framebuffer_size.w * framebuffer_size.h;
    for (int i=0; i < pixel_count; i++) {
        int interleaved_index = 4 * i;
        // Red
        channels[i] = buffer[interleaved_index];
        // Green
        channels[pixel_count + i] = buffer[interleaved_index + 1];
        // Blue
        channels[2*pixel_count + i] = buffer[interleaved_index + 2];
        // Alpha
        channels[3*pixel_count + i] = buffer[interleaved_index + 3];
    }
    free(buffer);
    // write buffer to file
    CImg<GLubyte> image(channels, framebuffer_size.w, framebuffer_size.h, 1, 4);
    image.save_png(path.c_str());
    free(channels);
}

}  // namespace ca
