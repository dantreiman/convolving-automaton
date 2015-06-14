#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include "ColorScheme.h"
#include "FrameBuffer.h"
#include "gl_includes.h"
#include "Timer.h"
#include "Shader.h"
#include "utils.h"

namespace ca {

class Renderer {
  public:
    Renderer(const Size& rtt_size, GLuint default_framebuffer);
  
    /**
     * Configure gl state.
     */
    void Init();

    void DrawState(GLFWwindow* window, const FrameBuffer* state);

    void Resize(int width, int height);

    const Size& rtt_size() const;

  private:
	void UpdateColors();
    
    Size rtt_size_;
    GLuint default_framebuffer_;
    std::unique_ptr<Shader> draw_shader_;
    std::unique_ptr<Shader> draw_gradient_shader_;
    // uniform locations
    GLint uniform_stateTexture_;
    // Gradient shader locations
    struct {
        GLint background_color_location;
        GLint color1_location;
        GLint color2_location;
        GLint color3_location;
        GLint color4_location;
        GLint state_texture_location;
    } uniforms_;
    int color_scheme_index_;
    ColorScheme color_scheme_;
	Timer color_scheme_timer_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_RENDERER_H_