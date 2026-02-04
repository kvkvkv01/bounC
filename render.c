/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	clear_back_buffer(t_game *game)
{
	RECT	rect;
	HBRUSH	brush;

	rect.left = 0;
	rect.top = 0;
	rect.right = game->window_width;
	rect.bottom = game->window_height;
	brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(game->back_buffer, &rect, brush);
	DeleteObject(brush);
}

void	draw_grid(t_game *game)
{
	int		row;
	int		col;
	RECT	rect;
	HBRUSH	brush;

	row = 0;
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
				brush = CreateSolidBrush(RGB(0, 0, 0));
			else
				brush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(game->back_buffer, &rect, brush);
			DeleteObject(brush);
			col++;
		}
		row++;
	}
}

void	draw_left_balls(t_game *game)
{
	int		i;
	t_ball	*ball;
	RECT	rect;
	HBRUSH	brush;

	i = 0;
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
}

void	draw_right_balls(t_game *game)
{
	int		i;
	t_ball	*ball;
	RECT	rect;
	HBRUSH	brush;

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
}

void	render_game(HDC hdc, t_game *game)
{
	clear_back_buffer(game);
	draw_grid(game);
	draw_left_balls(game);
	draw_right_balls(game);
	BitBlt(hdc, 0, 0, game->window_width, game->window_height,
		game->back_buffer, 0, 0, SRCCOPY);
}
