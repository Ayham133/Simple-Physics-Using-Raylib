# Simple Physics Ball (Raylib)

A small physics demo written in C using Raylib.\
It simulates a draggable ball with gravity and mouse-based throwing.

## Features

-   Gravity-based ball movement
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
gcc main.c -o physics_demo -lraylib -lm -lpthread -ldl -lrt -lX11
```

## Run

``` bash
./physics_demo
```

## Project Structure

-   `main.c` --- main application and physics logic

## Notes

The project uses simple gravity and mouse velocity calculations to
create a lightweight physics interaction demo.
