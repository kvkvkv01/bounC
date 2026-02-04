/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	check_window_collision(t_ball *ball, t_game *game)
{
	if (ball->x - BALL_RADIUS < 0 || ball->x + BALL_RADIUS > game->window_width)
	{
		ball->dx = -ball->dx;
		if (ball->x - BALL_RADIUS < 0)
			ball->x = BALL_RADIUS;
		if (ball->x + BALL_RADIUS > game->window_width)
			ball->x = game->window_width - BALL_RADIUS;
	}
	if (ball->y - BALL_RADIUS < 0
		|| ball->y + BALL_RADIUS > game->window_height)
	{
		ball->dy = -ball->dy;
		if (ball->y - BALL_RADIUS < 0)
			ball->y = BALL_RADIUS;
		if (ball->y + BALL_RADIUS > game->window_height)
			ball->y = game->window_height - BALL_RADIUS;
	}
}

static void	bounce_on_cell(t_ball *ball, int col, int row)
{
	float	cell_left;
	float	cell_right;
	float	cell_top;
	float	cell_bottom;
	float	overlap_x;
	float	overlap_y;

	cell_left = col * BLOCK_SIZE;
	cell_right = cell_left + BLOCK_SIZE;
	cell_top = row * BLOCK_SIZE;
	cell_bottom = cell_top + BLOCK_SIZE;
	overlap_x = fminf(ball->x + BALL_RADIUS - cell_left,
			cell_right - (ball->x - BALL_RADIUS));
	overlap_y = fminf(ball->y + BALL_RADIUS - cell_top,
			cell_bottom - (ball->y - BALL_RADIUS));
	if (overlap_x < overlap_y)
	{
		ball->dx = -ball->dx;
		if (ball->x < cell_left + BLOCK_SIZE / 2.0f)
			ball->x = cell_left - BALL_RADIUS;
		else
			ball->x = cell_right + BALL_RADIUS;
	}
	else
	{
		ball->dy = -ball->dy;
		if (ball->y < cell_top + BLOCK_SIZE / 2.0f)
			ball->y = cell_top - BALL_RADIUS;
		else
			ball->y = cell_bottom + BALL_RADIUS;
	}
}

static int	circle_rect_intersect(t_ball *ball, int col, int row)
{
	float	cell_left;
	float	cell_right;
	float	cell_top;
	float	cell_bottom;
	float	closest_x;
	float	closest_y;
	float	dist_sq;

	cell_left = col * BLOCK_SIZE;
	cell_right = cell_left + BLOCK_SIZE;
	cell_top = row * BLOCK_SIZE;
	cell_bottom = cell_top + BLOCK_SIZE;
	closest_x = fmaxf(cell_left, fminf(ball->x, cell_right));
	closest_y = fmaxf(cell_top, fminf(ball->y, cell_bottom));
	dist_sq = (ball->x - closest_x) * (ball->x - closest_x)
		+ (ball->y - closest_y) * (ball->y - closest_y);
	return (dist_sq < BALL_RADIUS * BALL_RADIUS);
}

void	check_grid_collision(t_ball *ball, t_game *game)
{
	int	col_min;
	int	col_max;
	int	row_min;
	int	row_max;
	int	col;
	int	row;

	col_min = (int)((ball->x - BALL_RADIUS) / BLOCK_SIZE);
	col_max = (int)((ball->x + BALL_RADIUS) / BLOCK_SIZE);
	row_min = (int)((ball->y - BALL_RADIUS) / BLOCK_SIZE);
	row_max = (int)((ball->y + BALL_RADIUS) / BLOCK_SIZE);
	row = row_min;
	while (row <= row_max)
	{
		col = col_min;
		while (col <= col_max)
		{
			if (col >= 0 && col < game->grid_cols
				&& row >= 0 && row < game->grid_rows
				&& ball->is_white != game->grid[row][col]
				&& circle_rect_intersect(ball, col, row))
			{
				game->grid[row][col] = !game->grid[row][col];
				bounce_on_cell(ball, col, row);
				return ;
			}
			col++;
		}
		row++;
	}
}

void	check_ball_collision(t_ball *ball, t_game *game)
{
	check_window_collision(ball, game);
	check_grid_collision(ball, game);
}
