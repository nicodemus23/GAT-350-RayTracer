#include "Canvas.h"
#include "Color.h"



Canvas::Canvas(int width, int height, const Renderer& renderer) : m_renderer(renderer) // initialize renderer reference
{
	m_size = { glm::ivec2(width, height) };
	m_texture = SDL_CreateTexture(renderer.m_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		width, height);

	m_buffer.resize(width * height); //resize vector to hold width* height elements>
}

Canvas::~Canvas()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Canvas::Update()
{	// jic
	if (!m_texture || m_buffer.empty()) {
		return;
	}

	// set texture with buffer rgba_t data
	int pitch = m_size.x * sizeof(Color::rgba_t);
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), pitch);
}

void Canvas::Clear(const Color::color4_t& color)
{
	Color::rgba_t rgba = Color::ColorToRGBA(color);
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const Color::color4_t& color)
{	// checking if point is within the canvas bounds: 
	if (point.x < 0 || point.x >= m_size.x || point.y < 0 || point.y >= m_size.y)
	{
		return; // point is outside of canvas bounds 
	}
	// otherwise convert to RGBA format and set the pixel in the buffer
	Color::rgba_t rgba = Color::ColorToRGBA(color);

	m_buffer[point.x + (point.y * m_size.x)] = rgba;
}

void Canvas::PresentCanvas(const Canvas& canvas)
{
	// copy canvas texture to renderer
	SDL_RenderCopy(m_renderer.GetSDLRenderer(),
		m_texture, NULL, NULL);
	// present renderer to screen
	SDL_RenderPresent(m_renderer.GetSDLRenderer());
}
