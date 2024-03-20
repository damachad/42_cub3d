/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:10:59 by damachad          #+#    #+#             */
/*   Updated: 2024/03/20 13:27:17 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Makes player move parallel to wall when trying to move (fowards) past it */
void	wall_sliding(t_game *g)
{
	if (g->wall_side == 0)
	{
		if (facing_right(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x + SPEED + WALL_BUFF) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x += SPEED;
		else if (facing_left(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x - SPEED - WALL_BUFF) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x -= SPEED;
	}
	else if (g->wall_side == 1)
	{
		if (g->p_angle < PI - SLIDE_BUFF && !is_wall(g, g->p_pos.x / CUB_SIDE, \
		(g->p_pos.y - SPEED - WALL_BUFF) / CUB_SIDE))
			g->p_pos.y -= SPEED;
		else if (g->p_angle > PI + SLIDE_BUFF && !is_wall(g, g->p_pos.x / \
		CUB_SIDE, (g->p_pos.y + SPEED + WALL_BUFF) / CUB_SIDE))
			g->p_pos.y += SPEED;
	}
}

/* Makes player move parallel to wall when trying to move (backwards) past it */
void	wall_sliding_back(t_game *g)
{
	if (g->back_wall == 0)
	{
		if (facing_right(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x - SPEED - WALL_BUFF) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x -= SPEED;
		else if (facing_left(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x + SPEED + WALL_BUFF) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x += SPEED;
	}
	else if (g->back_wall == 1)
	{
		if (g->p_angle < PI - SLIDE_BUFF && !is_wall(g, g->p_pos.x / CUB_SIDE, \
		(g->p_pos.y + SPEED + WALL_BUFF) / CUB_SIDE))
			g->p_pos.y += SPEED;
		else if (g->p_angle > PI + SLIDE_BUFF && !is_wall(g, g->p_pos.x / \
		CUB_SIDE, (g->p_pos.y - SPEED - WALL_BUFF) / CUB_SIDE))
			g->p_pos.y -= SPEED;
	}
}

void	rotate(t_game *g)
{
	if (g->keys.l_a)
	{
		g->p_angle += ROT_SPEED;
		if (g->p_angle >= PI_DOUBLE)
			g->p_angle -= PI_DOUBLE;
		g->p_dir = (t_point){cos(g->p_angle) * SPEED, sin(g->p_angle) * -SPEED};
	}
	else if (g->keys.r_a)
	{
		g->p_angle -= ROT_SPEED;
		if (g->p_angle < 0)
			g->p_angle += PI_DOUBLE;
		g->p_dir = (t_point){cos(g->p_angle) * SPEED, sin(g->p_angle) * -SPEED};
	}
}

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
	x = (g->p_pos.x + dir_x * 10) / CUB_SIDE;
	y = (g->p_pos.y + dir_y * 10) / CUB_SIDE;
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


void	sideways_movement(t_game *g)
{
	t_point	perp_dir;
	float	perp_angle;
	
	if (g->keys.a)
	{
		perp_angle = g->p_angle + PI_HALF;
		if (perp_angle >= PI_DOUBLE)
			perp_angle -= PI_DOUBLE;
		perp_dir.x = cos(perp_angle) * SPEED;
		perp_dir.y = sin(perp_angle) * -1 * SPEED;
	}
	else if (g->keys.d)
	{
		perp_angle = g->p_angle - PI_HALF;
		if (perp_angle < 0)
			perp_angle += PI_DOUBLE;
		perp_dir.x = cos(perp_angle) * SPEED;
		perp_dir.y = sin(perp_angle) * -1 * SPEED;
	}
	if (!is_wall(g, (g->p_pos.x + perp_dir.x * WALL_BUFF) / CUB_SIDE, \
	(g->p_pos.y + perp_dir.y * WALL_BUFF) / CUB_SIDE))
	{
		g->p_pos.x += perp_dir.x;
		g->p_pos.y += perp_dir.y;
	}
}

void	front_back_move(t_game *g)
{
	if (g->keys.w)
	{
		if (!is_wall(g, (g->p_pos.x + g->p_dir.x * WALL_BUFF) / CUB_SIDE, \
		(g->p_pos.y + g->p_dir.y * WALL_BUFF) / CUB_SIDE) && \
		!is_empty_corner(g, g->p_dir.x, g->p_dir.y, g->p_angle))
		{
			g->p_pos.x += g->p_dir.x;
			g->p_pos.y += g->p_dir.y;
		}
		else
			wall_sliding(g);
	}
	else if (g->keys.s)
	{
		if (!is_wall(g, (g->p_pos.x - g->p_dir.x * WALL_BUFF) / CUB_SIDE, \
		(g->p_pos.y - g->p_dir.y * WALL_BUFF) / CUB_SIDE) && \
		!is_empty_corner(g, -g->p_dir.x, -g->p_dir.y, g->p_b_angle))
		{
			g->p_pos.x -= g->p_dir.x;
			g->p_pos.y -= g->p_dir.y;
		}
		else
			wall_sliding_back(g);
	}
}

int	render_movement(t_game *g)
{
	if (g->keys.w || g->keys.s)
		front_back_move(g);
	if (g->keys.a || g->keys.d)
		sideways_movement(g);
	if (g->keys.l_a || g->keys.r_a)
		rotate(g);
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
