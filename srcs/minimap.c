/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by damachad          #+#    #+#             */
/*   Updated: 2024/03/12 14:49:21 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_game *g, int x, int y, int size, int color)
{
	int	i;
	int	j;
	t_img *img;

	i = 0;
	img = &g->img;
	while (i < size * g->minimap_scale && i + size * g->minimap_scale < img->height)
	{
		j = 0;
		while (j < size * g->minimap_scale && j + size * g->minimap_scale < img->width)
		{
			put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	set_scale_minimap(t_game *g, int rows, int cols)
{
	int	bigger;

	if (rows > cols)
		bigger = rows;
	else
		bigger = cols;
	g->minimap_scale = MINIMAP_SCALE / (float)bigger;
}

void	mini_backgroud(t_game *g, int offset)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < g->map_rows)
	{
		j = -1;
		while (++j < g->map_cols && g->map[i][j])
		{
			if (g->map[i][j] == '1')
				draw_square(g, (j * CUB_SIDE * g->minimap_scale) + offset, \
				(i * CUB_SIDE * g->minimap_scale) + offset, CUB_SIDE, WHITE);
			else
				draw_square(g, (j * CUB_SIDE * g->minimap_scale) + offset, \
				(i * CUB_SIDE * g->minimap_scale) + offset, CUB_SIDE, BLACK);
		}
	}
}

void	draw_minimap(t_game *g)
{
	int		offset;

	offset = 5;
	set_scale_minimap(g, g->map_rows, g->map_cols);
	mini_backgroud(g, offset);
	draw_square(g, (int)(g->p_pos.x * g->minimap_scale) + offset - 2.5, \
	(int)(g->p_pos.y * g->minimap_scale) + offset - 2.5, 5 / g->minimap_scale, RED);
	draw_line(g, &(t_point_int){(int)(g->p_pos.x * g->minimap_scale) + offset, \
	(int)(g->p_pos.y * g->minimap_scale) + offset}, \
	&(t_point_int){(int)(g->p_pos.x * g->minimap_scale + g->p_dir.x * 5) + offset, \
	(int)(g->p_pos.y * g->minimap_scale + g->p_dir.y * 5) + offset}, RED);
}
