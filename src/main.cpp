#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color Red = {230, 41, 55, 255};
Color Green = {0, 228, 48, 255};
Color Black = {0, 0, 0, 255};

int CellSize = 30;
int CellCount = 25;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
};

class Food
{
public:
    Vector2 position;

    Food(deque<Vector2> SnakeBody)
    {
        position = GenerateRandomPosition(SnakeBody);
    }

    void Draw()
    {
        DrawRectangle(position.x * CellSize, position.y * CellSize, CellSize, CellSize, Red);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, CellCount - 1);
        float y = GetRandomValue(0, CellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPosition(deque<Vector2> SnakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, SnakeBody))
        {
            position = GenerateRandomCell();
        }

        return position;
    }
};

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = Vector2{1, 0};
    bool AddBody = false;

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
        if (AddBody == true)
        {
            body.push_front(Vector2Add(body[0], direction));
            AddBody = false;
        }
        else
        {
            static float delay = 0.1f;
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
    }

    void HandleInput()
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            if (direction.x != -1)
            {
                direction = Vector2{1, 0};
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            if (direction.x != -1)
            {
                direction = Vector2{-1, 0};
            }
        }
        else if (IsKeyDown(KEY_UP))
        {
            if (direction.y != -1)
            {
                direction = Vector2{0, -1};
            }
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            if (direction.y != -1)
            {
                direction = Vector2{0, 1};
            }
        }
    }
};

class Game
{
public:
    Food food = Food(snake.body);
    Snake snake = Snake();

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        snake.Update();
        CheckFoodEaten();
        CheckBorderCollision();
    }

    void HandleInput()
    {
        snake.HandleInput();
    }

    void CheckFoodEaten()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPosition(snake.body);
            snake.AddBody = true;
        }
    }

    void CheckBorderCollision()
    {
        if (snake.body[0].x == CellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        else if (snake.body[0].y == CellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        CloseWindow();
    }
};

int main()
{
    InitWindow(CellSize * CellCount, CellSize * CellCount, "Snake");
    SetTargetFPS(240);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        game.HandleInput();
        game.Update();
        ClearBackground(Black);
        game.Draw();
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}