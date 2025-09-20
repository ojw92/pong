// main.cpp : entry point for the pong application

#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{ 38, 185, 154, 255 };
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };
Color Yellow = Color{ 243, 213, 91, 255 };

int player_score = 0;
int cpu_score = 0;

class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, Yellow);			// int centerX, int centerY, float radius, Color color
	}

	void Update() {
		x += speed_x;	// move ball position by 7 pixels
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth()) {	// cpu wins
			cpu_score++;
			ResetBall();
		}
		if (x - radius <= 0) {	// player wins
			player_score++;
			ResetBall();
		}
	}

	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1, 1 };	// speed of -1 or 1
		speed_x *= speed_choices[GetRandomValue(0, 1)];		// min, max
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};

class Paddle {
protected:		// This method is protected and thus no other program should know about it; it'll be inherited by CpuPaddle later
	void LimitMovement() {
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		//DrawRectangle(x, y, width, height, WHITE);	// int posX, int posY, int width, int height, Color color
		DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);	// Rectangle rec, float roundness, int segments, Color color
	}

	void Update() {
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}
		LimitMovement();
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
		LimitMovement();
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

		// Checking for collisions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {	// Vector2 center, float radius, Rectangle rec
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
			ball.speed_x *= -1;
		}

		// Drawing
		ClearBackground(Dark_Green);		// prevent ball from leaving traces
		DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);		// fill the right half of the field with Green
		DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
		DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);	// int startPosX, int startPosY, int endPosX, int endPosY, Color color
		ball.Draw();
		cpu.Draw();
		player.Draw();
		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);	// text, xpos, ypos, fontsize, color
		DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

// Reference: https://www.youtube.com/watch?v=W9VxRRtC_-U
//			  https://www.youtube.com/watch?v=VLJlTaFvHo4