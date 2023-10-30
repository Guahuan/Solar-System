#pragma once
#include "ball.h"
#include <GL/glut.h>
#include <cmath>
#include <vector>

class Star : public Ball {
public:
  Star(float circle_x, float circle_y, float circle_z, float circle_radius,
       float angular, Star *parent, std::vector<Star *> children, float size,
       float r, float g, float b)
      : Ball(circle_x + circle_radius, circle_y, circle_z, size, r, g, b) {
    this->circle_x = circle_x;
    this->circle_y = circle_y;
    this->circle_z = circle_z;
    this->circle_radius = circle_radius;
    this->angular = angular;
    this->parent = parent;
    this->children = children;
  };

  void draw(float time) {
    glPushMatrix();
    x = circle_x + circle_radius * std::cos(time * angular);
    y = circle_y;
    z = circle_z + circle_radius * std::sin(time * angular);
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(size, 30, 30);
    glPopMatrix();
  }

public:
  float circle_x, circle_y, circle_z;
  float circle_radius;
  float angular;
  Star *parent;
  std::vector<Star *> children;
};