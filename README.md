# Simple Physics Ball (Raylib)

A lightweight 2D physics engine written in C using Raylib.\
It simulates a draggable ball with real physics based gravity, other forces acting on the ball and mouse-based throwing.

## Features

-   Gravity-based ball movement
-   Other forces acting on the ball like friction *and hope fully drag soon.*
-   Click and drag the ball with the mouse
-   Release the mouse to throw the ball using cursor velocity
-   Real-time velocity and FPS display
-   Press `SPACE` to reset the ball position

## Controls

-   **Left Mouse Button** --- drag the ball
-   **Release Mouse** --- throw the ball
-   **SPACE** --- reset the ball position

## Requirements

-   C compiler (`gcc` or `clang`)
-   Raylib installed

## Build

Example using GCC:

``` bash
gcc main.c -o game -lraylib -lm -lpthread -ldl -lrt -lX11
```

## Run

``` bash
./game
```

## Project Structure

-   `main.c` --- main application and physics logic

## Notes

The project uses physics based gravity and mouse velocity calculations to
create a lightweight 2D physics engine.
