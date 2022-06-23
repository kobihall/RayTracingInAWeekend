#include "Renderer.h"

#include "utils.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "sphere.h"


double hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

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
    double aspect_ratio = double(ViewportWidth)/double(ViewportHeight);
    double camera_width = aspect_ratio*camera_height;
    vec3 horizontal = vec3(camera_width, 0, 0);
    vec3 vertical = vec3(0, camera_height, 0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    for(uint32_t j = 0; j < ViewportHeight; ++j){
        for(uint32_t i = 0; i < ViewportWidth; ++i){
            double u = double(i) / (ViewportWidth-1);
            double v = double(j) / (ViewportHeight-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			color pixel_color = ray_color(r, world);
			ImageData[(ViewportHeight - 1 - j)*ViewportWidth + i] = write_color(pixel_color);
		}
	}
}