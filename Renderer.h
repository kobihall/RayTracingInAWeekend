#pragma once

#include <cstdint>
#include "vec3.h"
#include "hittable_list.h"
#include "camera.h"

struct RenderSettings
{
    bool MSAA = false;
    int msaaSamples = 1;
};

class Renderer {
public:
    Renderer();
    ~Renderer() {}

    RenderSettings settings;

    void render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight);
    uint32_t renderPerPixel(double u, double v, double pixelWidth, double pixelHeight);
private:
    hittable_list world;

    point3 origin = point3(0, 0, 0);
    double focal_length = 1.0;
    double camera_height = 2.0;

    camera _camera;
};