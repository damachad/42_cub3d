/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:10:59 by damachad          #+#    #+#             */
/*   Updated: 2024/02/15 11:56:47 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_movement(t_game *g)
{
	int		offset;

	offset = 4;
	if (g->keys.w)
	{
		if (!is_wall((g->p_pos.x + g->p_dir.x * offset) / CUB_SIDE, (g->p_pos.y + g->p_dir.y * offset) / CUB_SIDE))
		{
			g->p_pos.x += g->p_dir.x;
			g->p_pos.y += g->p_dir.y;
		}
	}
	else if (g->keys.a)
	{
		g->p_angle += ROT_SPEED;
		if (g->p_angle >= PI_DOUBLE)
			g->p_angle -= PI_DOUBLE;
		g->p_dir = (t_point){cos(g->p_angle) * SPEED, sin(g->p_angle) * -1 * SPEED};
	}
	else if (g->keys.s)
	{
		if (!is_wall((g->p_pos.x - g->p_dir.x * offset) / CUB_SIDE, (g->p_pos.y - g->p_dir.y * offset) / CUB_SIDE))
		{
			g->p_pos.x -= g->p_dir.x;
			g->p_pos.y -= g->p_dir.y;
		}
	}
	else if (g->keys.d)
	{
		g->p_angle -= ROT_SPEED;
		if (g->p_angle < 0)
			g->p_angle += PI_DOUBLE;
		g->p_dir = (t_point){cos(g->p_angle) * SPEED, sin(g->p_angle) * -1 * SPEED};
	}
	draw_wall(g);
	return (0);
}
int	handle_keypress(int keysym, t_game *g)
{
	if (keysym == XK_Escape)
		quit_prog(g);
	else if (keysym == XK_w)
		g->keys.w = 1;
	else if (keysym == XK_a)
		g->keys.a = 1;
	else if (keysym == XK_s)
		g->keys.s = 1;
	else if (keysym == XK_d)
		g->keys.d = 1;
	else
		return (0);
	draw_wall(g);
	return (keysym);
}

int	handle_keyrelease(int keysym, t_game *g)
{
	if (keysym == XK_w)
		g->keys.w = 0;
	else if (keysym == XK_a)
		g->keys.a = 0;
	else if (keysym == XK_s)
		g->keys.s = 0;
	else if (keysym == XK_d)
		g->keys.d = 0;
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
				draw_square(&g->img, (j * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(i * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, WHITE);
			else
				draw_square(&g->img, (j * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(i * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, BLACK);
		}
	}
	draw_square(&g->img, (int)g->p_pos.x * MINIMAP_SCALE + offset - 3.5, \
	(int)g->p_pos.y * MINIMAP_SCALE + offset - 3.5, CUB_SIDE / 3, RED);
	// Draw player direction (HELP, how to apply rotation and maintain length of line)
	draw_line(g, &(t_point_int){(int)g->p_pos.x * MINIMAP_SCALE + offset, \
	(int)g->p_pos.y * MINIMAP_SCALE + offset}, \
	&(t_point_int){(int)(g->p_pos.x + g->p_dir.x * 7) * MINIMAP_SCALE, \
	(int)(g->p_pos.y + g->p_dir.y * 7) * MINIMAP_SCALE});
}
