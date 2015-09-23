#include "Arena.hpp"

/*F***********************************************************
 * is_snake_eating(void)
 * 
 * PURPOSE : Determines collision between the snake and the fruit
 *           
 *
 * RETURN :  bool
 *
 * NOTES :   
 *F*/
bool Arena::is_snake_eating(void) {

  snake->i = snake->body.begin();
  
  if(snake->i->getX() == fruit->getX() &&
     snake->i->getY() == fruit->getY()) {
    return true;
  }
  return false;

}

/*F***********************************************************
 * is_snake_dead(void)
 * 
 * PURPOSE : inline function that checks if the snake is dead
 *
 * RETURN :  bool, true if dead, false if not
 *
 * NOTES :   needs to be expanded later to ensure the snake can collide
 *           with itself
 *F*/
bool Arena::is_snake_dead(void) {

  snake->i = snake->body.begin();

  int snake_headX = snake->i->getX();
  int snake_headY = snake->i->getY();
  
  //did we hit an obstacle?
  if(snake_headX == obstacle->getX() &&
     snake_headY == obstacle->getY()) {
    return true;
  }

  //are we out of the arena?
  if(snake_headX == 20 ||
     snake_headY == 20 ||
     snake_headX == -1 ||
     snake_headY == -2) {
    return true;
  }

  ++snake->i; //skip the head

  //self collision
  while(snake->i != snake->body.end()) {
    if(snake_headX == snake->i->getX() &&
       snake_headY == snake->i->getY()) {
      return true;
    }
    ++snake->i;
  }
  return false;
}

/*F***********************************************************
 * draw(void)
 * 
 * PURPOSE : draws the arena to the buffer
 *
 * RETURN :  void
 *
 * NOTES :   
 *F*/
void Arena::draw(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //drawing the floor
  for(int x  = 0; x < 20; ++x) {
    for(int y  = 0; y < 20;++y) {
      glColor4f(.1, .2, .3, .3);
      glPushMatrix();
      glTranslatef(x, y - 1, -y);
      glutSolidCube(1);
      glPopMatrix();
    }
  }

  snake->draw();
  obstacle->draw();
  fruit->draw();

  glFlush();
  glFinish();
}

Arena::Arena() {
  snake    = new Snake();
  obstacle = new Obstacle();
  fruit    = new Fruit();
}

Arena::~Arena() {
  if(snake != NULL) {
    delete[] snake;
  }
  if(obstacle != NULL) {
    delete[] obstacle;
  }
  if(fruit != NULL) {
    delete[] fruit;
  }
}

/*F***********************************************************
 * update_arena(void)
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
    obstacle = new Obstacle();
    fruit    = new Fruit();
  }

  if(is_snake_eating()) {
    if(fruit != NULL) {
      delete[] fruit;
    }
    fruit = new Fruit();
    snake->grow(2);
  }

  draw();
}
