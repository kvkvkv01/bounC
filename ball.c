/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	init_left_ball(t_game *game, int idx)
{
	float	x;
	float	y;

	x = game->window_width / 4;
	y = game->window_height / 2;
	init_ball(&game->left_balls[idx], x, y, 1);
}

void	init_right_ball(t_game *game, int idx)
{
	float	x;
	float	y;

	x = (game->window_width / 4) * 3;
	y = game->window_height / 2;
	init_ball(&game->right_balls[idx], x, y, 0);
}

static int	add_left_ball(t_game *game)
{
	t_ball	*new_left;

	game->left_ball_count++;
	new_left = (t_ball *)realloc(game->left_balls,
			game->left_ball_count * sizeof(t_ball));
	if (!new_left)
		return (0);
	game->left_balls = new_left;
	init_left_ball(game, game->left_ball_count - 1);
	return (1);
}

static int	add_right_ball(t_game *game)
{
	t_ball	*new_right;

	game->right_ball_count++;
	new_right = (t_ball *)realloc(game->right_balls,
			game->right_ball_count * sizeof(t_ball));
	if (!new_right)
		return (0);
	game->right_balls = new_right;
	init_right_ball(game, game->right_ball_count - 1);
	return (1);
}

void	add_new_balls(t_game *game)
{
	if (!add_left_ball(game))
		return ;
	add_right_ball(game);
}
