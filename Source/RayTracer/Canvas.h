#pragma once
#include "Color.h"
#include "Renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Renderer;

class Canvas
{
public:
    Canvas(int width, int height, const class Renderer& renderer); // why do we need forward declaraction here?
    ~Canvas();

    void Update();

    void Clear(const Color::color4_t& color);
    void DrawPoint(const glm::ivec2& point, const Color::color4_t& color);

   
    const glm::ivec2& GetSize() const { return m_size; }

    friend class Renderer;

private:

    struct SDL_Texture* m_texture = nullptr; // forward dec and pointer to SDL_Texture
    std::vector<Color::rgba_t> m_buffer; // vector of rgba_t 

    glm::ivec2 m_size = glm::ivec2(0, 0); // integer 


};