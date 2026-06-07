#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include "raylib.h"

typedef struct 
{
    Vector2 position;
	Vector2 Velocity;
	Vector2 Force;
	int raduis;
	float mass;
	bool collision;
}Object;

bool CheckCollisionWithGround(float centerY, int raduis, int window_height);
bool CheckCollisionWithRightWindowEdge(float centerX, int raduis, int window_width, float velocityX);
bool CheckCollisionWithLeftWindowEdge(float centerX, int raduis, float velocityX);

/**
 * @brief Calculte collision between two objects and return true if collision detected, false otherwise.
 * 
 * @param[in] ball1		First ball.
 * @param[in] ball2		Second ball.
 * @return bool 		true if collision detected, false otherwise. 
 */
bool CheckCollisionWithBallV(Object *ball1, Object *ball2);

#endif