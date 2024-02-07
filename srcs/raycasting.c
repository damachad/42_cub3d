/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/02/07 15:00:49 by damachad         ###   ########.fr       */
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

t_point	player = {3 * CUB_SIDE, 3 * CUB_SIDE};

// Later adapt to get map from t_game
bool	is_wall(int x, int y)
{
	if (map[x][y] && map[x][y] == 1)
		return (true);
	else
		return (false);
}

/* Formula to get the distance */
double	get_distance(t_point a, t_point p, double alpha)
{
	return (abs(p.x - a.x) / cos(alpha));
}

double	wall_dist_horizontal(t_point p, double alpha)
{
	t_point 	a;
	int			ya;
	int			xa;

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
		a.y = floor(p.y / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		ya = CUB_SIDE;
	}
	else
		a.y = p.y;
	a.x = p.x + abs(p.y - a.y) / tan(alpha);// not sure about this formula
	// 3. Finding Xa
	xa = CUB_SIDE / tan(alpha);
	// Check for wall collision on horizontal lines
	while (a.x < SCREEN_WIDTH && a.x > 0 && a.y > 0 && a.y < SCREEN_HEIGHT)
	{
		if (is_wall(a.x / CUB_SIDE, a.y / CUB_SIDE))
			return (get_distance(p, a, alpha));
		else
		{
			a.x += xa;
			a.y += ya;
		}
	}
	return (0);
}

// Transform alpha so that when it is bigger than 2PI, resets to 0
double	wall_dist_vertical(t_point p, double alpha)
{
	t_point 	b;
	int			ya;
	int			xa;

// ======Finding vertical intersection ======
// 1. Finding the coordinates of A.  
	if (alpha > PI_HALF && alpha < PI_THREE_HALFS)// If the ray is facing left
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE - 1;
		// 2. Finding Xa
		xa = -1 * CUB_SIDE;
	}
	else if (alpha < PI || alpha < PI_THREE_HALFS)// If the ray is facing right
	{
		b.x = floor(p.x / CUB_SIDE) * CUB_SIDE + CUB_SIDE;
		ya = CUB_SIDE;
	}
	else
		b.x = p.x;
	b.y = p.y - abs(p.x - b.x) * tan(alpha);// not sure about this formula
	// 3. Finding Ya
	ya = CUB_SIDE * tan(alpha);
	// Check for wall collision on horizontal lines
	while (b.x < SCREEN_WIDTH && b.x > 0 && b.y > 0 && b.y < SCREEN_HEIGHT)
	{
		if (is_wall(b.x / CUB_SIDE, b.y / CUB_SIDE))
			return (get_distance(p, b, alpha));
		else
		{
			b.x += xa;
			b.y += ya;
		}
	}
	return (0);
}

double	shorter_distance(double horizontal, double vertical)
{
	if (horizontal > vertical)
		return (vertical);
	else
		return (horizontal);
}

void	draw_wall(t_game *game)
{
	int		x;
	double	alpha;
	double	d_to_wall;
	double	proj_wall_height;
	double	d_to_proj_plane;
	
	alpha = START_ANGLE + FOV / 2;
	x = -1;
	d_to_wall = 0;
	proj_wall_height = 0;
	d_to_proj_plane = (PLANE_W / 2) / tan(FOV / 2);// later initialize this variable in t_game or define as macro
	while (++x < SCREEN_WIDTH)
	{
		d_to_wall = shorter_distance(wall_dist_horizontal(player, alpha), wall_dist_vertical(player, alpha));
		proj_wall_height = CUB_SIDE / d_to_wall * d_to_proj_plane;
		draw_line(game, &(t_point){x, SCREEN_HEIGHT / 2 + proj_wall_height / 2}, &(t_point){x, SCREEN_HEIGHT / 2 - proj_wall_height / 2});
		alpha -= 1/PLANE_W;
	}
}
