#include "raylib.h"
#include <stdlib.h>

#define GRAVITY 500.0f
#define INITILA_VELOCITY_X -100
#define INITILA_VELOCITY_Y 100
#define INITILA_POSITION_X 400
#define INITILA_POSITION_Y 300

typedef struct Ball {
	Vector2 position;
	Vector2 Velocity;
	int raduis;
} Ball;

bool CollisionWithGroundCircle(Vector2 center, int raduis, int window_height);

int main(void) {

	const int window_width = 800;
	const int window_height = 600;

	InitWindow(window_width, window_height, "Simple Physics");

	Ball ball = {{INITILA_POSITION_X, INITILA_POSITION_Y},{INITILA_VELOCITY_X, INITILA_VELOCITY_Y},50};
	int ballVelocityX = ball.Velocity.x;
	int ballVelocityY = ball.Velocity.y;
	int ballPositionX = ball.position.x;
	int ballPositionY = ball.position.y;

	Vector2  prevMousePos = GetMousePosition();
	Vector2 mouseVelocity = {0.0f, 0.0f};
	bool dragging = false;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Update Loop.
		ballVelocityX = ball.Velocity.x;
		ballVelocityY = ball.Velocity.y;
		ballPositionX = ball.position.x;
		ballPositionY = ball.position.y;

		// Get current mouse position
		Vector2 currentMousePos = GetMousePosition();

		//---- Physics. ----
		float dt = GetFrameTime();

		// Calculate mouse velocity
		if(dt > 0.0f){
			mouseVelocity.x = (currentMousePos.x - prevMousePos.x)/dt;
			mouseVelocity.y = (currentMousePos.y - prevMousePos.y)/dt;
		}

		prevMousePos = currentMousePos;

		// Make the ball followes the Cursor when Collision happen
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(ball.position, GetMousePosition(), 50.0f)){
			dragging = true;
			ball.position = GetMousePosition();
		}

		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
			dragging = false;
			ball.Velocity = mouseVelocity;
		}

		// Ball physics 
		if (CollisionWithGroundCircle(ball.position, ball.raduis, window_height) && !dragging) {// on Y-axis
			ball.Velocity.y += GRAVITY * dt;
			ball.position.y += ball.Velocity.y * dt;
		} else {
			ball.Velocity.y = 0;
		}
		if (ballPositionX <= window_width - ball.raduis && ballPositionX >= 0 + ball.raduis && !dragging)  {// on X-axis
			ball.position.x += ball.Velocity.x * dt;
		} else
			ball.Velocity.x = 0;

		// Reset the ballPositionY
		if (IsKeyDown(KEY_SPACE)) {
			ball.position.y = 100;
			ball.Velocity.x = 0;
			ball.Velocity.y = 0;
		}




		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText(TextFormat("Ball's Velocity {%i, %i}, FPS: %i", ballVelocityX, ballVelocityY, GetFPS()),10, 10, 20, BLACK);
		DrawText(TextFormat("Mouse Velocity: {%.3f, %.3f}", mouseVelocity.x, mouseVelocity.y), 10, 40, 20, GRAY);
		if(dragging)
			DrawText("Dragging: enabled", 10, 60, 20, GREEN);
		else
			DrawText("Dragging: disabled", 10, 60, 20, RED);

		DrawText("Click space to reset the y position of the ball!.", 10, 80, 20, LIGHTGRAY);

		DrawCircleV(ball.position, ball.raduis, RED);

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}


bool CollisionWithGroundCircle(Vector2 center, int raduis, int window_height) 
{
	return (center.y<= window_height - raduis);
}