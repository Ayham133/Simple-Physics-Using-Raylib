#include "object.h"
#include <stdbool.h>


bool CheckCollisionWithGround(float centerY, int raduis, int window_height){
	return (centerY >= window_height - raduis);
}

bool CheckCollisionWithRightWindowEdge(float centerX, int raduis, int window_width, float velocityX){
	return (centerX + raduis >= window_width && velocityX > 0.0f);
}

bool CheckCollisionWithLeftWindowEdge(float centerX, int raduis, float velocityX){
	return (centerX - raduis <= 0.0f && velocityX < 0.0f);
}