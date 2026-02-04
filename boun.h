/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boun.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by user             #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUN_H
# define BOUN_H

# define UNICODE
# define _UNICODE
# define BLOCK_SIZE		15
# define BALL_RADIUS	7
# define WINDOW_WIDTH	1200
# define WINDOW_HEIGHT	900

# include <windows.h>
# include <tchar.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

typedef struct s_ball
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		is_white;
	float	speed;
}	t_ball;

typedef struct s_game
{
	int		**grid;
	t_ball	*left_balls;
	t_ball	*right_balls;
	int		left_ball_count;
	int		right_ball_count;
	int		window_width;
	int		window_height;
	int		grid_rows;
	int		grid_cols;
	HDC		back_buffer;
	HBITMAP	back_bitmap;
}	t_game;

extern t_game			g_game;
extern const TCHAR		g_clsname[];

void		init_game(t_game *game, int width, int height, HWND hwnd);
void		add_new_balls(t_game *game);
void		check_ball_collision(t_ball *ball, t_game *game);
void		check_ball_to_ball_collision(t_ball *b1, t_ball *b2);
void		update_game(t_game *game);
void		render_game(HDC hdc, t_game *game);
void		free_game(t_game *game);
void		init_grid(t_game *game);
void		init_ball(t_ball *ball, float x, float y, int is_white);
void		normalize_ball(t_ball *ball);
void		init_left_ball(t_game *game, int idx);
void		init_right_ball(t_game *game, int idx);
void		check_window_collision(t_ball *ball, t_game *game);
void		check_grid_collision(t_ball *ball, t_game *game);
void		update_left_balls(t_game *game);
void		update_right_balls(t_game *game);
void		check_left_collisions(t_game *game);
void		check_right_collisions(t_game *game);
void		check_cross_collisions(t_game *game);
void		draw_grid(t_game *game);
void		draw_left_balls(t_game *game);
void		draw_right_balls(t_game *game);
void		clear_back_buffer(t_game *game);
int			handle_create(HWND hwnd);
int			handle_keydown(HWND hwnd, WPARAM wp);
int			handle_timer(HWND hwnd);
int			handle_paint(HWND hwnd);
int			handle_destroy(HWND hwnd);
LRESULT		winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);
void		init_wndclass(WNDCLASSEX *wc, HINSTANCE hinst);
void		get_window_rect(RECT *wr);
HWND		create_window(HINSTANCE hinst, RECT *wr);
int			run_message_loop(void);

#endif
