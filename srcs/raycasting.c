/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/02/09 15:16:51 by damachad         ###   ########.fr       */
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

t_point	player = {(double)3 * CUB_SIDE + CUB_SIDE/2, (double)3 * CUB_SIDE + CUB_SIDE/2};

// Later adapt to get map from t_game
bool	is_wall(int x, int y)
{
	if (map[x][y] && map[x][y] == 1)// Probably a repetition, how to check if the position is valid?
		return (true);
	else
		return (false);
}

/* Formula to get the distance */
double	get_distance(t_point a, t_point p, double alpha)
{
	double	distance;

	distance = 0;
	if (alpha > 0 && alpha < PI)
		distance = fabs(p.x - a.x) / fabs(cos(alpha));
	else if (alpha > PI && alpha < PI_DOUBLE)
		distance = fabs(p.x - a.x) / fabs(cos(alpha - PI));
	else if (alpha == PI_HALF || alpha == PI_THREE_HALFS)
		distance = fabs(p.y - a.y);
	else if (alpha == PI || alpha == 0)
		distance = fabs(p.x - a.x);
	// printf("distance: %f\n", distance);
	return (distance);
}

/* Calculates the distance between horizontal intersections in the grid,
aplies a correction in sign depending on the angle */
double	get_xa(double alpha)
{
	double	xa;

	xa = 0;
	xa = CUB_SIDE / tan(alpha);
	if (alpha > PI && alpha < PI_DOUBLE)
		xa *= -1;
	// printf("xa: %f\n", xa);
	return (xa);
}

/* Calculates the distance between vertical intersections in the grid,
aplies a correction in sign depending on the angle */
double	get_ya(double alpha)
{
	double	ya;

	ya = 0;
	ya = CUB_SIDE * tan(alpha);
	if (alpha > PI_THREE_HALFS || alpha < PI_HALF)
		ya *= -1;
	// printf("get ya: %f\n", ya);
	return (ya);
}

double	wall_dist_horizontal(t_point p, double alpha)
{
	t_point 	a;
	double		ya;
	double		xa;

// ======Finding horizontal intersection ======
// 1. Finding the coordinates of A.  
	if (alpha > 0 && alpha < PI)// If the ray is facing up
	{
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE - 1;
		// 2. Finding Ya
		ya = -1 * CUB_SIDE;
	}
	else if (alpha > PI && alpha < PI_DOUBLE)// If the ray is facing down
	{
		// transform alpha so angle is acute
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		ya = CUB_SIDE;
	}
	else
		a.y = p.y;
	a.x = p.x + fabs(p.y - a.y) / tan(alpha);// not sure about this formula
	// 3. Finding Xa
	xa = get_xa(alpha);
	// printf("a.y: %f\n", a.y);
	// printf("a.x: %f\n", a.x);
	// printf("xa: %f\n", xa);
	// printf("ya: %f\n", ya);
	// Check for wall collision on horizontal lines
	while (a.x < SCREEN_WIDTH && a.x > 0 && a.y > 0 && a.y < SCREEN_HEIGHT)// should be while in map range
	{
		// printf("horizontal a.x: %f\n", a.x / CUB_SIDE);
		// printf("horizontal a.y: %f\n", a.y / CUB_SIDE);
		if (is_wall(a.x / CUB_SIDE, a.y / CUB_SIDE))
			return (get_distance(a, p, alpha));
		else
		{
			a.x += xa;
			a.y += ya;
		}
	}
	return (-1);
}

// Transform alpha so that when it is bigger than 2PI, resets to 0
double	wall_dist_vertical(t_point p, double alpha)
{
	t_point 	b;
	double		ya;
	double		xa;

// ======Finding vertical intersection ======
// 1. Finding the coordinates of B.  
	if (alpha > PI_HALF && alpha < PI_THREE_HALFS)// If the ray is facing left
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE - 1;
		// 2. Finding Xa
		xa = -1 * CUB_SIDE;
	}
	else if (alpha < PI_HALF || alpha > PI_THREE_HALFS)// If the ray is facing right
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		xa = CUB_SIDE;
	}
	else
		b.x = p.x;
	b.y = p.y - fabs(p.x - b.x) * tan(alpha);// not sure about this formula
	// 3. Finding Ya
	ya = get_ya(alpha);
	// printf("xa: %f\n", xa);
	// printf("ya: %f\n", ya);
	// printf("b.y: %f\n", b.y);
	// printf("b.x: %f\n", b.x);
	// Check for wall collision on horizontal lines
	while (b.x < SCREEN_WIDTH && b.x > 0 && b.y > 0 && b.y < SCREEN_HEIGHT)
	{
		// printf("vertical b.x: %f\n", b.x / CUB_SIDE);
		// printf("vertical b.y: %f\n", b.y / CUB_SIDE);
		if (is_wall(b.x / CUB_SIDE, b.y / CUB_SIDE))
			return (get_distance(b, p, alpha));
		else
		{
			b.x += xa;
			b.y += ya;
		}
	}
	return (-1);
}

/* Returns shorter distance
If one method failed to find wall, return the distance obtained 
by the other */
double	shorter_distance(double horizontal, double vertical)
{
	// printf("horizontal: %f\n", horizontal);
	// printf("vertical: %f\n", vertical);
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

void	draw_wall(t_game *game)
{
	int		x;
	double	alpha;
	double	beta;
	double	d_to_wall;
	double	proj_wall_height;
	double	d_to_proj_plane;
	
	alpha = (double)START_ANGLE + ((double)FOV / 2);
	beta = (double)START_ANGLE;
	if (alpha >= PI_DOUBLE)
		alpha -= PI_DOUBLE;
	x = -1;
	d_to_wall = 0;
	proj_wall_height = 0;
	(void)game;
	d_to_proj_plane = (SCREEN_WIDTH / 2) / tan((double)FOV / 2);// later initialize this variable in t_game or define as macro
	(void)x;
	while (++x < SCREEN_WIDTH)
	{
		d_to_wall = shorter_distance(wall_dist_horizontal(player, alpha), wall_dist_vertical(player, alpha));
		// printf("Iteration: %d\n", x);
		// printf("alpha: %f\n", alpha);
		if (d_to_wall == -1)
		{
			ft_putstr_fd("Error calculating wall distance\n", 2);
			break;
		}
		d_to_wall *= cos(fabs(beta - alpha));// fisheye-correction
		// printf("d_to_wall: %f\n", d_to_wall);
		proj_wall_height = (CUB_SIDE / d_to_wall * d_to_proj_plane);
		draw_line(game, &(t_point_int){x, SCREEN_HEIGHT / 2 + proj_wall_height / 2}, &(t_point_int){x, SCREEN_HEIGHT / 2 - proj_wall_height / 2});
		alpha -= (double)1/SCREEN_WIDTH;
		if (alpha < 0)
			alpha += PI_DOUBLE;
	}
}
