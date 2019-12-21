#pragma once
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/MeshRenderer.hpp>

class TrafficLight: public Primitive {
 private:
    static MeshRenderer* cubeMesh;
    static MeshRenderer* sphereMesh;
    Transform stand;
    Transform holder;
    Transform green, yellow, red;
    static GLuint standTex;
    static GLuint holderTex;
 public:
    explicit TrafficLight() {};
};