#include "Simulation.h"

#include "Buffer.h"
#include "Kernel.h"
#include "log.h"

namespace ca {

Simulation::Simulation(const Size& world_size) : world_size_(world_size) {
}

void Simulation::Init() {
	// Temp: Generate textures
	glGenTextures (1, &inner_kernel_tex_);
	CHECK_GL_ERROR("glGenTextures");
	Buffer2D<float> inner_kernel(world_size_);
	float inner_sum = CircularKernel(&inner_kernel, 20, 1);
	glBindTexture (GL_TEXTURE_2D, inner_kernel_tex_);
	CHECK_GL_ERROR("glBindTexture");
	// glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, world_size_.w, world_size_.h, GL_RED, GL_FLOAT, inner_kernel.data());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA,
	             world_size_.w, world_size_.h,
				0, GL_ALPHA, GL_FLOAT, inner_kernel.data());
	CHECK_GL_ERROR("glTexImage2D");
}

}  // namespace ca