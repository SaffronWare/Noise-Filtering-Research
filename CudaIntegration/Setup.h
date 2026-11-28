#pragma once

#include "config.h"
#include "Render.cuh"

inline RenderConfig Setup()
{
    RenderConfig config;
    config.width = 1920;
    config.height = 1080;
    config.cam = Camera();
    config.scene;


    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Rect> rects;


    Sphere matteSphere = Sphere();
    matteSphere.radius = 0.65f;
    matteSphere.position = glm::vec3(-2.2f, 0.36f, 3.6f);
    matteSphere.mat.baseColor = glm::vec3(0.85f, 0.75f, 0.60f);
    matteSphere.mat.roughness = 1.0f;
    matteSphere.mat.mettalic = 0.0f;
    matteSphere.mat.clearcoat = 0.0f;

    Sphere glossyPlasticSphere = Sphere();
    glossyPlasticSphere.radius = 0.65f;
    glossyPlasticSphere.position = glm::vec3(0.0f, 0.36f, 3.6f);
    glossyPlasticSphere.mat.baseColor = glm::vec3(0.9f, 0.06f, 0.04f);
    glossyPlasticSphere.mat.roughness = 0.12f;
    glossyPlasticSphere.mat.mettalic = 0.0f;
    glossyPlasticSphere.mat.specular = 1.0f;
    glossyPlasticSphere.mat.clearcoat = 0.0f;

    Sphere smoothMetalSphere =Sphere();
    smoothMetalSphere.radius = 0.65f;
    smoothMetalSphere.position = glm::vec3(2.2f, 0.36f, 3.6f);
    smoothMetalSphere.mat.baseColor = glm::vec3(0.95f, 0.72f, 0.26f);
    smoothMetalSphere.mat.roughness = 0.04f;
    smoothMetalSphere.mat.mettalic = 1.0f;
    smoothMetalSphere.mat.clearcoat = 0.0f;

    Sphere roughMetalSphere =Sphere();
    roughMetalSphere.radius = 0.65f;
    roughMetalSphere.position = glm::vec3(-2.2f, 0.36f, 5.9f);
    roughMetalSphere.mat.baseColor = glm::vec3(0.72f, 0.78f, 0.88f);
    roughMetalSphere.mat.roughness = 0.7f;
    roughMetalSphere.mat.mettalic = 1.0f;
    roughMetalSphere.mat.clearcoat = 0.0f;

    Sphere clearcoatSphere =Sphere();
    clearcoatSphere.radius = 0.65f;
    clearcoatSphere.position = glm::vec3(0.0f, 0.36f, 5.9f);
    clearcoatSphere.mat.baseColor = glm::vec3(0.05f, 0.22f, 0.95f);
    clearcoatSphere.mat.roughness = 0.5f;
    clearcoatSphere.mat.mettalic = 0.0f;
    clearcoatSphere.mat.specular = 1.0f;
    clearcoatSphere.mat.clearcoat = 1.0f;
    clearcoatSphere.mat.clearcoatGloss = 1.0f;

    Sphere mixedSphere =Sphere();
    mixedSphere.radius = 0.65f;
    mixedSphere.position = glm::vec3(2.2f, 0.36f, 5.9f);
    mixedSphere.mat.baseColor = glm::vec3(0.7f, 0.15f, 0.55f);
    mixedSphere.mat.roughness = 0.3f;
    mixedSphere.mat.mettalic = 0.5f;
    mixedSphere.mat.specular = 1.0f;
    mixedSphere.mat.specularTint = 1.0f;
    mixedSphere.mat.clearcoat = 0.6f;
    mixedSphere.mat.clearcoatGloss = 0.8f;

    Plane floorPlane = Plane();
    floorPlane.position = glm::vec3(0, 1.01f, 0);
    floorPlane.normal = glm::vec3(0, -1, 0);
    floorPlane.mat.baseColor = glm::vec3(0.8f);
    floorPlane.mat.roughness = 1.0f;
    floorPlane.mat.mettalic = 0.0f;

    Plane ceilPlane = Plane();
    ceilPlane.position = glm::vec3(0, -2.01f, 0);
    ceilPlane.normal = glm::vec3(0, 1, 0);
    ceilPlane.mat.baseColor = glm::vec3(0.8f);
    ceilPlane.mat.roughness = 1.0f;

    Plane leftPlane = Plane();
    leftPlane.position = glm::vec3(-4, 0, 0);
    leftPlane.normal = glm::vec3(1, 0, 0);
    leftPlane.mat.baseColor = glm::vec3(0.9f, 0.2f, 0.12f);
    leftPlane.mat.roughness = 0.12f;
    leftPlane.mat.mettalic = 0.0f;
    leftPlane.mat.specular = 1.0f;
    leftPlane.mat.clearcoat = 1.0f;
    leftPlane.mat.clearcoatGloss = 1.0f;

    Plane rightPlane = Plane();
    rightPlane.position = glm::vec3(4, 0, 0);
    rightPlane.normal = glm::vec3(-1, 0, 0);
    rightPlane.mat.baseColor = glm::vec3(0.95f);
    rightPlane.mat.roughness = 0.02f;
    rightPlane.mat.mettalic = 1.0f;
    rightPlane.mat.clearcoat = 0.0f;

    Plane frontPlane = Plane();
    frontPlane.position = glm::vec3(0, 0, 8);
    frontPlane.normal = glm::vec3(0, 0, 1);
    frontPlane.mat.baseColor = glm::vec3(0.8f);
    frontPlane.mat.roughness = 1.0f;

    Plane backPlane = Plane();
    backPlane.position = glm::vec3(0, 0, -2);
    backPlane.normal = glm::vec3(0, 0, -1);
    backPlane.mat.baseColor = glm::vec3(0.8f);
    backPlane.mat.roughness = 1.0f;

    Rect lightRect = Rect();
    lightRect.center = glm::vec3(0, -1.98f, 4.2f);
    lightRect.right = glm::vec3(1, 0, 0);
    lightRect.up = glm::vec3(0, 0, -1);
    lightRect.dimensions = glm::vec2(3.0f, 2.0f);
    lightRect.mat.emissionColor = glm::vec3(1.0f);
    lightRect.mat.emissionStrength = 6.0f;
    lightRect.mat.baseColor = glm::vec3(1.0f);
    lightRect.mat.roughness = 1.0f;

    spheres = { smoothMetalSphere, matteSphere, mixedSphere, roughMetalSphere, glossyPlasticSphere, clearcoatSphere };
    planes = { frontPlane, backPlane, rightPlane, leftPlane, ceilPlane, floorPlane };
    rects = { lightRect };

    config.scene.Load(spheres, planes, rects);
    return config;
}