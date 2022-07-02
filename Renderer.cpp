#include "Renderer.h"

#include "utils.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world) 
{
    hit_record rec;
    if(world.hit(r, 0, INFTY, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

Renderer::Renderer()
{
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));
}

void Renderer::render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight)
{
    camera _camera(ViewportWidth, ViewportHeight);

    for(uint32_t j = 0; j < ViewportHeight; ++j){
        for(uint32_t i = 0; i < ViewportWidth; ++i){
            double u = double(i) / (ViewportWidth-1);
            double v = double(j) / (ViewportHeight-1);
            ray r = _camera.get_ray(u, v);
			color pixel_color = ray_color(r, world);
			ImageData[j*ViewportWidth + i] = write_color(pixel_color);
		}
	}
}