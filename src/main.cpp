#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <memory>

#include "Math.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"


void GenQuad(std::vector<Vertex> &verts, float x, float y, vec4b color) {
    y = (y+x)*0.5;
    x = x*0.8;

    verts.push_back(Vertex(vec2f(0+x, 0+y), color));
    verts.push_back(Vertex(vec2f(0+x, 1+y), color));
    verts.push_back(Vertex(vec2f(0.8+x, 0.5+y), color));

    verts.push_back(Vertex(vec2f(0+x, 0+y), color));
    verts.push_back(Vertex(vec2f(0+x, 1+y), color));
    verts.push_back(Vertex(vec2f(-0.8+x, 0.5+y), color));
}

template<uint32_t N>
std::array<uint32_t, N> GenIndices() {
    std::array<uint32_t, N> ind;
    for (size_t i = 0; i < N; i++)
    {
        ind[i] = i;
        //std::cout << ind[i] << std::endl;
    }
    return ind;
}

void GenRow(std::vector<Vertex> &verts, float y, int count) {
    for (float i = 0; i < count; i++)
    {
        GenQuad(verts, i-y, y*2, vec4b(240, 180, 160, 255));
    }
    
}

const uint32_t MaxGrid = 10;
const uint32_t MaxQuads = MaxGrid*MaxGrid;
const uint32_t MaxIndices = MaxQuads*6;

int main(void) {
    Renderer renderer(vec2i(1280, 720), "IsometricGrid");
    renderer.InitEnable();

    std::vector<Vertex> verts;
    
    for (size_t i = 0; i < MaxGrid; i++)
    {
        GenRow(verts, i, MaxGrid);
    }
    

    std::array<uint32_t, MaxIndices> indices = GenIndices<MaxIndices>();


    VertexArray va;
    VertexBuffer vb(verts.data(), verts.size() * sizeof(Vertex));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<uint8_t>(4);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices.data(), indices.size());

    glm::mat4 proj = glm::ortho(-17.0f, 17.0f, 10.0f, -10.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    while (!renderer.WindowShouldClose())
    {
        renderer.Clear(vec3f(1.0f, 1.0f, 0.94f));

        vb.Bind();
        glm::mat4 mvp = proj * view * glm::mat4(1.0f);
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);


        if(glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            exit(0);
        } 

        if(glfwGetKey(renderer.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        } else { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

        renderer.EndEvents();
    }
    
    renderer.~Renderer();
    return 0;
}
