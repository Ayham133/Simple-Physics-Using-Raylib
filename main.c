#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define GRAVITY 500.0f
#define INITILA_VELOCITY_X -100
#define INITILA_VELOCITY_Y 100
#define INITILA_POSITION_X 400
#define INITILA_POSITION_Y 300

typedef struct Ball {
	Vector2 position;
	Vector2 Velocity;
	Vector2 Force;
	int raduis;
	float mass;
} Ball;

bool CollisionWithGroundCircle(Vector2 center, int raduis, int window_height);
bool CheckCollisionWithGroundCirlcle(int ceterY, int raduis, int window_height);
bool CheckCollisionWithRightWindowEdgeCircle(float centerX, int raduis, int window_width, float velocityX);
bool CheckCollisionWithLeftWindowEdgeCicle(float centerX, int raduis, float velocityX);

int main(void) {

	const int window_width = 800;
	const int window_height = 600;

	InitWindow(window_width, window_height, "Simple Physics");

	const Vector2 GRAVITATIONAL_FORCE = {0.0f, 9.8f};

	Ball ball = {
		.position = {window_height/2, window_width/2},
		.Velocity = {0,0},
		.Force = {0,0},
		.raduis = 50,
		.mass = 10.0f
	};

	Vector2  prevMousePos = GetMousePosition();
	Vector2 mouseVelocity = {0.0f, 0.0f};
	bool dragging = false;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Update Loop.

		// Get current mouse position
		Vector2 currentMousePos = GetMousePosition();

		//---- Physics. ----
		float dt = GetFrameTime();
		float const Weight = ball.mass * GRAVITATIONAL_FORCE.y;
		float const Normal = -Weight;
		float const Mue = 5.0f;
		float VelociytMagnitude; 
		float KenaticEnergy;
		float restitution = 0.8f;


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

		/**
		 *
		 * 
		 * Ball physics
		 *
		 */

		 /**
		  * 
		  * Y-axis Forces and Collisions
		  * 
		  */
		if (!CollisionWithGroundCircle(ball.position, ball.raduis, window_height) && !dragging) {
			ball.Force.y += Weight;
		} else {
			ball.Force.y = 0;
			ball.Velocity.y = 0;
		}

		/**
		 * 
		 * X-axis Forces and Collision  
		 * 
		 */

		// Right wall Collision and Bouncing
		if (CheckCollisionWithRightWindowEdgeCircle(ball.position.x, ball.raduis, window_width, ball.Velocity.x) && !dragging)
		{
			// Correct penetration, snapping the ball back by (window_width - ball.raduis)/ the exact position where the ball touches the wall.
			ball.position.x = window_width - ball.raduis;
			// Bounce, by the equation v' = -e * v
			ball.Velocity.x *= -restitution;
		}

		// Left wall Collision and Bouncing
		if (CheckCollisionWithLeftWindowEdgeCicle(ball.position.x, ball.raduis, ball.Velocity.x) && !dragging)
		{
			// Correct penetration, snapping the ball back by (ball.raduis)/ the exact position where the ball touches the wall.
			ball.position.x = ball.raduis;
			// Bounce, by the equation v' = -e * v
			ball.Velocity.x *= -restitution;
		}

		// Frinction force when the object (ball) is on the ground
		if (CollisionWithGroundCircle(ball.position, ball.raduis, window_height) && !dragging)
		{
			float friction = Mue * Normal;

			// Check if the friction will cause an overshoot.
			if (fabs(ball.Velocity.x) < friction)
				ball.Velocity.x = 0.0f;
			else
			{
				if (ball.Velocity.x > 0.0f)
					ball.Force.x = friction;
				else 
					ball.Force.x = -friction;
			}
		}

		// Fixing the small Velocity bug (Computers don't know when it's trully zero)
		if(fabs(ball.Velocity.x) < 0.5f){
			ball.Velocity.x = 0.0f;
			ball.Force.x = 0;
		}

		// Applying and updating Velocity vector and position vector.
		ball.Velocity.y += (ball.Force.y / ball.mass) * dt;
		ball.Velocity.x += (ball.Force.x/ ball.mass) * dt;

		ball.position.y += ball.Velocity.y * dt;
		ball.position.x += ball.Velocity.x * dt;

		// Reset the ballPositionY
		if (IsKeyDown(KEY_SPACE)) {
			ball.position.y = 100;
			ball.position.x = window_width/2;
			ball.Force = (Vector2){.x = 0.0f, .y = 0.0f};
			ball.Velocity = (Vector2){.x = 0.0f, .y = 0.0f};
		}



		/**
		 * 
		 * Drawing and rendering.
		 * 
		 */
		float ballVelocityX = ball.Velocity.x;
		float ballVelocityY = ball.Velocity.y;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText(TextFormat("Ball's Velocity {%f, %f}, FPS: %i",ballVelocityX, ballVelocityY, GetFPS()),10, 10, 20, BLACK);
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


bool CollisionWithGroundCircle(Vector2 center, int raduis, int window_height) {
	return (center.y > window_height - raduis);
}

bool CheckCollisionWithRightWindowEdgeCircle(float centerX, int raduis, int window_width, float velocityX){
	return (centerX + raduis >= window_width && velocityX > 0.0f);
}

bool CheckCollisionWithLeftWindowEdgeCicle(float centerX, int raduis, float velocityX){
	return (centerX - raduis <= 0.0f && velocityX < 0.0f);
}