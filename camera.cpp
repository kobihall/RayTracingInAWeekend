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

camera::camera(uint32_t ViewportWidth, uint32_t ViewportHeight)
{
    auto aspect_ratio = double(ViewportWidth)/double(ViewportHeight);
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    m_origin = glm::dvec3(0, 0, 0);
    m_horizontal = glm::dvec3(viewport_width, 0.0, 0.0);
    m_vertical = glm::dvec3(0.0, viewport_height, 0.0);
    m_lower_left_corner = m_origin - m_horizontal/2.0 - m_vertical/2.0 - glm::dvec3(0, 0, focal_length);
}

ray camera::get_ray(double u, double v) const 
{
    return ray(m_origin, m_lower_left_corner + u*m_horizontal + v*m_vertical - m_origin);
}