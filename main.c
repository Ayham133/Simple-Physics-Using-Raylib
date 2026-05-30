#include "raylib.h"
#include <stdlib.h>

#define GRAVITY 500.0f

typedef struct Ball {
  Vector2 position;
  Vector2 Velocity;
  int raduis;
} Ball;

int main(void) {

  const int window_width = 800;
  const int window_height = 600;

  InitWindow(window_width, window_height, "Simple Physics");

  Ball ball = {{400, 100}, {100, 0}, 50};
  int ballVelocityX = ball.Velocity.x;
  int ballVelocityY = ball.Velocity.y;
  int ballPositionX = ball.position.x;
  int ballPositionY = ball.position.y;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update Loop.
    ballVelocityX = ball.Velocity.x;
    ballVelocityY = ball.Velocity.y;
    ballPositionX = ball.position.x;
    ballPositionY = ball.position.y;

    // Physics.
    float dt = GetFrameTime();
    if (ballPositionY <= window_height - ball.raduis &&
        !(IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
      ball.Velocity.y += GRAVITY * dt;
      ball.position.y += ball.Velocity.y * dt;
    } else {
      ball.Velocity.y = 0;
    }

    // Reset the ballPositionY
    if (IsKeyDown(KEY_SPACE)) {
      ball.position.y = 100;
    }
    // Make the ball followes the Cursor
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      ball.position = GetMousePosition();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("X: %i, Y: %i, FPS: %i", ballPositionX, ballVelocityY,
                        GetFPS()),
             10, 10, 20, BLACK);
    DrawCircleV(ball.position, ball.raduis, RED);

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
