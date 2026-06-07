#include "raylib.h"
#include "include/object.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void initWindowHelper(int window_width, int window_height, char *window_title) {
	InitWindow(window_width, window_height, window_title);
}

int main(void) {

	const int window_width = 800;
	const int window_height = 600;
	initWindowHelper(window_width, window_height, "Physics Engine 1.0");

	const float GRAVITATIONAL_ACCELERATION= 980.0f; // Pixiles

	const int OBJECT_COUNT = 6;

	Object *objects = malloc(OBJECT_COUNT * (sizeof *objects));
	objects[0] = (Object){
		.position = {window_width/2, window_height/2},
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {-100.0f, 0.0f},
		.collision = false

	};

	objects[1] = (Object){
		.position = {100, 200},
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {-180.0f, 0.0f},
		.collision = false

	};

	objects[2] = (Object){
		.position = {200, 50},
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {70.0f, 0.0f},
		.collision = false

	};
	objects[3] = (Object){
		.position = {300, 100},
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {-120.0f, 0.0f},
		.collision = false

	};
	objects[4] = (Object){
		.position = {500,550}, 
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {50.0f, 0.0f},
		.collision = false

	};
	objects[5] = (Object){
		.position = {700, 450},
		.Force = {0.0f, 0.0f},
		.mass = 10.0f,
		.raduis = 50,
		.Velocity = {200.0f, 0.0f},
		.collision = false

	};

	int draggingIndex =-1; 
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
		float const Mue = 5.0f;
		float restitution = 0.8f;


		// Calculate mouse velocity
		if(dt > 0.0f){
			mouseVelocity.x = (currentMousePos.x - prevMousePos.x)/dt;
			mouseVelocity.y = (currentMousePos.y - prevMousePos.y)/dt;
		}

		prevMousePos = currentMousePos;
		// Handle dragging logic outside the loop to ensure only one object is dragged at a time
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && draggingIndex == -1)
		{
			for (int i = 0; i < OBJECT_COUNT; i++)
			{
				if (CheckCollisionPointCircle(objects[i].position, GetMousePosition(), 50.0f))
				{
					draggingIndex = i;
					dragging = true;
					objects[i].position = GetMousePosition();
					objects[i].Force = (Vector2){0, 0};
					objects[i].Velocity = (Vector2){0, 0};
					break;
				}
			}
		}
		else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && draggingIndex != -1)
		{
			objects[draggingIndex].position = GetMousePosition();
			objects[draggingIndex].Force = (Vector2){0, 0};
			objects[draggingIndex].Velocity = (Vector2){0, 0};
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && draggingIndex != -1)
		{
			objects[draggingIndex].Velocity = mouseVelocity;
			draggingIndex = -1;
			dragging = false;
		}

		for (int i = 0; i < OBJECT_COUNT; i++)
		{
			float const Weight = objects[i].mass * GRAVITATIONAL_ACCELERATION;
			// calculating the net applayed forces each farme and store them in the objects[i].Force
			Vector2 ApplayedForces = (Vector2){0.0f, 0.0f};


			/**
			 *
			 *
			 * objects[i].physics
			 *
			 */

			/**
			 *
			 * Y-axis Forces and Collisions
			 *
			 * v = v + a *dt
			 *
			 */

			// When the objects[i].is in free fall.
			// Only skip physics for the object currently being dragged.
			if (!CheckCollisionWithGround(objects[i].position.y, objects[i].raduis, window_height) && i != draggingIndex)
			{
				ApplayedForces.y += Weight;
				objects[i].Force.y += ApplayedForces.y;

				objects[i].Velocity.y += GRAVITATIONAL_ACCELERATION * dt;
				objects[i].position.y += objects[i].Velocity.y * dt;
			}

			// When the objects[i].hits the ground the forces in the y-axis is zero thus the velocity should be zero
			if (CheckCollisionWithGround(objects[i].position.y, objects[i].raduis, window_height) && i != draggingIndex)
			{
				objects[i].Force.y = 0;

				if (fabs(objects[i].Velocity.y) < 0.9f)
				{
					objects[i].Velocity.y = 0.0f;
					objects[i].position.y = window_height - objects[i].raduis;
				}
				else
				{
					objects[i].Velocity.y *= -restitution;
					objects[i].position.y += objects[i].Velocity.y * dt;
				}
			}

			/**
			 *
			 * X-axis Forces and Collision
			 *
			 * updating the x postion is on the line  183
			 */

			// When in free fall the horizontal forces should be zero.
			if (!CheckCollisionWithGround(objects[i].position.y, objects[i].raduis, window_height) && i != draggingIndex)
			{
				objects[i].Force.x = 0;
			}
			// When the objects[i].on the ground add friction.
			if (CheckCollisionWithGround(objects[i].position.y, objects[i].raduis, window_height) && i != draggingIndex)
			{
				// friction force
				float FrictionForce = 30.0f;
				// update the forces on the objects[i].
				objects[i].Force.x = Mue * Weight;
				// calculate the magnatued of the objects[i].Velocity vector.
				float Velocity = sqrtf((objects[i].Velocity.x * objects[i].Velocity.x) + (objects[i].Velocity.y * objects[i].Velocity.y));

				// apply friction just when the objects[i].is moveing along the x-axis
				if (Velocity > 0.0f)
				{
					float speedReduction = FrictionForce * dt;

					// stop friction when the speed smaller than the force of friction (just stop the objects[i].bro).
					if (Velocity <= speedReduction)
					{
						objects[i].Velocity.x = 0.0f;
						objects[i].Force.x = 0;
					}
					// else apply the friction calculated.
					else
					{
						objects[i].Velocity.x -= (objects[i].Velocity.x / Velocity) * speedReduction;
					}
				}
			}

			// Right wall Collision and Bouncing
			if (CheckCollisionWithRightWindowEdge(objects[i].position.x, objects[i].raduis, window_width, objects[i].Velocity.x) && i != draggingIndex)
			{
				// Correct penetration, snapping the objects[i].back by (window_width - ball.raduis)/ the exact position where the ball touches the wall.
				objects[i].position.x = window_width - objects[i].raduis;
				// Bounce, by the equation v' = -e * v
				objects[i].Velocity.x *= -restitution;
			}

			// Left wall Collision and Bouncing
			if (CheckCollisionWithLeftWindowEdge(objects[i].position.x, objects[i].raduis, objects[i].Velocity.x) && i != draggingIndex)
			{
				// Correct penetration, snapping the objects[i].back by (ball.raduis)/ the exact position where the ball touches the wall.
				objects[i].position.x = objects[i].raduis;
				// Bounce, by the equation v' = -e * v
				objects[i].Velocity.x *= -restitution;
			}

			// updating the x position of the objects[i].after all the calculation of the ball.Velocity.x
			objects[i].position.x += objects[i].Velocity.x * dt;

			// Reset the objects[i].ositionY
			if (IsKeyDown(KEY_SPACE))
			{
				objects[i].position.y = 100;
				objects[i].position.x = window_width / 2;
				objects[i].Force = (Vector2){.x = 0.0f, .y = 0.0f};
				objects[i].Velocity = (Vector2){.x = 0.0f, .y = 0.0f};
			}

			for (int j = 0; j < OBJECT_COUNT; j++)
			{
				if(i == j)
					continue;

				if (CheckCollisionWithBallV(&objects[i], &objects[j]))
				{
					objects[i].collision = true;
					printf("collison happend between %d, and %d\n", i, j);
				}
			}
			

			
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (int i = 0; i < OBJECT_COUNT; i++)
		{
			/**
			 *
			 * Drawing and rendering.
			 *
			 */
			// float ballVelocityX = objects[i].Velocity.x;
			// float ballVelocityY = objects[i].Velocity.y;

			// DrawText(TextFormat("objects[i].s Velocity {%.3f, %.3f}, FPS: %i", ballVelocityX, ballVelocityY, GetFPS()), 10, 10, 20, BLACK);
			DrawText(TextFormat("Mouse Velocity: {%.3f, %.3f}", mouseVelocity.x, mouseVelocity.y), 10, 40, 20, GRAY);
			if (dragging)
				DrawText("Dragging: enabled", 10, 60, 20, GREEN);
			else
				DrawText("Dragging: disabled", 10, 60, 20, RED);

			DrawText("Click space to reset the y position of the objects[i]..", 10, 80, 20, LIGHTGRAY);

			DrawCircleV(objects[i].position, objects[i].raduis, RED);
		}
		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
