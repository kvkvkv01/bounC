/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winproc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

int	handle_create(HWND hwnd)
{
	RECT	rect;

	GetClientRect(hwnd, &rect);
	init_game(&g_game, rect.right - rect.left, rect.bottom - rect.top, hwnd);
	SetTimer(hwnd, 1, 16, NULL);
	return (0);
}

static void	reset_game(HWND hwnd)
{
	RECT	rect;

	free_game(&g_game);
	GetClientRect(hwnd, &rect);
	init_game(&g_game, rect.right - rect.left, rect.bottom - rect.top, hwnd);
	InvalidateRect(hwnd, NULL, FALSE);
}

int	handle_keydown(HWND hwnd, WPARAM wp)
{
	if (wp == 'R' || wp == 'r')
		reset_game(hwnd);
	else if (wp == 'N' || wp == 'n')
	{
		add_new_balls(&g_game);
		InvalidateRect(hwnd, NULL, FALSE);
	}
	return (0);
}

int	handle_timer(HWND hwnd)
{
	update_game(&g_game);
	InvalidateRect(hwnd, NULL, FALSE);
	return (0);
}

int	handle_paint(HWND hwnd)
{
	PAINTSTRUCT	ps;
	HDC			hdc;

	hdc = BeginPaint(hwnd, &ps);
	render_game(hdc, &g_game);
	EndPaint(hwnd, &ps);
	return (0);
}
