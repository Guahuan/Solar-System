#include "star.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#define PI 3.1415926

float SCREEN_X = 1000;
float SCREEN_Y = 1000;

// revolution control
float t = 0;

//视角控制
float look_x = 0, look_y = 0, look_z = 0, look_x_temp = 0, look_z_temp = 0;
float screenrate_x, screenrate_y; //鼠标屏幕坐标相对于中心点移动的比例
float r = 10;
//相机位置
float cpos_x = 0, cpos_y = 5, cpos_z = 25;

int centerpoint_x = SCREEN_X / 2, centerpoint_y = SCREEN_Y / 2;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glViewport(0, 0, SCREEN_X, SCREEN_Y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)SCREEN_X / (GLfloat)SCREEN_Y, 0.1, 100000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(cpos_x, cpos_y, cpos_z, cpos_x + look_x, cpos_y + look_y,
            cpos_z - look_z, 0, 1, 0);

  t += 0.001;
  // sun
  Star sun1(0, 0, 0, 8, 1, nullptr, std::vector<Star *>(), 2, 1, 1, 0);
  sun1.draw(t);
  Star sun2(0, 0, 0, 8, 1, nullptr, std::vector<Star *>(), 2, 1, 1, 0);
  sun2.draw(t + 3.14 / 1);

  // // plant
  Star plant1(sun1.x, sun1.y, sun1.z, 4, 10, &sun1, std::vector<Star *>(), 1, 1,
              0, 0);

  sun1.children.push_back(&plant1);
  plant1.draw(t);
  Star plant2(sun2.x, sun2.y, sun2.z, 4, 15, &sun2, std::vector<Star *>(), 1, 1,
              0, 0);
  sun2.children.push_back(&plant2);
  plant2.draw(t);

  // moon
  Star moon1(plant1.x, plant1.y, plant1.z, 2, 50, &plant1,
             std::vector<Star *>(), 0.5, 0, 1, 0);
  plant1.children.push_back(&moon1);
  moon1.draw(t);

  glutSwapBuffers();
}

void reshape(int w, int h) {
  SCREEN_X = w;
  SCREEN_Y = h;
  glViewport(0, 0, SCREEN_X, SCREEN_Y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)SCREEN_X / (GLfloat)SCREEN_Y, 0.1, 100000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//不按鼠标移动事件
void onMouseMovePassive(int screen_x, int screen_y) {
  float offsetx = screen_x - centerpoint_x;
  float offsety = screen_y - centerpoint_y;
  screenrate_x = offsetx / centerpoint_x * PI;     //用于摄像机水平移动
  screenrate_y = offsety / centerpoint_y * PI / 2; //用于摄像机上下移动
  //水平方向
  look_x_temp = r * sin(screenrate_x);
  look_z_temp = r * cos(screenrate_x); //最后使用时要和相机坐标相加/减
  //竖直方向
  look_y = r * sin(-screenrate_y);
  float r_castlenght = abs(r * cos(screenrate_y)); //投影在xz面的长度
  //根据长度计算真正的look_x,look_z
  look_x = r_castlenght * look_x_temp / r;
  look_z = r_castlenght * look_z_temp / r;
}

float step = 0.1;
void key(unsigned char key, int x, int y) {
  switch (key) {
  case 'r':
    t += 0.01;
    break;
  case 'w':
    cpos_x += look_x_temp * step;
    cpos_z -= look_z_temp * step;
    break;
  case 's':
    cpos_x -= look_x_temp * step;
    cpos_z += look_z_temp * step;
    break;
  case 'a':
    cpos_x += -look_z_temp * step;
    cpos_z -= look_x_temp * step;
    break;
  case 'd':
    cpos_x += look_z_temp * step;
    cpos_z -= -look_x_temp * step;
    break;
  default:
    break;
  }
}

void idle(void) { display(); }

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_X, SCREEN_Y);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Solar System");
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glutReshapeFunc(reshape);
  glutPassiveMotionFunc(onMouseMovePassive);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);

  glutMainLoop();
  return 0;
}