#include "Renderer.h"

#include "utils.h"
#include "Random.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"

glm::dvec3 ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;
    if(depth <= 0)
        return glm::dvec3(0,0,0);
    if(world.hit(r, 0.001, INFTY, rec)) {
        glm::dvec3 target = rec.p + rec.normal + random_in_unit_sphere(rec.normal, 0.0);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }
    glm::dvec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

Renderer::Renderer()
{
    world.add(std::make_shared<sphere>(glm::dvec3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(glm::dvec3(0,-100.5,-1), 100));
}

void Renderer::render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight)
{
    _camera = camera(ViewportWidth, ViewportHeight);
    double pixelWidth = 1.0 / (ViewportWidth-1);
    double pixelHeight = 1.0 / (ViewportHeight-1);

    for(uint32_t j = 0; j < ViewportHeight; ++j){
        for(uint32_t i = 0; i < ViewportWidth; ++i){
            double u = double(i) * pixelWidth;
            double v = double(j) * pixelHeight;
			ImageData[j*ViewportWidth + i] = renderPerPixel(u,v, pixelWidth, pixelWidth);
		}
	}
}

uint32_t Renderer::renderPerPixel(double u, double v, double pixelWidth, double pixelHeight)
{
    if(settings.MSAA){
        glm::dvec3 pixel_color(0, 0, 0);
        for(int i = 0; i < settings.msaaSamples; i++){
            ray r = _camera.get_ray(u + random_double() * pixelWidth, v + random_double() * pixelHeight);
            pixel_color += ray_color(r, world, settings.rayDepth);
        }
        return write_color(pixel_color,settings.msaaSamples);
    }
    ray r = _camera.get_ray(u, v);
    glm::dvec3 pixel_color = ray_color(r, world, settings.rayDepth);
    return write_color(pixel_color,1);
}