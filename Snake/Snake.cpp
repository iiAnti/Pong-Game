#include "raylib.h"

struct Ball //this allows us to hold variables and methods
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, RED); // set the color as created the circle
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;
	int score;
	

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 }; //created the paddle
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), GREEN); //calls the rectangle 
	}
};



int main()
{
	InitWindow(800, 600, "Pong"); //this creates the window
	SetWindowState(FLAG_VSYNC_HINT); //flag to update as fsat as your local machine

	Ball ball; //ball info
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 250;
	ball.speedY = 250;

	Paddle leftPaddle; //the paddle info
	leftPaddle.x = 50; //where it is in the x and y axis
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 600; //speed of paddle


	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 600;

	const char* winnerText = nullptr; //variable to announce winner
	const char* player1 = "Player One"; //varibale to draw the player
	const char* player2 = "Player Two";
	const char* playerScore1 = "0";
	const char* playerScore2 = "0";

	while (!WindowShouldClose()) // this is while we still have the window open 
	{
		ball.x += ball.speedX * GetFrameTime(); //helps makeup for FPS
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1; //this makes the ball go the other way when hitting top or bottom 
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (leftPaddle.y < 0) //this is how we get the paddle to stop at the top.... still working out the bottom section
			leftPaddle.y = 0;
		} 
		if (leftPaddle.y < -1)
		{
			leftPaddle.y = -1;
		}

		if (rightPaddle.y < 0)
		{
			rightPaddle.y = 0;
		}


		if (IsKeyDown(KEY_W)) //this is how we call the paddles to move
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect())) //checks if the ball touches a paddle
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f; //redirectst the ball
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX; //this helps th ball not stay linear
			}
		}

		if (ball.x < 0)
		{
			winnerText = "Player Two Wins!"; //conditional for winner of the match
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Player One Wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2; //drew the ball
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 250; //speed of ball
			ball.speedY = 250;
			winnerText = nullptr;
		}


		BeginDrawing(); //start a drawing 
		ClearBackground(BLACK); //this allows us to color the background

		ball.Draw(); //draw the objects
		leftPaddle.Draw();
		rightPaddle.Draw();
		

		DrawText(player2, 500, 10, 25, YELLOW); //position of player name
		DrawText(player1, 150, 10, 25, YELLOW);

		DrawText(playerScore2, 500, 35, 25, YELLOW);
		DrawText(playerScore1, 150, 30, 25, YELLOW);

		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, SKYBLUE);
		}

		DrawFPS(350, 10); //shows FPS
		EndDrawing(); //end the events and drawing
	}

	CloseWindow(); //this closes the window when done 

	return 0;
}