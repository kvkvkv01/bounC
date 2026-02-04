/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

t_game			g_game;
const TCHAR		g_clsname[] = TEXT("bouncWClass");

static int	start_app(HINSTANCE hinst)
{
	WNDCLASSEX	wc;
	RECT		wr;
	HWND		hwnd;

	ZeroMemory(&wc, sizeof(wc));
	init_wndclass(&wc, hinst);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Could not register window class"),
			NULL, MB_ICONERROR);
		return (0);
	}
	get_window_rect(&wr);
	hwnd = create_window(hinst, &wr);
	if (!hwnd)
	{
		MessageBox(NULL, TEXT("Could not create window"),
			NULL, MB_ICONERROR);
		return (0);
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return (run_message_loop());
}

int	main(void)
{
	HINSTANCE	hinst;

	hinst = GetModuleHandle(NULL);
	return (start_app(hinst));
}
