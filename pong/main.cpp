// main.cpp : entry point for the pong application

#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);			// int centerX, int centerY, float radius, Color color
	}

	void Update() {
		x += speed_x;	// move ball position by 7 pixels
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth() || x - radius <= 0) {
			speed_x *= -1;
		}
	}
};

class Paddle {
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);	// int posX, int posY, int width, int height, Color color
	}

	void Update() {
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}

		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
};

class CpuPaddle: public Paddle {		// define CpuPaddle class that inherits all attributes & methods from Paddle class
public:
	void Update(int ball_y) {
		// Rudimentary artificial intelligence algorithm
		// If paddle is below the ball, move up, and vice versa
		if (y + height / 2 > ball_y) {
			y = y - speed;
		}
		if (y + height / 2 < ball_y) {
			y = y + speed;
		}
	}
};

Ball ball;		// Create an instance of Ball called ball
Paddle player;
CpuPaddle cpu;

int main()
{
	cout << "Starting the game. Are you ready?" << endl;
	const int screen_width = 1280;
	const int screen_height = 800;
	const int paddle_offset = 10;
	InitWindow(screen_width, screen_height, "The pong");
	SetTargetFPS(60);		// lock 60 fps; otherwise every computer will run program as fast as it can

	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	player.width = 25;
	player.height = 120;
	player.x = screen_width - paddle_offset - player.width;
	player.y = (screen_height - player.height)/2;
	player.speed = 6;

	cpu.height = 120;
	cpu.width = 25;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 6;

	while (WindowShouldClose() == false) {		// WindowShouldClose() checks if esc key is pressed or X on the window is clicked - in which case it returns true 
		BeginDrawing();

		// Updating
		ball.Update();
		cpu.Update(ball.y);
		player.Update();

		// Drawing
		ClearBackground(BLACK);		// prevent ball from leaving traces
		DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);	// int startPosX, int startPosY, int endPosX, int endPosY, Color color
		ball.Draw();
		cpu.Draw();
		player.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
