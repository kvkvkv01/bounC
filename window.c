/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boun.h"

void	init_wndclass(WNDCLASSEX *wc, HINSTANCE hinst)
{
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->style = 0;
	wc->lpfnWndProc = winproc;
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->hInstance = hinst;
	wc->hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc->hCursor = LoadCursor(NULL, IDC_ARROW);
	wc->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc->lpszMenuName = NULL;
	wc->lpszClassName = g_clsname;
	wc->hIconSm = LoadIcon(NULL, IDI_APPLICATION);
}

void	get_window_rect(RECT *wr)
{
	wr->left = 0;
	wr->top = 0;
	wr->right = WINDOW_WIDTH;
	wr->bottom = WINDOW_HEIGHT;
	AdjustWindowRect(wr, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| WS_MINIMIZEBOX, FALSE);
}

HWND	create_window(HINSTANCE hinst, RECT *wr)
{
	HWND	hwnd;
	DWORD	style;

	style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	hwnd = CreateWindowEx(WS_EX_LEFT, g_clsname, TEXT("bounC"), style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			wr->right - wr->left, wr->bottom - wr->top,
			NULL, NULL, hinst, NULL);
	return (hwnd);
}

int	run_message_loop(void)
{
	MSG	msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}
