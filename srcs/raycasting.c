/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/03/17 12:02:48 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_wall(t_game *g, int x, int y)
{
	if (x < g->map_cols && y < g->map_rows && g->map[y][x] \
	&& g->map[y][x] == '1')
		return (true);
	else
		return (false);
}

/* Calculates the distance between horizontal intersections in the grid,
aplies a correction in sign depending on the angle */
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

/* Calculates the distance between vertical intersections in the grid,
aplies a correction in sign depending on the angle */
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

// Check for wall collision on horizontal lines
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

/* Sets if player is facing a N/S or W/E wall */
void	set_wall_side(t_game *g, float horizontal, float vertical)
{
	if (horizontal == -1 && vertical > 0)
		g->wall_side = 1; // vertical
	else if (vertical == -1 && horizontal > 0)
		g->wall_side = 0; // horizontal
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

/* Returns shorter distance, chooses bitmap offset for wall texture, 
and selects the right texture
If one method failed to find wall, return the distance obtained 
by the other */
float	shorter_distance(t_game *g, float horiz, float vertical, bool p_ray)
{
	float	shorter;

	shorter = horiz;
	if (horiz == -1 && vertical == -1)
		return (-1);
	if (p_ray)
		set_wall_side(g, horiz, vertical);
	if ((horiz == -1 && vertical > 0) || (horiz > vertical && vertical >= 0))
		shorter = vertical;
	set_texture(g, shorter == horiz);
	return (shorter);
}

/* Sets if player's back is facing a N/S or W/E wall */
void	set_back_wall(t_game *g, float horizontal, float vertical)
{
	if (horizontal == -1 && vertical == -1)
		return;
	if (horizontal == -1 && vertical > 0)
		g->back_wall = 1; // vertical
	else if (vertical == -1 && horizontal > 0)
		g->back_wall = 0; // horizontal
	else if (horizontal > vertical)
		g->back_wall = 1;
	else
		g->back_wall = 0;
}

float	fisheye_correction(float pa, float ra)
{
	float	ca;
	
	ca = pa - ra;
	if (ca < 0)
		ca += PI_DOUBLE;
	else if (ca > PI_DOUBLE)
		ca -= PI_DOUBLE;
	return (cos(ca));
}

void draw_wall_assist(t_game *g, float d_to_proj_plane, int x)
{
	float	d_to_wall;
	float	p_w_height;
	float	back_angle;

	d_to_wall = 0;
	p_w_height = 0;
	d_to_wall = shorter_distance(g, wall_dist_horiz(g, g->p_pos, g->alpha, 1), \
	wall_dist_vertical(g, g->p_pos, g->alpha, 1), \
	(fabs(g->alpha - g->p_angle) < (float)1/SCREEN_WIDTH));
	if (fabs(g->alpha - g->p_angle) < (float)1/SCREEN_WIDTH)
	{
		back_angle = g->p_angle - PI;
		if (back_angle < 0)
			back_angle += PI_DOUBLE;
		set_back_wall(g, wall_dist_horiz(g, g->p_pos, back_angle, 0), \
		wall_dist_vertical(g, g->p_pos, back_angle, 0));
	}
	if (d_to_wall == -1)
	{
		ft_putstr_fd("Error calculating wall distance\n", 2);
		return;
	}
	d_to_wall *= fisheye_correction(g->p_angle, g->alpha);// Not working perfectly
	p_w_height = (CUB_SIDE / d_to_wall * d_to_proj_plane);
	draw_column(g, x, (float)(SCREEN_HEIGHT / 2 + p_w_height / 2), p_w_height);
}

int	draw_wall(t_game *g)
{
	int		x;
	float	d_to_proj_plane;
	
	x = -1;
	g->alpha = g->p_angle + ((float)FOV / 2);
	if (g->alpha >= PI_DOUBLE)
		g->alpha -= PI_DOUBLE;
	d_to_proj_plane = (SCREEN_WIDTH / 2) / tan((float)FOV / 2);// later initialize this variable in t_game or define as macro
	g->img = new_img(g);
	draw_background(g);
	draw_minimap(g);
	while (++x < SCREEN_WIDTH)
	{
		draw_wall_assist(g, d_to_proj_plane, x);
		g->alpha -= (float)1/SCREEN_WIDTH;
		if (g->alpha < 0)
			g->alpha += PI_DOUBLE;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_destroy_image(g->mlx, g->img.img);
	return(0);
}
