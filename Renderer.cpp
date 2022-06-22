#include "Renderer.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"

void Renderer::render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight)
{
    for(uint32_t j = 0; j < ViewportHeight; ++j){
		for(uint32_t i = 0; i < ViewportWidth; ++i){
			color pixel_color(double(i) / (ViewportWidth-1), double(j) / (ViewportHeight-1), 0.25);
			ImageData[(ViewportHeight - 1 - j)*ViewportWidth + i] = write_color(pixel_color);
		}
	}
}