/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:51:10 by damachad          #+#    #+#             */
/*   Updated: 2024/03/23 18:47:59 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	is_wall(t_game *g, int x, int y)
{
	if (x < g->map_cols && y < g->map_rows && g->map[y][x] \
	&& g->map[y][x] == '1')
		return (true);
	else
		return (false);
}

/*
** Calculates the distance between horizontal intersections in the grid,
** applies a correction in sign depending on the angle
*/
float	get_xa(float alpha)
{
	float	xa;

	xa = 0;
	if (alpha == 0 || alpha == PI)
		return (CUB_SIDE);
	xa = CUB_SIDE / tan(alpha);
	if (facing_down(alpha))
		xa *= -1;
	return (xa);
}

/*
** Calculates the distance between vertical intersections in the grid,
** applies a correction in sign depending on the angle
*/
float	get_ya(float alpha)
{
	float	ya;

	ya = 0;
	if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
		return (CUB_SIDE);
	ya = CUB_SIDE * tan(alpha);
	if (facing_right(alpha, 0))
		ya *= -1;
	return (ya);
}

/* Sets if player is facing a N/S or W/E wall */
void	set_wall_side(t_game *g, float horizontal, float vertical)
{
	if (horizontal == -1 && vertical > 0)
		g->wall_side = 1;
	else if (vertical == -1 && horizontal > 0)
		g->wall_side = 0;
	else if (horizontal > vertical)
		g->wall_side = 1;
	else
		g->wall_side = 0;
}

void	set_texture(t_game *g, bool horiz)
{
	if (horiz)
	{
		g->draw_offset_y = -1;
		if (facing_up(g->alpha))
			g->right_texture = &g->sprites[N];
		else
			g->right_texture = &g->sprites[S];
	}
	else
	{
		g->draw_offset_x = -1;
		if (facing_left(g->alpha, 0))
			g->right_texture = &g->sprites[W];
		else
			g->right_texture = &g->sprites[E];
	}
}
