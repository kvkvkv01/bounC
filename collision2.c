/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

static void	apply_collision(t_ball *b1, t_ball *b2, float nx, float ny)
{
	float	rel_vx;
	float	rel_vy;
	float	dot;

	rel_vx = b1->dx - b2->dx;
	rel_vy = b1->dy - b2->dy;
	dot = rel_vx * nx + rel_vy * ny;
	if (dot > 0)
	{
		b1->dx -= dot * nx;
		b1->dy -= dot * ny;
		b2->dx += dot * nx;
		b2->dy += dot * ny;
	}
}

static void	separate_balls(t_ball *b1, t_ball *b2, float *data)
{
	float	overlap;

	overlap = (BALL_RADIUS * 2 - data[0]) / 2;
	b1->x -= overlap * data[1];
	b1->y -= overlap * data[2];
	b2->x += overlap * data[1];
	b2->y += overlap * data[2];
}

void	check_ball_to_ball_collision(t_ball *b1, t_ball *b2)
{
	float	dx;
	float	dy;
	float	data[3];

	dx = b2->x - b1->x;
	dy = b2->y - b1->y;
	data[0] = sqrtf(dx * dx + dy * dy);
	if (data[0] < BALL_RADIUS * 2 && data[0] > 0)
	{
		data[1] = dx / data[0];
		data[2] = dy / data[0];
		apply_collision(b1, b2, data[1], data[2]);
		separate_balls(b1, b2, data);
	}
}
