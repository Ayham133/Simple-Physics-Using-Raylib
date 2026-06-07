#include "include/object.h"
#include <stdbool.h>
#include <math.h>


bool CheckCollisionWithGround(float centerY, int raduis, int window_height){
	return (centerY >= window_height - raduis);
}

bool CheckCollisionWithRightWindowEdge(float centerX, int raduis, int window_width, float velocityX){
	return (centerX + raduis >= window_width && velocityX > 0.0f);
}

bool CheckCollisionWithLeftWindowEdge(float centerX, int raduis, float velocityX){
	return (centerX - raduis <= 0.0f && velocityX < 0.0f);
}

/**
 * @brief Calculte collision between two objects and return true if collision detected, false otherwise.
 * 
 * @param[in] ball1		First ball.
 * @param[in] ball2		Second ball.
 * @return bool 		true if collision detected, false otherwise. 
 */
bool CheckCollisionWithBallV(Object *ball1, Object *ball2)
{
	int xComponenet = (ball1->position.x - ball2->position.x);
	int yComponenet = (ball1->position.y - ball2->position.y);

	return (xComponenet *xComponenet + yComponenet*yComponenet) <= (ball1->raduis * ball2->raduis);
}