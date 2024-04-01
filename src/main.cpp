#include <raylib.h>
#include <deque>

using namespace std;

Color Red = {230, 41, 55, 255};
Color Green = {0, 228, 48, 255};

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

    void Draw()
    {
        for (size_t i = 0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, Green);
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
        food.Draw();
        snake.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}