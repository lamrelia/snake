#include <raylib.h>

using namespace std;

Color Red = {230, 41, 55, 255};

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

int main()
{
    InitWindow(CellSize * CellCount, CellSize * CellCount, "Snake");
    SetTargetFPS(240);

    Food food = Food();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        food.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}