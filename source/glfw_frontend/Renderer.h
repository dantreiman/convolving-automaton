#ifndef CONVOLVING_AUTOMATON_RENDERER_H_
#define CONVOLVING_AUTOMATON_RENDERER_H_

#include "ColorScheme.h"
#include "FrameBuffer.h"
#include "gl_includes.h"
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
    void DrawHue(const FrameBuffer* state);
    void DrawGradient(const FrameBuffer* state);
    void UpdateGradientColors(const ColorScheme& color_scheme);

    Size rtt_size_;
    GLuint default_framebuffer_;
    std::unique_ptr<Shader> hue_shader_;
    std::unique_ptr<Shader> gradient_shader_;
    // uniform locations
    struct {
        GLint state_texture_location;
    } hue_uniforms_;
// Gradient shader unforms
    struct {
        GLint background_color_location;
        GLint color1_location;
        GLint color2_location;
        GLint color3_location;
        GLint color4_location;
        GLint state_texture_location;
    } gradient_uniforms_;
};

}  // namespace ca


#endif  // CONVOLVING_AUTOMATON_RENDERER_H_