/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:10:59 by damachad          #+#    #+#             */
/*   Updated: 2024/03/23 17:57:34 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Makes player move parallel to wall when trying to move past it */
void	wall_sliding(t_game *g, int side, int s)
{
	if (side == 0)
	{
		if (facing_right(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x + SPEED * s + WALL_BUFF * s) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x += SPEED * s;
		else if (facing_left(g->p_angle, SLIDE_BUFF) && \
		!is_wall(g, (g->p_pos.x - SPEED * s - WALL_BUFF * s) / CUB_SIDE, \
		g->p_pos.y / CUB_SIDE))
			g->p_pos.x -= SPEED * s;
	}
	else if (side == 1)
	{
		if (g->p_angle < PI - SLIDE_BUFF && !is_wall(g, g->p_pos.x / CUB_SIDE, \
		(g->p_pos.y - SPEED * s - WALL_BUFF * s) / CUB_SIDE))
			g->p_pos.y -= SPEED * s;
		else if (g->p_angle > PI + SLIDE_BUFF && !is_wall(g, g->p_pos.x / \
		CUB_SIDE, (g->p_pos.y + SPEED * s + WALL_BUFF * s) / CUB_SIDE))
			g->p_pos.y += SPEED * s;
	}
}

void	rotate(t_game *g)
{
	if (g->keys.l_a && g->keys.r_a)
		return ;
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

void	sideways_movement(t_game *g)
{
	t_point	perp_dir;
	float	perp_angle;

	if (g->keys.a && g->keys.d)
		return ;
	if (g->keys.a)
	{
		perp_angle = set_angle(g->p_angle + PI_HALF);
		perp_dir.x = cos(perp_angle) * SPEED;
		perp_dir.y = sin(perp_angle) * -1 * SPEED;
	}
	else if (g->keys.d)
	{
		perp_angle = set_angle(g->p_angle - PI_HALF);
		perp_dir.x = cos(perp_angle) * SPEED;
		perp_dir.y = sin(perp_angle) * -1 * SPEED;
	}
	if (!is_wall(g, (g->p_pos.x + perp_dir.x * WALL_BUFF) / CUB_SIDE, \
	(g->p_pos.y + perp_dir.y * WALL_BUFF) / CUB_SIDE) && \
	!is_empty_corner(g, perp_dir.x, perp_dir.y, perp_angle))
	{
		g->p_pos.x += perp_dir.x;
		g->p_pos.y += perp_dir.y;
	}
}

void	move_backwards(t_game *g)
{
	if (!is_wall(g, (g->p_pos.x - g->p_dir.x * WALL_BUFF) / CUB_SIDE, \
	(g->p_pos.y - g->p_dir.y * WALL_BUFF) / CUB_SIDE) && \
	!is_empty_corner(g, -g->p_dir.x, -g->p_dir.y, g->p_b_angle))
	{
		g->p_pos.x -= g->p_dir.x;
		g->p_pos.y -= g->p_dir.y;
	}
	else
		wall_sliding(g, g->back_wall, -1);
}

void	front_back_move(t_game *g)
{
	if (g->keys.w && g->keys.s)
		return ;
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
			wall_sliding(g, g->wall_side, 1);
	}
	else if (g->keys.s)
		move_backwards(g);
}
