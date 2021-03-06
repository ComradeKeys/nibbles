#pragma once
/*H**********************************************************************
 * FILENAME :        arena.h
 *
 * DESCRIPTION :
 *       Contains main game content and holds the contents of the arena
 *       such as the snake, fruit, and obstacles
 *
 * PUBLIC FUNCTIONS :
 *       update_arena(void)
 *
 * AUTHOR     :    Brigham Keys, Esq
 * START DATE :    07/31/2015
 *
 *H*/
#ifdef __MINGW32__
#include <windows.h>
#endif

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Obstacle.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "Font.hpp"

class Arena {

 public:

  Arena(void);
  virtual ~Arena(void);
  void update(void);
  inline void draw(void);
  Snake *snake;

 private:
  float rot;
  unsigned int score;
  Font *font;
  inline void correct_elements(void);
  void drawRainbowTriangle(void);
  void correct_fruit(void);
  void correct_obstacle(void);
  void correct_snake(void);
  bool is_snake_dead(void);
  bool is_snake_eating(void);
  Obstacle *obstacle;
  Fruit *fruit;
};
