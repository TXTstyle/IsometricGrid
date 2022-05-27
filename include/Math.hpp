#pragma once

#include <cstdint>

struct vec3f
{
    float x, y, z;

    vec3f(float p_x, float p_y, float p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec2f
{
    float x, y;

    vec2f(float p_x, float p_y)
    : x(p_x), y(p_y) {}
};

struct vec3i
{
    int x, y, z;

    vec3i(int p_x, int p_y, int p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec2i
{
    int x, y;

    vec2i(int p_x, int p_y)
    : x(p_x), y(p_y) {}
};

struct vec3u
{
    uint32_t x, y, z;

    vec3u(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    : x(p_x), y(p_y), z(p_z) {}
};

struct vec2u
{
    uint32_t x, y;

    vec2u(uint32_t p_x, uint32_t p_y)
    : x(p_x), y(p_y) {}
};

struct vec2b
{
    uint8_t x, y;

    vec2b(uint8_t p_x, uint8_t p_y)
    : x(p_x), y(p_y) {}
};

struct vec4b
{
    uint8_t x, y, z, w;

    vec4b(uint8_t p_x, uint8_t p_y, uint8_t p_z, uint8_t p_w)
    : x(p_x), y(p_y), z(p_z), w(p_w) {}
};

struct Vertex {
    vec2f Pos;
    vec4b Color;

    Vertex(vec2f p_pos, vec4b p_color)
    : Pos(p_pos), Color(p_color) {}
};
