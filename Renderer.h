#pragma once

#include <cstdint>

class Renderer {
public:
    Renderer() {}
    ~Renderer() {}

    void render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight);
private:
};