#include "raylib.h"
struct Ball
{
    float x, y; 
   float  speedX, speedY;
    float rad;


    void Draw()
    {
        DrawCircle((int) x , (int) y, rad, RED );
    }
};

struct Paddle
{
    float x, y;
    float speed;    
    float width, height; 

    Rectangle GetRect()
    {
        return Rectangle{ x - width / 2 , y - height / 2, 10, 100 }; 
    }

    void Draw()
    {
        DrawRectangleRec(GetRect(), YELLOW);
    }
};

int main(void)
{
    InitWindow(1200, 800, "Pong Pong");
    SetWindowState(FLAG_VSYNC_HINT);
    Ball ball;
        ball.x = GetScreenWidth () / 2.0f ;
        ball.y = GetScreenHeight() / 2.0f ;
        ball.rad = 10 ;
        ball.speedX = 300;
        ball.speedY = 300;


        Paddle leftPaddle;
        leftPaddle.x = 50;
        leftPaddle.y = GetScreenHeight() / 2 ; 
        leftPaddle.width = 10;
        leftPaddle.height = 100;
        leftPaddle.speed = 500;

        Paddle rightPaddle;
        rightPaddle.x = GetScreenWidth() - 50 ;
        rightPaddle.y = GetScreenHeight() / 2 ; 
        rightPaddle.width = 10;
        rightPaddle.height = 100;
        rightPaddle.speed = 500;

        const char* winnerText = nullptr; 
    while (!WindowShouldClose())
    {
        ball.x += ball.speedX * GetFrameTime();
        ball.y += ball.speedY * GetFrameTime();

        if (ball.y < 0)
        {
            ball.y = 0;
            ball.speedY *= -1;
        }
        if (ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1; 
        }
        if (IsKeyDown(KEY_W))
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
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.rad, leftPaddle.GetRect()))
        {
            if (ball.speedX < 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX  ;
            }
            
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.rad, rightPaddle.GetRect()))
        {
            if (ball.speedX > 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * - ball.speedX;
            }
            
        }
        if (ball.x < 0)
        {
            winnerText = "Mahdi Wins!";
        }
        if (ball.x > GetScreenWidth()) 
        {
            winnerText = "Obada Wins!";
        }
        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenWidth() / 2;
            ball.speedX = 250;
            ball.speedY = 250;
            winnerText = nullptr;
        }


        BeginDrawing();
        ClearBackground(GREEN );
        ball.Draw(); 
        leftPaddle.Draw();
        rightPaddle.Draw();
        if (winnerText)
        {
            int textWidth = MeasureText(winnerText, 60 );
            DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, RED );
        }

        DrawFPS(10 ,10 );
        EndDrawing();
    }

    CloseWindow();
    return 0;
}   