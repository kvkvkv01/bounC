#define UNICODE
#define _UNICODE
#define BLOCK_SIZE      15
#define BALL_RADIUS     7
#define WINDOW_WIDTH    1200
#define WINDOW_HEIGHT   900


#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const TCHAR CLSNAME[] = TEXT("bouncWClass");
LRESULT CALLBACK        winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

typedef struct s_ball
{
        float           x;
        float           y;
        float           dx;
        float           dy;
        int             is_white;
        float           speed;
} t_ball;

typedef struct s_game
{
        int             **grid;
        t_ball          *left_balls;
        t_ball          *right_balls;
        int             left_ball_count;
        int             right_ball_count;
        int             window_width;
        int             window_height;
        int             grid_rows;
        int             grid_cols;
        HDC             back_buffer;
        HBITMAP         back_bitmap;
} t_game;

t_game g_game;

void    init_game(t_game *game, int width, int height, HWND hwnd)
{
        int     row;
        int     col;
        HDC     hdc;

        ZeroMemory(game, sizeof(t_game));
        game->window_width = width;
        game->window_height = height;
        game->grid_cols = width / BLOCK_SIZE;
        game->grid_rows = height / BLOCK_SIZE;

        // Allocate grid dynamically
        game->grid = (int **)malloc(game->grid_rows * sizeof(int *));
        row = 0;
        while (row < game->grid_rows)
        {
                game->grid[row] = (int *)malloc(game->grid_cols * sizeof(int));
                row++;
        }

        // Initialize grid: left half black (1), right half white (0)
        row = 0;
        while (row < game->grid_rows)
        {
                col = 0;
                while (col < game->grid_cols)
                {
                        if (col < game->grid_cols / 2)
                                game->grid[row][col] = 1;  // Black
                        else
                                game->grid[row][col] = 0;  // White
                        col++;
                }
                row++;
        }

        // Create double buffer
        hdc = GetDC(hwnd);
        game->back_buffer = CreateCompatibleDC(hdc);
        game->back_bitmap = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(game->back_buffer, game->back_bitmap);
        ReleaseDC(hwnd, hdc);

        // Seed random
        srand((unsigned int)time(NULL));

        // Initialize one ball on each side
        game->left_ball_count = 1;
        game->right_ball_count = 1;
        game->left_balls = (t_ball *)malloc(sizeof(t_ball));
        game->right_balls = (t_ball *)malloc(sizeof(t_ball));

        // Initialize left ball (white) with random direction
        game->left_balls[0].x = width / 4;
        game->left_balls[0].y = height / 2;
        game->left_balls[0].speed = 13.0f;
        game->left_balls[0].dx = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        game->left_balls[0].dy = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        // Normalize and apply speed
        float left_mag = sqrtf(game->left_balls[0].dx * game->left_balls[0].dx + game->left_balls[0].dy * game->left_balls[0].dy);
        game->left_balls[0].dx = (game->left_balls[0].dx / left_mag) * game->left_balls[0].speed;
        game->left_balls[0].dy = (game->left_balls[0].dy / left_mag) * game->left_balls[0].speed;
        game->left_balls[0].is_white = 1;

        // Initialize right ball (black) with random direction
        game->right_balls[0].x = (width / 4) * 3;
        game->right_balls[0].y = height / 2;
        game->right_balls[0].speed = 13.0f;
        game->right_balls[0].dx = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        game->right_balls[0].dy = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        // Normalize and apply speed
        float right_mag = sqrtf(game->right_balls[0].dx * game->right_balls[0].dx + game->right_balls[0].dy * game->right_balls[0].dy);
        game->right_balls[0].dx = (game->right_balls[0].dx / right_mag) * game->right_balls[0].speed;
        game->right_balls[0].dy = (game->right_balls[0].dy / right_mag) * game->right_balls[0].speed;
        game->right_balls[0].is_white = 0;
}

void    add_new_balls(t_game *game)
{
        t_ball  *new_left;
        t_ball  *new_right;
        float   magnitude;

        // Reallocate left balls array
        game->left_ball_count++;
        new_left = (t_ball *)realloc(game->left_balls, game->left_ball_count * sizeof(t_ball));
        if (new_left)
                game->left_balls = new_left;
        else
                return;

        // Initialize new left ball
        game->left_balls[game->left_ball_count - 1].x = game->window_width / 4;
        game->left_balls[game->left_ball_count - 1].y = game->window_height / 2;
        game->left_balls[game->left_ball_count - 1].speed = 13.0f;
        game->left_balls[game->left_ball_count - 1].dx = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        game->left_balls[game->left_ball_count - 1].dy = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        magnitude = sqrtf(game->left_balls[game->left_ball_count - 1].dx * game->left_balls[game->left_ball_count - 1].dx +
                          game->left_balls[game->left_ball_count - 1].dy * game->left_balls[game->left_ball_count - 1].dy);
        game->left_balls[game->left_ball_count - 1].dx = (game->left_balls[game->left_ball_count - 1].dx / magnitude) *
                                                          game->left_balls[game->left_ball_count - 1].speed;
        game->left_balls[game->left_ball_count - 1].dy = (game->left_balls[game->left_ball_count - 1].dy / magnitude) *
                                                          game->left_balls[game->left_ball_count - 1].speed;
        game->left_balls[game->left_ball_count - 1].is_white = 1;

        // Reallocate right balls array
        game->right_ball_count++;
        new_right = (t_ball *)realloc(game->right_balls, game->right_ball_count * sizeof(t_ball));
        if (new_right)
                game->right_balls = new_right;
        else
                return;

        // Initialize new right ball
        game->right_balls[game->right_ball_count - 1].x = (game->window_width / 4) * 3;
        game->right_balls[game->right_ball_count - 1].y = game->window_height / 2;
        game->right_balls[game->right_ball_count - 1].speed = 13.0f;
        game->right_balls[game->right_ball_count - 1].dx = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        game->right_balls[game->right_ball_count - 1].dy = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
        magnitude = sqrtf(game->right_balls[game->right_ball_count - 1].dx * game->right_balls[game->right_ball_count - 1].dx +
                          game->right_balls[game->right_ball_count - 1].dy * game->right_balls[game->right_ball_count - 1].dy);
        game->right_balls[game->right_ball_count - 1].dx = (game->right_balls[game->right_ball_count - 1].dx / magnitude) *
                                                            game->right_balls[game->right_ball_count - 1].speed;
        game->right_balls[game->right_ball_count - 1].dy = (game->right_balls[game->right_ball_count - 1].dy / magnitude) *
                                                            game->right_balls[game->right_ball_count - 1].speed;
        game->right_balls[game->right_ball_count - 1].is_white = 0;
}

void    check_ball_collision(t_ball *ball, t_game *game)
{
        int     grid_col;
        int     grid_row;
        int     cell_is_black;
        float   magnitude;

        // Window boundary collisions
        if (ball->x - BALL_RADIUS < 0 || ball->x + BALL_RADIUS > game->window_width)
        {
                ball->dx = -ball->dx;
                // Clamp position within bounds
                if (ball->x - BALL_RADIUS < 0)
                        ball->x = BALL_RADIUS;
                if (ball->x + BALL_RADIUS > game->window_width)
                        ball->x = game->window_width - BALL_RADIUS;
        }
        if (ball->y - BALL_RADIUS < 0 || ball->y + BALL_RADIUS > game->window_height)
        {
                ball->dy = -ball->dy;
                // Clamp position within bounds
                if (ball->y - BALL_RADIUS < 0)
                        ball->y = BALL_RADIUS;
                if (ball->y + BALL_RADIUS > game->window_height)
                        ball->y = game->window_height - BALL_RADIUS;
        }

        // Grid collisions
        grid_col = (int)(ball->x / BLOCK_SIZE);
        grid_row = (int)(ball->y / BLOCK_SIZE);

        if (grid_col >= 0 && grid_col < game->grid_cols && grid_row >= 0 && grid_row < game->grid_rows)
        {
                cell_is_black = game->grid[grid_row][grid_col];

                // White ball (is_white=1) bounces on white cells (0)
                // Black ball (is_white=0) bounces on black cells (1)
                if (ball->is_white != cell_is_black)
                {
                        // Ball hits opposite color - bounce and flip cell
                        game->grid[grid_row][grid_col] = !cell_is_black;

                        // Determine bounce direction based on entry side
                        float cell_center_x = (grid_col + 0.5f) * BLOCK_SIZE;
                        float cell_center_y = (grid_row + 0.5f) * BLOCK_SIZE;

                        if (ball->x < cell_center_x)
                                ball->dx = -fabsf(ball->dx);
                        else
                                ball->dx = fabsf(ball->dx);

                        if (ball->y < cell_center_y)
                                ball->dy = -fabsf(ball->dy);
                        else
                                ball->dy = fabsf(ball->dy);
                }
        }
}


void    check_ball_to_ball_collision(t_ball *b1, t_ball *b2)
{
        float   dx;
        float   dy;
        float   distance;
        float   min_distance;
        float   nx;
        float   ny;
        float   relative_vx;
        float   relative_vy;
        float   dot_product;

        dx = b2->x - b1->x;
        dy = b2->y - b1->y;
        distance = sqrtf(dx * dx + dy * dy);
        min_distance = BALL_RADIUS * 2;

        if (distance < min_distance && distance > 0)
        {
                // Normalize collision vector
                nx = dx / distance;
                ny = dy / distance;

                // Relative velocity
                relative_vx = b1->dx - b2->dx;
                relative_vy = b1->dy - b2->dy;

                // Relative velocity in collision normal direction
                dot_product = relative_vx * nx + relative_vy * ny;

                // Only collide if balls are moving towards each other
                if (dot_product > 0)
                {
                        // Apply collision response (elastic collision)
                        b1->dx -= dot_product * nx;
                        b1->dy -= dot_product * ny;
                        b2->dx += dot_product * nx;
                        b2->dy += dot_product * ny;

                        // Separate balls to avoid overlap
                        float overlap = (min_distance - distance) / 2;
                        b1->x -= overlap * nx;
                        b1->y -= overlap * ny;
                        b2->x += overlap * nx;
                        b2->y += overlap * ny;
                }
        }
}

void    update_game(t_game *game)
{
        int     i;
        int     j;

        // Update all left balls
        i = 0;
        while (i < game->left_ball_count)
        {
                game->left_balls[i].x += game->left_balls[i].dx;
                game->left_balls[i].y += game->left_balls[i].dy;
                check_ball_collision(&game->left_balls[i], game);
                i++;
        }

        // Update all right balls
        i = 0;
        while (i < game->right_ball_count)
        {
                game->right_balls[i].x += game->right_balls[i].dx;
                game->right_balls[i].y += game->right_balls[i].dy;
                check_ball_collision(&game->right_balls[i], game);
                i++;
        }

        // Check collisions between all balls
        // Left balls with other left balls
        i = 0;
        while (i < game->left_ball_count)
        {
                j = i + 1;
                while (j < game->left_ball_count)
                {
                        check_ball_to_ball_collision(&game->left_balls[i], &game->left_balls[j]);
                        j++;
                }
                i++;
        }

        // Right balls with other right balls
        i = 0;
        while (i < game->right_ball_count)
        {
                j = i + 1;
                while (j < game->right_ball_count)
                {
                        check_ball_to_ball_collision(&game->right_balls[i], &game->right_balls[j]);
                        j++;
                }
                i++;
        }

        // Left balls with right balls
        i = 0;
        while (i < game->left_ball_count)
        {
                j = 0;
                while (j < game->right_ball_count)
                {
                        check_ball_to_ball_collision(&game->left_balls[i], &game->right_balls[j]);
                        j++;
                }
                i++;
        }
}

void    render_game(HDC hdc, t_game *game)
{
        t_ball  *ball;
        RECT    rect;
        int     row;
        int     col;
        HBRUSH  brush;
        HBRUSH  old_brush;

        row = 0;
        col = 0;

        // Clear back buffer
        RECT clear_rect = {0, 0, game->window_width, game->window_height};
        HBRUSH clear_brush = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(game->back_buffer, &clear_rect, clear_brush);
        DeleteObject(clear_brush);

        // Draw grid to back buffer
        while (row < game->grid_rows)
        {
                col = 0;
                while (col < game->grid_cols)
                {
                        rect.left = col * BLOCK_SIZE;
                        rect.top = row * BLOCK_SIZE;
                        rect.right = rect.left + BLOCK_SIZE;
                        rect.bottom = rect.top + BLOCK_SIZE;

                        if (game->grid[row][col] == 1)
                                brush = CreateSolidBrush(RGB(0, 0, 0));  // Black
                        else
                                brush = CreateSolidBrush(RGB(255, 255, 255));  // White

                        FillRect(game->back_buffer, &rect, brush);
                        DeleteObject(brush);
                        col++;
                }
                row++;
        }

        // Draw all left balls (white) - as squares
        int i = 0;
        while (i < game->left_ball_count)
        {
                ball = &game->left_balls[i];
                rect.left = (int)(ball->x - BALL_RADIUS);
                rect.top = (int)(ball->y - BALL_RADIUS);
                rect.right = (int)(ball->x + BALL_RADIUS);
                rect.bottom = (int)(ball->y + BALL_RADIUS);
                brush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(game->back_buffer, &rect, brush);
                DeleteObject(brush);
                i++;
        }

        // Draw all right balls (black) - as squares
        i = 0;
        while (i < game->right_ball_count)
        {
                ball = &game->right_balls[i];
                rect.left = (int)(ball->x - BALL_RADIUS);
                rect.top = (int)(ball->y - BALL_RADIUS);
                rect.right = (int)(ball->x + BALL_RADIUS);
                rect.bottom = (int)(ball->y + BALL_RADIUS);
                brush = CreateSolidBrush(RGB(0, 0, 0));
                FillRect(game->back_buffer, &rect, brush);
                DeleteObject(brush);
                i++;
        }

        // Copy back buffer to screen
        BitBlt(hdc, 0, 0, game->window_width, game->window_height, game->back_buffer, 0, 0, SRCCOPY);
}

int WINAPI      WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow)
{
        WNDCLASSEX wc = {0};
        MSG msg;
        HWND hwnd;

        wc.cbSize               = sizeof (wc);
        wc.style                = 0;
        wc.lpfnWndProc          = winproc;
        wc.cbClsExtra           = 0;
        wc.cbWndExtra           = 0;
        wc.hInstance            = hInst;
        wc.hIcon                = LoadIcon (NULL, IDI_APPLICATION);
        wc.hCursor              = LoadCursor (NULL, IDC_ARROW);
        wc.hbrBackground        = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wc.lpszMenuName         = NULL;
        wc.lpszClassName        = CLSNAME;
        wc.hIconSm              = LoadIcon (NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc))
        {
                MessageBox(NULL, TEXT("Could not register window class"), 
                NULL, MB_ICONERROR);
                return 0;
        }

        RECT window_rect;
        window_rect.left = 0;
        window_rect.top = 0;
        window_rect.right = WINDOW_WIDTH;
        window_rect.bottom = WINDOW_HEIGHT;
        AdjustWindowRect(&window_rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

        hwnd = CreateWindowEx(WS_EX_LEFT,
                        CLSNAME,
                        TEXT("bounC"),
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        window_rect.right - window_rect.left,
                        window_rect.bottom - window_rect.top,
                        NULL,
                        NULL,
                        hInst,
                        NULL);
        if (!hwnd)
        {
                MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
                return 0;
        }
        ShowWindow(hwnd, cmdshow);
        UpdateWindow(hwnd);
        while (GetMessage(&msg, NULL, 0, 0))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }
        return msg.wParam;
}

LRESULT CALLBACK        winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
        switch(wm)
        {
                case WM_CREATE:
                        {
                                RECT    rect;
                                GetClientRect(hwnd, &rect);
                                init_game(&g_game, rect.right - rect.left, rect.bottom - rect.top, hwnd);
                                SetTimer(hwnd, 1, 16, NULL);
                                return 0;
                        }
                case WM_KEYDOWN:
                        {
                                if (wp == 'R' || wp == 'r')
                                {
                                        RECT    rect;
                                        int     row;

                                        // Free existing grid and balls
                                        row = 0;
                                        while (row < g_game.grid_rows)
                                        {
                                                free(g_game.grid[row]);
                                                row++;
                                        }
                                        free(g_game.grid);
                                        free(g_game.left_balls);
                                        free(g_game.right_balls);

                                        // Reinitialize game
                                        GetClientRect(hwnd, &rect);
                                        init_game(&g_game, rect.right - rect.left, rect.bottom - rect.top, hwnd);
                                        InvalidateRect(hwnd, NULL, FALSE);
                                }
                                else if (wp == 'N' || wp == 'n')
                                {
                                        // Add two new balls, one on each side
                                        add_new_balls(&g_game);
                                        InvalidateRect(hwnd, NULL, FALSE);
                                }
                                return 0;
                        }
                case WM_TIMER:
                        {
                                update_game(&g_game);
                                InvalidateRect(hwnd, NULL, FALSE);
                                return 0;
                        }
                case WM_PAINT:
                        {
                                PAINTSTRUCT ps;
                                HDC         hdc;

                                hdc = BeginPaint(hwnd, &ps);
                                render_game(hdc, &g_game);
                                EndPaint(hwnd, &ps);
                                return 0;
                        }
                case WM_DESTROY:
                        {
                                int row;
                                KillTimer(hwnd, 1);

                                // Free grid memory
                                row = 0;
                                while (row < g_game.grid_rows)
                                {
                                        free(g_game.grid[row]);
                                        row++;
                                }
                                free(g_game.grid);

                                // Free ball arrays
                                free(g_game.left_balls);
                                free(g_game.right_balls);

                                // Free back buffer
                                DeleteObject(g_game.back_bitmap);
                                DeleteDC(g_game.back_buffer);

                                PostQuitMessage(0);
                                return 0;
                        }
        }
        return DefWindowProc(hwnd, wm, wp, lp);
}