/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winproc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

int	handle_destroy(HWND hwnd)
{
	KillTimer(hwnd, 1);
	free_game(&g_game);
	DeleteObject(g_game.back_bitmap);
	DeleteDC(g_game.back_buffer);
	PostQuitMessage(0);
	return (0);
}

LRESULT CALLBACK	winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	if (wm == WM_CREATE)
		return (handle_create(hwnd));
	else if (wm == WM_KEYDOWN)
		return (handle_keydown(hwnd, wp));
	else if (wm == WM_TIMER)
		return (handle_timer(hwnd));
	else if (wm == WM_PAINT)
		return (handle_paint(hwnd));
	else if (wm == WM_DESTROY)
		return (handle_destroy(hwnd));
	return (DefWindowProc(hwnd, wm, wp, lp));
}
