#pragma once
#include <glm/glm.hpp>

// COLOR ALIASES

// represents the color (RGB) with floating point values (0.0-1.0)
using color3_t = glm::vec3;

// represents the color(RGBA) with floating point values(0.0 - 1.0)
using color4_t = glm::vec4;

// represents the color (RGBA) with integer values
using rgba_t = glm::uint32;


//converts the integer (8888) color representation to floating point (0.0-1.0) color representation
// color4_t = struct that holds four floating point values (RGBA)
inline color4_t RGBAToColor(const rgba_t& rgba)
{	// 32-bit int representing color:
	color4_t color;

	// (rgba >> 24) = rgba right shift 24 bits (move most significant bits to least significant position
	// & 0xFF = after bit shift, 0xFF (HEX = 255 in decimal, in binary 11111111 (8 bits)) & (AND) isolates 8 bits that were shifted and ensures only last 8 bits are kept --> extracts red component 
	color.r = ((rgba >> 24) & 0xFF) / 255.0f; // Extract red component, divide by floating point and normalize (0.0 - 1.0) --> 0 = 0.0, 255 = 1.0
	color.g = ((rgba >> 16) & 0xFF) / 255.0f; // Extract green component and normalize
	color.b = ((rgba >> 8) & 0xFF) / 255.0f; // Extract blue component and normalize
	color.a = (rgba & 0xFF) / 255.0f; // Extract alpha component and normalize


}

//converts the floating point (0.0-1.0) color representation to integer (8888) color representation
inline rgba_t ColorToRGBA(const color4_t& color)
{
	rgba_t rgba = 0;

	rgba |= uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24; // bitshit 24 bits to least bit position 
	rgba |= uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16; // bitshit 16 bits to least bit position 
	rgba |= uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8; // bitshit 8 bits to least bit position 
	rgba |= uint8_t(glm::clamp(color.a, 0.0f, 1.0f) * 255) << 0; // bitshit 0 bits to least bit position 

	return rgba;

}