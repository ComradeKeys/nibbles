#include "Arena.hpp"
#include <chrono>
#include <thread>
bool Arena::is_snake_eating(void) {

  snake->iter = snake->body.begin();

  if(snake->iter->getX() == fruit->getX() &&
     snake->iter->getY() == fruit->getY()) {
    return true;
  }
  return false;
}

bool Arena::is_snake_dead(void) {

  snake->iter = snake->body.begin();

  int snake_headX = snake->iter->getX();
  int snake_headY = snake->iter->getY();

  //are we out of the arena?
  if(snake_headX == 20 ||
     snake_headY == 20 ||
     snake_headX == -1 ||
     snake_headY == -2) {
    return true;
  }


  for(obstacle->iter = obstacle->item.begin(); obstacle->iter != obstacle->item.end();++obstacle->iter) {

    //did we hit an obstacle?
    if(snake_headX == obstacle->iter->getX() &&
       snake_headY == obstacle->iter->getY()) {
      return true;
    }
  }

  ++snake->iter; //skip the head
  //self collision
  while(snake->iter != snake->body.end()) {
    if(snake_headX == snake->iter->getX() &&
       snake_headY == snake->iter->getY()) {
      return true;
    }
    ++snake->iter;
  }
  return false;
}

void Arena::drawRainbowTriangle(void) {

  ++rot;
  for(int i = 1; i < 20; ++i) {
  glPushMatrix();
  glTranslatef(i + 1.25, i - .5, -12 - i);
  glRotatef((rot / 2) * i, 1, 1, 1);
  //some linear algebra
  glScalef(-.5 * cos((rot / 20) * i), 1, 1);
  glColor4f(.1, .2, .3, .3);
  glBegin(GL_TRIANGLES);
  glColor3ub(255, 0, 0);
  glVertex3f(0, 0, -5);
  glColor3ub(0, 255, 0);
  glVertex3f(5, 0, -5);
  glColor3ub(0, 0, 255);
  glVertex3f(0, 5, -5);
  glEnd();
  glPopMatrix();
  }

}

void Arena::draw(void) {

  char buffer[50] = {};
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawRainbowTriangle();

  glColor4f(.1, .2, .3, .3);
  //drawing the floor
  for(int x  = 0; x < 20; ++x) {
    for(int y  = 0; y < 20;++y) {
      glPushMatrix();
      glTranslatef(x, y - 1, -y);
      glutSolidCube(1);
      glPopMatrix();
    }
  }

  snake->draw();
  obstacle->draw();
  fruit->draw();
  glColor3ub(255, 255, 255);
  sprintf(buffer, "%d", score);
  font->bitmap_output(0, 12, "3D Nibbles");
  font->bitmap_output(0, 11, "Score:");
  font->bitmap_output(0, 10, buffer);

  sprintf(buffer, "%d", static_cast<int>(obstacle->item.size()));
  font->bitmap_output(15, 12, "Total obstacles");
  font->bitmap_output(16, 11, buffer);

}

/*F***********************************************************
 * correct_fruit(void)
 *
 * PURPOSE : fruit does not spawn on top of snake
 *
 * NOTES :   will require recursion
 *F*/
void Arena::correct_fruit(void) {

  for(snake->iter = snake->body.begin();
      snake->iter != snake->body.end();
      ++snake->iter) {
    if(fruit->getX() == snake->iter->getX() &&
       fruit->getY() == snake->iter->getY()) {
      delete[] fruit;
      fruit = new Fruit();
      correct_fruit();
    }
  }
}

/*F***********************************************************
 * correct_obstacle(void)
 *
 * PURPOSE : ensures that the fruit does not spawn on the
 *           obstacle
 *
 *
 * NOTES :   will require recursion
 *F*/
void Arena::correct_obstacle(void) {

  //obstacle and fruit are not on the same spot
  for(obstacle->iter = obstacle->item.begin();
      obstacle->iter != obstacle->item.end();
      ++obstacle->iter) {
    if(fruit->getX() == obstacle->iter->getX() &&
       fruit->getY() == obstacle->iter->getY()) {
      delete[] fruit;
      fruit = new Fruit();
      correct_fruit();
    }
  }
}

/*F***********************************************************
 * correct_
 *
 * PURPOSE :
 *
 *
 *
 * NOTES :   will require recursion
 *F*/
void Arena::correct_snake(void) {

}

/*F***********************************************************
 * correct_elements
 *
 * PURPOSE : gives the user a clean spawn with nothing on
 *           top of the snake or right next to it as it
 *           spawns
 *
 * NOTES :   will require recursion
 *F*/
inline void Arena::correct_elements(void) {
  correct_fruit();
  correct_obstacle();
  correct_snake();
}

/*F***********************************************************
 * DEFAULT CONSTRUCTOR
 *
 * NOTES :
 *F*/
Arena::Arena(void) {
  rot      = 0;
  score    = 0;
  font     = new Font();
  snake    = new Snake();
  obstacle = new Obstacle();
  fruit    = new Fruit();
  correct_elements();
}

/*F***********************************************************
 * DESTRUCTOR
 *
 * NOTES :
 *F*/
Arena::~Arena(void) {
  delete[] this;
}

/*F***********************************************************
 * update(void)
 *
 * PURPOSE : checks all possible events that could of occured
 *           in the arena
 *
 * RETURN :  void
 *
 * NOTES :
 *F*/
void Arena::update(void) {

  snake->update();
  if(is_snake_dead()) {
    snake    = new Snake();
    obstacle = new Obstacle;
    fruit    = new Fruit();
    score = 0;
  }

  correct_obstacle();

  if(is_snake_eating()) {
    if(fruit != NULL) {
      delete[] fruit;
    }
    fruit = new Fruit();
    correct_fruit();
    correct_obstacle();
    snake->grow(2);
    score++;
  }
  draw();
}
