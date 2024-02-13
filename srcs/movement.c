/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:10:59 by damachad          #+#    #+#             */
/*   Updated: 2024/02/13 16:04:37 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keysym, t_game *g)
{
	float	a;

	a = g->p_angle;
	if (keysym == XK_Escape)
		quit_prog(g);
	else if (keysym == XK_w)
	{
		g->p_pos.x += g->p_dir.x;
		g->p_pos.y += g->p_dir.y;
	}
	else if (keysym == XK_a)
	{
		g->p_angle += 0.1;
		if (g->p_angle >= PI_DOUBLE)
			g->p_angle -= PI_DOUBLE;
		g->p_dir = (t_point){cos(a) * 5, sin(a) * -5};
	}
	else if (keysym == XK_s)
	{
		g->p_pos.x -= g->p_dir.x;
		g->p_pos.y -= g->p_dir.y;
	}
	else if (keysym == XK_d)
	{
		g->p_angle -= 0.1;
		if (g->p_angle < 0)
			g->p_angle += PI_DOUBLE;
		g->p_dir = (t_point){cos(a) * 5, sin(a) * -5};
	}
	else
		return (0);
	// printf("g->p_pos.x: %f\n", g->p_pos.x);
	// printf("g->p_pos.y: %f\n", g->p_pos.y);
	draw_wall(g);
	return (keysym);
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (size - 4) * MINIMAP_SCALE && i + size * MINIMAP_SCALE < img->height)
	{
		j = 0;
		while (j < (size - 4) * MINIMAP_SCALE && j + size * MINIMAP_SCALE < img->width)
		{
			put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *g)// replace with map dimensions
{
	int		i;
	int		j;
	int		offset;

	i = -1;
	j = -1;
	offset = 5;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if (map[i][j] == 1)
				draw_square(&g->img, (i * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(j * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, WHITE);
			else
				draw_square(&g->img, (i * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(j * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, BLACK);
		}
	}
	draw_square(&g->img, (int)g->p_pos.x * MINIMAP_SCALE + offset - 3.5, \
	(int)g->p_pos.y * MINIMAP_SCALE + offset - 3.5, CUB_SIDE / 3, RED);
	draw_line(g, &(t_point_int){(int)g->p_pos.x * MINIMAP_SCALE + offset, \
	(int)g->p_pos.y * MINIMAP_SCALE + offset}, \
	&(t_point_int){(int)(g->p_pos.x + g->p_dir.x) * 0.4 + offset, \
	(int)(g->p_pos.y + g->p_dir.y) * 0.4 + offset});
}
