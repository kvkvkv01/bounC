/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	update_left_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->left_ball_count)
	{
		game->left_balls[i].x += game->left_balls[i].dx;
		game->left_balls[i].y += game->left_balls[i].dy;
		check_ball_collision(&game->left_balls[i], game);
		i++;
	}
}

void	update_right_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->right_ball_count)
	{
		game->right_balls[i].x += game->right_balls[i].dx;
		game->right_balls[i].y += game->right_balls[i].dy;
		check_ball_collision(&game->right_balls[i], game);
		i++;
	}
}

void	check_left_collisions(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->left_ball_count)
	{
		j = i + 1;
		while (j < game->left_ball_count)
		{
			check_ball_to_ball_collision(&game->left_balls[i],
				&game->left_balls[j]);
			j++;
		}
		i++;
	}
}

void	check_right_collisions(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->right_ball_count)
	{
		j = i + 1;
		while (j < game->right_ball_count)
		{
			check_ball_to_ball_collision(&game->right_balls[i],
				&game->right_balls[j]);
			j++;
		}
		i++;
	}
}

void	check_cross_collisions(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->left_ball_count)
	{
		j = 0;
		while (j < game->right_ball_count)
		{
			check_ball_to_ball_collision(&game->left_balls[i],
				&game->right_balls[j]);
			j++;
		}
		i++;
	}
}
