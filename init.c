/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	init_grid(t_game *game)
{
	int	row;
	int	col;

	game->grid = (int **)malloc(game->grid_rows * sizeof(int *));
	row = 0;
	while (row < game->grid_rows)
	{
		game->grid[row] = (int *)malloc(game->grid_cols * sizeof(int));
		col = 0;
		while (col < game->grid_cols)
		{
			if (col < game->grid_cols / 2)
				game->grid[row][col] = 1;
			else
				game->grid[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	normalize_ball(t_ball *ball)
{
	float	mag;

	mag = sqrtf(ball->dx * ball->dx + ball->dy * ball->dy);
	ball->dx = (ball->dx / mag) * ball->speed;
	ball->dy = (ball->dy / mag) * ball->speed;
}

void	init_ball(t_ball *ball, float x, float y, int is_white)
{
	ball->x = x;
	ball->y = y;
	ball->speed = 13.0f;
	ball->dx = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
	ball->dy = ((rand() % 2) * 2 - 1) * (rand() % 100 / 100.0f + 0.5f);
	ball->is_white = is_white;
	normalize_ball(ball);
}

static void	init_back_buffer(t_game *game, HWND hwnd)
{
	HDC	hdc;

	hdc = GetDC(hwnd);
	game->back_buffer = CreateCompatibleDC(hdc);
	game->back_bitmap = CreateCompatibleBitmap(hdc,
			game->window_width, game->window_height);
	SelectObject(game->back_buffer, game->back_bitmap);
	ReleaseDC(hwnd, hdc);
}

void	init_game(t_game *game, int width, int height, HWND hwnd)
{
	ZeroMemory(game, sizeof(t_game));
	game->window_width = width;
	game->window_height = height;
	game->grid_cols = width / BLOCK_SIZE;
	game->grid_rows = height / BLOCK_SIZE;
	init_grid(game);
	init_back_buffer(game, hwnd);
	srand((unsigned int)time(NULL));
	game->left_ball_count = 1;
	game->right_ball_count = 1;
	game->left_balls = (t_ball *)malloc(sizeof(t_ball));
	game->right_balls = (t_ball *)malloc(sizeof(t_ball));
	init_ball(&game->left_balls[0], width / 4, height / 2, 1);
	init_ball(&game->right_balls[0], (width / 4) * 3, height / 2, 0);
}
