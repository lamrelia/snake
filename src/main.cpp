#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color Red = {230, 41, 55, 255};
Color Green = {0, 228, 48, 255};
Color Black = {0, 0, 0, 255};

int CellSize = 30;
int CellCount = 25;

class Food
{
public:
    Vector2 position;

    Food()
    {
        position = GenerateRandomPosition();
    }

    void Draw()
    {
        DrawCircle(position.x * CellSize, position.y * CellSize, CellSize / 2, Red);
    }

    Vector2 GenerateRandomPosition()
    {
        float x = GetRandomValue(0, CellCount - 1);
        float y = GetRandomValue(0, CellCount - 1);
        return Vector2{x, y};
    }
};

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = Vector2{1, 0};

    void Draw()
    {
        for (size_t i = 0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, Green);
        }
    }

    void Update()
    {
        static float delay = 0.2f;
        static float elapsedTime = 0.0f;

        elapsedTime += GetFrameTime();
        if (elapsedTime > delay)
        {
            elapsedTime -= delay;
            body.pop_back();
            Vector2 newHead = Vector2Add(body.front(), direction);
            body.push_front(newHead);
        }
    }
};

int main()
{
    InitWindow(CellSize * CellCount, CellSize * CellCount, "Snake");
    SetTargetFPS(240);

    Food food = Food();
    Snake snake = Snake();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        snake.Update();
        ClearBackground(Black);
        food.Draw();
        snake.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}