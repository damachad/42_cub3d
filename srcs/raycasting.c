/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/02/13 16:04:48 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Later adapt to get map from t_game
bool	is_wall(int x, int y)
{
	if (map[x][y] && map[x][y] == 1)// Probably a repetition, how to check if the position is valid?
		return (true);
	else
		return (false);
}

/* Formula to get the distance */
// float	get_distance(t_point a, t_point p, float alpha)
// {
// 	float	distance;

// 	distance = 0;
// 	if (alpha > 0 && alpha < PI)
// 		distance = fabs(p.x - a.x) / fabs(cos(alpha));
// 	else if (alpha > PI && alpha < PI_DOUBLE)
// 		distance = fabs(p.x - a.x) / fabs(cos(alpha - PI));
// 	else if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
// 		distance = fabs(p.y - a.y);
// 	else if (alpha == PI || alpha == 0)
// 		distance = fabs(p.x - a.x);
// 	return (distance);
// }

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
	xa = CUB_SIDE / tan(alpha);
	if (alpha > PI && alpha < PI_DOUBLE)
		xa *= -1;
	return (xa);
}

/* Calculates the distance between vertical intersections in the grid,
aplies a correction in sign depending on the angle */
float	get_ya(float alpha)
{
	float	ya;

	ya = 0;
	ya = CUB_SIDE * tan(alpha);
	if (alpha > PI_THREE_HALFS || alpha < PI_HALF)
		ya *= -1;
	return (ya);
}

float	wall_dist_horizontal(t_point p, float alpha)
{
	t_point 	a;
	t_point		offset;
 
	offset.y = 0;
	if (alpha > 0 && alpha < PI)// If the ray is facing up
	{
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE - 1;
		a.x = p.x + fabs(p.y - a.y) / tan(alpha);
		offset.y = -1 * CUB_SIDE;
	}
	else if (alpha > PI && alpha < PI_DOUBLE)// If the ray is facing down
	{
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		a.x = p.x + fabs(p.y - a.y) / tan(alpha);
		// a.x = p.x + (p.y - a.y) * (-1 / tan(alpha));
		offset.y = CUB_SIDE;
	}
	else
	{
		a.y = p.y;
		a.x = p.x;
	}
	// a.x = p.x + fabs(p.y - a.y) / tan(alpha);// not sure about this formula
	offset.x = get_xa(alpha);
	// offset.x = -1 * offset.y * (-1 / tan(alpha));
	// Check for wall collision on horizontal lines
	while (a.x < SCREEN_WIDTH && a.x > 0 && a.y > 0 && a.y < SCREEN_HEIGHT)// should be while in map range
	{
		if (is_wall(a.x / CUB_SIDE, a.y / CUB_SIDE))
			return (get_distance(a, p, alpha));
		else
		{
			a.x += offset.x;
			a.y += offset.y;
		}
	}
	return (-1);
}

// float	wall_dist_horizontal(t_point p, float alpha)
// {
// 	t_point 	a;
// 	t_point		offset;
// 	int			dof;
	
// 	offset.y = 0;
// 	offset.x = 0;
// 	dof = 0;
// 	if (alpha < PI)// If the ray is facing up
// 	{
// 		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE - 0.0001;
// 		offset.y = -1 * CUB_SIDE;
// 	}
// 	else if (alpha > PI)// If the ray is facing down
// 	{
// 		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
// 		offset.y = CUB_SIDE;
// 	}
// 	else if (alpha == PI || alpha == 0)
// 	{
// 		a.y = p.y;
// 		a.x = p.x;
// 	}
// 	a.x = p.x + (p.y - a.y) * (-1 / tan(alpha));
// 	offset.x = -1 * offset.y * (-1 / tan(alpha));
// 	while (dof < 10)
// 	{
		
// 	}
// 	return (-1);
// }

// Transform alpha so that when it is bigger than 2PI, resets to 0
float	wall_dist_vertical(t_point p, float alpha)
{
	t_point 	b;
	t_point		offset;

	offset.x = 0;
	if (alpha > PI_HALF && alpha < PI_THREE_HALFS)// If the ray is facing left
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE - 0.0001;
		b.y = p.y - fabs(p.x - b.x) * tan(alpha);
		offset.x = -1 * CUB_SIDE;
	}
	else if (alpha < PI_HALF || alpha > PI_THREE_HALFS)// If the ray is facing right
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		b.y = p.y - fabs(p.x - b.x) * tan(alpha);
		offset.x = CUB_SIDE;
	}
	else if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
	{
		b.x = p.x;
		b.y = p.y;
	}
	// b.y = p.y - fabs(p.x - b.x) * tan(alpha);// not sure about this formula
	offset.y = get_ya(alpha);
	// offset.y = -1 * offset.x * (-1 * tan(alpha));
	// Check for wall collision on horizontal lines
	while (b.x < SCREEN_WIDTH && b.x > 0 && b.y > 0 && b.y < SCREEN_HEIGHT)
	{
		if (is_wall(b.x / CUB_SIDE, b.y / CUB_SIDE))
			return (get_distance(b, p, alpha));
		else
		{
			b.x += offset.x;
			b.y += offset.y;
		}
	}
	return (-1);
}

/* Returns shorter distance
If one method failed to find wall, return the distance obtained 
by the other */
float	shorter_distance(float horizontal, float vertical)
{
	if (horizontal == -1 && vertical == -1)
		return (-1);
	else if (horizontal == -1 && vertical > 0)
		return (vertical);
	else if (vertical == -1 && horizontal > 0)
		return (horizontal);
	else if (horizontal > vertical)
		return (vertical);
	else
		return (horizontal);
}

int	draw_wall(t_game *g)
{
	int		x;
	float	alpha;
	float	d_to_wall;
	float	proj_wall_height;
	float	d_to_proj_plane;
	
	alpha = g->p_angle + ((float)FOV / 2);
	// printf("g->p_angle: %f\n", g->p_angle);
	if (alpha >= PI_DOUBLE)
		alpha -= PI_DOUBLE;
	x = -1;
	d_to_wall = 0;
	proj_wall_height = 0;
	d_to_proj_plane = (SCREEN_WIDTH / 2) / tan((float)FOV / 2);// later initialize this variable in t_game or define as macro
	g->img = new_img(g);
	draw_background(&(g->img));
	draw_minimap(g);
	while (++x < SCREEN_WIDTH)
	{
		d_to_wall = shorter_distance(wall_dist_horizontal(g->p_pos, alpha), wall_dist_vertical(g->p_pos, alpha));
		// printf("Iteration: %d\n", x);
		// printf("alpha: %f\n", alpha);
		if (d_to_wall == -1)
		{
			ft_putstr_fd("Error calculating wall distance\n", 2);
			break;
		}
		d_to_wall *= cos(fabs(g->p_angle - alpha));// fisheye-correction
		// printf("d_to_wall: %f\n", d_to_wall);
		proj_wall_height = (CUB_SIDE / d_to_wall * d_to_proj_plane);
		draw_line(g, &(t_point_int){x, SCREEN_HEIGHT / 2 + proj_wall_height / 2}, &(t_point_int){x, SCREEN_HEIGHT / 2 - proj_wall_height / 2});
		alpha -= (float)1/SCREEN_WIDTH;
		if (alpha < 0)
			alpha += PI_DOUBLE;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_destroy_image(g->mlx, g->img.img);
	return(0);
}
