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
bool CollisionWithWindowWidthCircle(Vector2 center, int raduis, int window_width);

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
		VelociytMagnitude = sqrt(pow(ball.Velocity.x, 2) + pow(ball.Velocity.y, 2));
		KenaticEnergy += 0.5 * ball.mass * VelociytMagnitude * VelociytMagnitude *dt;
		if (!CollisionWithGroundCircle(ball.position, ball.raduis, window_height) && !dragging) {// on Y-axis
			ball.Force.y += Weight;
		} else {
			ball.Force.y = 0;
			ball.Velocity.y = 0;
		}
		if(CollisionWithWindowWidthCircle(ball.position, ball.raduis, window_width) && !dragging)
			ball.Velocity.x = 0.0f;
		// Frinction force when the objec (ball) is on the ground
		if (CollisionWithGroundCircle(ball.position, ball.raduis, window_height) && !dragging)
		{
			float friction = Mue * Normal;

			// Apply friction to velocity
			if (ball.Velocity.x > 0.0f)
			{
				ball.Force.x = friction;

			}
			else if (ball.Velocity.x < 0.0f)
			{
				ball.Force.x = -friction;
			}
		}

		ball.Velocity.y += (ball.Force.y / ball.mass) * dt;
		ball.Velocity.x += (ball.Force.x/ ball.mass) * dt;

		// Prevent overshoot/jitter near zero
		if (fabs(ball.Velocity.x) < 0.1f )
		{
			ball.Velocity.x = 0.0f;
		}

		ball.position.y += ball.Velocity.y * dt;
		ball.position.x += ball.Velocity.x * dt;

		// Reset the ballPositionY
		if (IsKeyDown(KEY_SPACE)) {
			ball.position.y = 100;
			ball.position.x = window_width/2;
			ball.Force = (Vector2){.x = 0.0f, .y = 0.0f};
			ball.Velocity = (Vector2){.x = 0.0f, .y = 0.0f};
		}



		int ballVelocityX = ball.Velocity.x;
		int ballVelocityY = ball.Velocity.y;
		int TextKenaticEnergy = KenaticEnergy;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText(TextFormat("Ball's Velocity {%i, %i}, Ball's Kenatic: %i, FPS: %i",ballVelocityX, ballVelocityY, TextKenaticEnergy, GetFPS()),10, 10, 20, BLACK);
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

bool CollisionWithWindowWidthCircle(Vector2 center, int raduis, int window_width){
	return (center.x >= window_width - raduis || center.x - raduis <= 0 );
}