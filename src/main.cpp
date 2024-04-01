#include <raylib.h>

int main()
{
    InitWindow(750, 750, "Snake");
    SetTargetFPS(240);

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}