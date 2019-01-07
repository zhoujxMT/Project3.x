
#ifndef MATH_AIDE_H_
#define MATH_AIDE_H_
#pragma once

#include "cocos2d.h"
#include "CMD_Fish.h"
#include <vector>

class MathAide {
private:
  MathAide();

public:
  static int Factorial(int number);
  static int Combination(int count, int r);
  static float CalcDistance(float x1, float y1, float x2, float y2);
  static float CalcAngle(float x1, float y1, float x2, float y2);
  static void BuildLinear(float init_x[], float init_y[], int init_count, std::vector<NS_lrbyFish::FPoint>& trace_vector, float distance);
  static void BuildLinear(float init_x[], float init_y[], int init_count, std::vector<NS_lrbyFish::FPointAngle>& trace_vector, float distance);
  static void BuildBezier(float init_x[], float init_y[], int init_count, std::vector<NS_lrbyFish::FPoint>& trace_vector, float distance);
  static void BuildBezierFast(float init_x[], float init_y[], int init_count, std::vector<NS_lrbyFish::FPoint>& trace_vector, float distance);
  static void BuildBezier(float init_x[], float init_y[], int init_count, std::vector<NS_lrbyFish::FPointAngle>& trace_vector, float distance);
  static void BuildCircle(float center_x, float center_y, float radius, NS_lrbyFish::FPoint* fish_pos, int fish_count);
  static void BuildCircle(float center_x, float center_y, float radius, NS_lrbyFish::FPointAngle* fish_pos, int fish_count, float rotate = 0.f, float rotate_speed = 0.f);
};

#endif // MATH_AIDE_H_