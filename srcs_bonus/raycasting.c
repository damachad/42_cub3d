/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/03/23 18:48:04 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

float	find_collision_v(t_game *g, t_calc *calc, t_point p, float correct)
{
	while (calc->b.x <= g->map_cols * CUB_SIDE && calc->b.x >= 0 && \
	calc->b.y >= 0 && calc->b.y <= g->map_rows * CUB_SIDE)
	{
		if (is_wall(g, calc->b.x / CUB_SIDE - correct, calc->b.y / CUB_SIDE))
		{
			if (calc->set)
				g->draw_offset_y = (int)calc->b.y % CUB_SIDE;
			return (sqrt(pow(calc->b.x - p.x, 2) + pow(calc->b.y - p.y, 2)));
		}
		else
		{
			calc->b.x += calc->offset.x;
			calc->b.y += calc->offset.y;
		}
	}
	return (-1);
}

float	find_collision_h(t_game *g, t_calc *calc, t_point p, float correct)
{
	while (calc->a.x <= g->map_cols * CUB_SIDE && calc->a.x >= 0 && \
	calc->a.y >= 0 && calc->a.y <= g->map_rows * CUB_SIDE)
	{
		if (is_wall(g, calc->a.x / CUB_SIDE, calc->a.y / CUB_SIDE - correct))
		{
			if (calc->set)
				g->draw_offset_x = (int)calc->a.x % CUB_SIDE;
			return (sqrt(pow(calc->a.x - p.x, 2) + pow(calc->a.y - p.y, 2)));
		}
		else
		{
			calc->a.x += calc->offset.x;
			calc->a.y += calc->offset.y;
		}
	}
	return (-1);
}

/* Check for wall collision on horizontal lines */
float	wall_dist_horiz(t_game *g, t_point p, float alpha, bool set)
{
	float	correct;

	correct = 0;
	if (facing_up(alpha))
	{
		g->calc->a.y = floor(p.y / CUB_SIDE) * CUB_SIDE - 0.0001;
		g->calc->a.x = p.x + (p.y - g->calc->a.y) / tan(alpha);
		correct = 0.1;
		g->calc->offset.y = -1 * CUB_SIDE;
	}
	else if (facing_down(alpha))
	{
		g->calc->a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		g->calc->a.x = p.x + (p.y - g->calc->a.y) / tan(alpha);
		g->calc->offset.y = CUB_SIDE;
	}
	else if (alpha == PI || alpha == 0)
	{
		g->calc->a.y = p.y;
		g->calc->a.x = p.x;
	}
	g->calc->offset.x = get_xa(alpha);
	g->calc->set = set;
	return (find_collision_h(g, g->calc, p, correct));
}

float	wall_dist_vertical(t_game *g, t_point p, float alpha, bool set)
{
	float	correct;

	correct = 0;
	if (facing_left(alpha, 0))
	{
		g->calc->b.x = floor(p.x / CUB_SIDE) * CUB_SIDE - 0.0001;
		g->calc->b.y = p.y + (p.x - g->calc->b.x) * tan(alpha);
		correct = 0.1;
		g->calc->offset.x = -1 * CUB_SIDE;
	}
	else if (facing_right(alpha, 0))
	{
		g->calc->b.x = floor(p.x / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		g->calc->b.y = p.y + (p.x - g->calc->b.x) * tan(alpha);
		g->calc->offset.x = CUB_SIDE;
	}
	else if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
	{
		g->calc->b.x = p.x;
		g->calc->b.y = p.y;
	}
	g->calc->offset.y = get_ya(alpha);
	g->calc->set = set;
	return (find_collision_v(g, g->calc, p, correct));
}
