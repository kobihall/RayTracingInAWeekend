#include "Renderer.h"

#include "utils.h"
#include "Random.h"
#include "ray.h"
#include "material.h"
#include "color.h"
#include "sphere.h"

glm::dvec3 ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;
    if(depth <= 0)
        return glm::dvec3(0,0,0);
    if(world.hit(r, 0.001, INFTY, rec)) {
        ray scattered;
        glm::dvec3 attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return glm::dvec3(0,0,0);
    }
    glm::dvec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

Renderer::Renderer()
{
    auto material_ground = std::make_shared<lambertian>(glm::dvec3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(glm::dvec3(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<metal>(glm::dvec3(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<metal>(glm::dvec3(0.8, 0.6, 0.2));

    world.add(std::make_shared<sphere>(glm::dvec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(glm::dvec3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<sphere>(glm::dvec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<sphere>(glm::dvec3( 1.0,    0.0, -1.0),   0.5, material_right));
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
            ray r = _camera.get_ray(u + Random::random_double() * pixelWidth, v + Random::random_double() * pixelHeight);
            pixel_color += ray_color(r, world, settings.rayDepth);
        }
        return write_color(pixel_color,settings.msaaSamples);
    }
    ray r = _camera.get_ray(u, v);
    glm::dvec3 pixel_color = ray_color(r, world, settings.rayDepth);
    return write_color(pixel_color,1);
}