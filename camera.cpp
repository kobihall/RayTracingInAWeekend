#include "camera.h"

camera::camera() 
{
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    m_origin = glm::dvec3(0, 0, 0);
    m_horizontal = glm::dvec3(viewport_width, 0.0, 0.0);
    m_vertical = glm::dvec3(0.0, viewport_height, 0.0);
    m_lower_left_corner = m_origin - m_horizontal/2.0 - m_vertical/2.0 - glm::dvec3(0, 0, focal_length);
}

camera::camera(uint32_t ViewportWidth, uint32_t ViewportHeight, double vfov, glm::dvec3 lookfrom, glm::dvec3 lookat, glm::dvec3 vup)
{
    auto aspect_ratio = double(ViewportWidth)/double(ViewportHeight);
    auto theta = degrees_to_radians(vfov);
    auto h = glm::tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;
    //auto focal_length = 1.0;

    auto w = glm::normalize(lookfrom - lookat);
    auto u = glm::normalize(glm::cross(vup, w));
    auto v = glm::cross(w, u);

    m_origin = lookfrom;
    m_horizontal = viewport_width * u;
    m_vertical = viewport_height * v;
    m_lower_left_corner = m_origin - m_horizontal/2.0 - m_vertical/2.0 - w;
}

ray camera::get_ray(double u, double v) const 
{
    return ray(m_origin, m_lower_left_corner + u*m_horizontal + v*m_vertical - m_origin);
}