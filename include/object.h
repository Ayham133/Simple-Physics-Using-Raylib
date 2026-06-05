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
}Object;

bool CheckCollisionWithGround(float centerY, int raduis, int window_height);
bool CheckCollisionWithRightWindowEdge(float centerX, int raduis, int window_width, float velocityX);
bool CheckCollisionWithLeftWindowEdge(float centerX, int raduis, float velocityX);

#endif