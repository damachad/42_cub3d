/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:45:44 by damachad          #+#    #+#             */
/*   Updated: 2024/03/23 18:44:41 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/*
** Returns shorter distance, chooses bitmap offset for wall texture, 
** and selects the right texture
** If one method failed to find wall, return the distance obtained 
** by the other
*/
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
		return ;
	if (horizontal == -1 && vertical > 0)
		g->back_wall = 1;
	else if (vertical == -1 && horizontal > 0)
		g->back_wall = 0;
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

void	draw_wall_assist(t_game *g, int x)
{
	float	d_to_wall;
	float	p_w_height;

	d_to_wall = 0;
	p_w_height = 0;
	d_to_wall = shorter_distance(g, wall_dist_horiz(g, g->p_pos, g->alpha, 1), \
	wall_dist_vertical(g, g->p_pos, g->alpha, 1), \
	(fabs(g->alpha - g->p_angle) < (float)1 / SCREEN_WIDTH));
	if (fabs(g->alpha - g->p_angle) < (float)1 / SCREEN_WIDTH)
	{
		g->p_b_angle = set_angle(g->p_angle - PI);
		set_back_wall(g, wall_dist_horiz(g, g->p_pos, g->p_b_angle, 0), \
		wall_dist_vertical(g, g->p_pos, g->p_b_angle, 0));
	}
	if (d_to_wall == -1)
	{
		ft_putstr_fd("Error calculating wall distance\n", 2);
		return ;
	}
	d_to_wall *= fisheye_correction(g->p_angle, g->alpha);
	p_w_height = (CUB_SIDE / d_to_wall * g->d_proj_plane);
	draw_column(g, x, (float)(SCREEN_HEIGHT / 2 + p_w_height / 2), p_w_height);
}

int	draw_wall(t_game *g)
{
	int		x;

	x = -1;
	g->alpha = set_angle(g->p_angle + ((float)FOV / 2));
	g->img = new_img(g);
	draw_background(g);
	draw_minimap(g);
	while (++x < SCREEN_WIDTH)
	{
		draw_wall_assist(g, x);
		g->alpha = set_angle(g->alpha - (float)1 / SCREEN_WIDTH);
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_destroy_image(g->mlx, g->img.img);
	return (0);
}
