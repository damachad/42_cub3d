/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:56:46 by damachad          #+#    #+#             */
/*   Updated: 2024/03/28 10:08:55 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_empty_corner(t_game *g, float dir_x, float dir_y, float angle)
{
	bool	empty;
	int		x_sign;
	int		y_sign;
	int		x;
	int		y;

	empty = false;
	x_sign = 1;
	y_sign = 1;
	x = (g->p_pos.x + dir_x * WALL_BUFF) / CUB_SIDE;
	y = (g->p_pos.y + dir_y * WALL_BUFF) / CUB_SIDE;
	if (x == (int)g->p_pos.x / CUB_SIDE && y == (int)g->p_pos.y / CUB_SIDE)
		return (empty);
	if (facing_right(angle, 0))
		x_sign *= -1;
	if (facing_down(angle))
		y_sign *= -1;
	if (!is_wall(g, x, y) && is_wall(g, x + x_sign, y) \
	&& is_wall(g, x, y + y_sign))
		empty = true;
	return (empty);
}

int	render_movement(t_game *g)
{
	if (g->keys.w || g->keys.s)
		front_back_move(g);
	if (g->keys.a || g->keys.d)
		sideways_movement(g);
	if (g->keys.l_a || g->keys.r_a)
		rotate(g);
	if (g->keys.w || g->keys.s || g->keys.a || g->keys.d || g->keys.l_a \
	|| g->keys.r_a)
		draw_wall(g);
	return (0);
}

int	handle_keypress(int keysym, t_game *g)
{
	if (keysym == XK_Escape)
		quit_prog(g);
	else if (keysym == XK_w)
		g->keys.w = 1;
	else if (keysym == XK_a)
		g->keys.a = 1;
	else if (keysym == XK_s)
		g->keys.s = 1;
	else if (keysym == XK_d)
		g->keys.d = 1;
	else if (keysym == XK_Left)
		g->keys.l_a = 1;
	else if (keysym == XK_Right)
		g->keys.r_a = 1;
	return (keysym);
}

int	handle_keyrelease(int keysym, t_game *g)
{
	if (keysym == XK_w)
		g->keys.w = 0;
	else if (keysym == XK_a)
		g->keys.a = 0;
	else if (keysym == XK_s)
		g->keys.s = 0;
	else if (keysym == XK_d)
		g->keys.d = 0;
	else if (keysym == XK_Left)
		g->keys.l_a = 0;
	else if (keysym == XK_Right)
		g->keys.r_a = 0;
	return (keysym);
}
