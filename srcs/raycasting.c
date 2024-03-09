/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/03/09 11:47:40 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_wall(t_game *g, int x, int y)
{
	if (x < g->map_cols && y < g->map_rows && g->map[y][x] && g->map[y][x] == '1')
		return (true);
	else
		return (false);
}

float	get_distance(t_point a, t_point p, float alpha)
{
	(void)alpha;
	return (sqrt(pow(a.x - p.x, 2) + pow(a.y - p.y, 2)));
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

float	wall_dist_horizontal(t_game *g, t_point p, float alpha, bool set)
{
	t_point 	a;
	t_point		offset;
 
	offset.y = 0;
	if (facing_up(alpha))
	{
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE - 0.0001;
		a.x = p.x + (p.y - a.y) / tan(alpha);
		offset.y = -1 * CUB_SIDE;
	}
	else if (facing_down(alpha))
	{
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		a.x = p.x + (p.y - a.y) / tan(alpha);
		// a.x = p.x + (p.y - a.y) * (-1 / tan(alpha));
		offset.y = CUB_SIDE;
	}
	else if (alpha == PI || alpha == 0)
	{
		a.y = p.y;
		a.x = p.x;
	}
	offset.x = get_xa(alpha);
	// offset.x = -1 * offset.y * (-1 / tan(alpha));
	// Check for wall collision on horizontal lines
	while (a.x < g->map_cols * CUB_SIDE && a.x > 0 && a.y > 0 && a.y < g->map_rows * CUB_SIDE)// should be while in map range
	{
		if (is_wall(g, a.x / CUB_SIDE, a.y / CUB_SIDE))
		{
			if (set)
				g->draw_offset_x = (int)a.x % CUB_SIDE;
			return (get_distance(a, p, alpha));
		}
		else
		{
			a.x += offset.x;
			a.y += offset.y;
		}
	}
	return (-1);
}

// Transform alpha so that when it is bigger than 2PI, resets to 0
float	wall_dist_vertical(t_game *g, t_point p, float alpha, bool set)
{
	t_point 	b;
	t_point		offset;

	offset.x = 0;
	if (facing_left(alpha, 0))
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE - 0.0001;
		b.y = p.y + (p.x - b.x) * tan(alpha);
		offset.x = -1 * CUB_SIDE;
	}
	else if (facing_right(alpha, 0))
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		b.y = p.y + (p.x - b.x) * tan(alpha);
		offset.x = CUB_SIDE;
	}
	else if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
	{
		b.x = p.x;
		b.y = p.y;
	}
	offset.y = get_ya(alpha);
	// offset.y = -1 * offset.x * (-1 * tan(alpha));
	// Check for wall collision on horizontal lines
	while (b.x < g->map_cols * CUB_SIDE && b.x > 0 && b.y > 0 && b.y < g->map_rows * CUB_SIDE)
	{
		if (is_wall(g, b.x / CUB_SIDE, b.y / CUB_SIDE))
		{
			if (set)
				g->draw_offset_y = (int)b.y % CUB_SIDE;
			return (get_distance(b, p, alpha));
		}
		else
		{
			b.x += offset.x;
			b.y += offset.y;
		}
	}
	return (-1);
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

/* Returns shorter distance, chooses bitmap offset for wall texture, 
and selects the right texture
If one method failed to find wall, return the distance obtained 
by the other */
float	shorter_distance(t_game *g, float horizontal, float vertical, bool p_ray)
{
	float	shorter;

	shorter = horizontal;
	if (horizontal == -1 && vertical == -1)
		return (-1);
	if (p_ray)
		set_wall_side(g, horizontal, vertical);
	if ((horizontal == -1 && vertical > 0) || (horizontal > vertical && vertical >= 0))
		shorter = vertical;
	if (shorter == horizontal)
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

int	draw_wall(t_game *g)
{
	int		x;
	float	d_to_wall;
	float	proj_wall_height;
	float	d_to_proj_plane;
	float	back_angle;
	
	g->alpha = g->p_angle + ((float)FOV / 2);
	if (g->alpha >= PI_DOUBLE)
		g->alpha -= PI_DOUBLE;
	x = -1;
	d_to_wall = 0;
	proj_wall_height = 0;
	d_to_proj_plane = (SCREEN_WIDTH / 2) / tan((float)FOV / 2);// later initialize this variable in t_game or define as macro
	g->img = new_img(g);
	draw_background(g);
	draw_minimap(g);
	while (++x < SCREEN_WIDTH)
	{
		d_to_wall = shorter_distance(g, wall_dist_horizontal(g, g->p_pos, g->alpha, 1), wall_dist_vertical(g, g->p_pos, g->alpha, 1), \
		(fabs(g->alpha - g->p_angle) < (float)1/SCREEN_WIDTH));
		if (fabs(g->alpha - g->p_angle) < (float)1/SCREEN_WIDTH)
		{
			back_angle = g->p_angle - PI;
			if (back_angle < 0)
				back_angle += PI_DOUBLE;
			set_back_wall(g, wall_dist_horizontal(g, g->p_pos, back_angle, 0), wall_dist_vertical(g, g->p_pos, back_angle, 0));
		}
		if (d_to_wall == -1)
		{
			ft_putstr_fd("Error calculating wall distance\n", 2);
			break;
		}
		d_to_wall *= fisheye_correction(g->p_angle, g->alpha);// Not working perfectly
		// d_to_wall *= cos(fabs(g->p_angle - alpha));// fisheye-correction
		proj_wall_height = (CUB_SIDE / d_to_wall * d_to_proj_plane);
		draw_column(g, x, (float)(SCREEN_HEIGHT / 2 + proj_wall_height / 2), proj_wall_height);
		g->alpha -= (float)1/SCREEN_WIDTH;
		if (g->alpha < 0)
			g->alpha += PI_DOUBLE;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_destroy_image(g->mlx, g->img.img);
	return(0);
}
