/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by damachad          #+#    #+#             */
/*   Updated: 2024/03/09 12:43:07 by damachad         ###   ########.fr       */
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
	while (i < (size - 4) * g->minimap_scale && i + size * g->minimap_scale < img->height)
	{
		j = 0;
		while (j < (size - 4) * g->minimap_scale && j + size * g->minimap_scale < img->width)
		{
			put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

// void	draw_square(t_img *img, int x, int y, int size, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < (size - 4) * MINIMAP_SCALE && i + size * MINIMAP_SCALE < img->height)
// 	{
// 		j = 0;
// 		while (j < (size - 4) * MINIMAP_SCALE && j + size * MINIMAP_SCALE < img->width)
// 		{
// 			put_pixel(img, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	set_scale_minimap(t_game *g, int rows, int cols)
{
	int	bigger;

	if (rows > cols)
		bigger = rows;
	else
		bigger = cols;
	g->minimap_scale = 3.0 / (float)bigger;
}

void	draw_minimap(t_game *g)
{
	int		i;
	int		j;
	int		offset;

	i = -1;
	j = -1;
	offset = 5;
	set_scale_minimap(g, g->map_rows, g->map_cols);
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
	draw_square(g, (int)g->p_pos.x * g->minimap_scale + offset - 3.5, \
	(int)g->p_pos.y * g->minimap_scale + offset - 3.5, CUB_SIDE / 3, RED);
	draw_line(g, &(t_point_int){(int)(g->p_pos.x * g->minimap_scale) + offset, \
	(int)(g->p_pos.y * g->minimap_scale) + offset}, \
	&(t_point_int){(int)(g->p_pos.x * g->minimap_scale + g->p_dir.x * 5) + offset, \
	(int)(g->p_pos.y * g->minimap_scale + g->p_dir.y * 5) + offset}, RED);
}
