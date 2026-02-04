/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	update_game(t_game *game)
{
	update_left_balls(game);
	update_right_balls(game);
	check_left_collisions(game);
	check_right_collisions(game);
	check_cross_collisions(game);
}

void	free_game(t_game *game)
{
	int	row;

	row = 0;
	while (row < game->grid_rows)
	{
		free(game->grid[row]);
		row++;
	}
	free(game->grid);
	free(game->left_balls);
	free(game->right_balls);
}
