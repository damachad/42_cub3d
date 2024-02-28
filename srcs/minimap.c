/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by damachad          #+#    #+#             */
/*   Updated: 2024/02/28 15:18:32 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	while (++i < 10) // update with actual map height
	{
		j = -1;
		while (++j < 10) // update with actual map width
		{
			if (g->map[i][j] == '1')
				draw_square(&g->img, (j * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(i * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, WHITE);
			else
				draw_square(&g->img, (j * CUB_SIDE * MINIMAP_SCALE) + offset, \
				(i * CUB_SIDE * MINIMAP_SCALE) + offset, CUB_SIDE, BLACK);
		}
	}
	draw_square(&g->img, (int)g->p_pos.x * MINIMAP_SCALE + offset - 3.5, \
	(int)g->p_pos.y * MINIMAP_SCALE + offset - 3.5, CUB_SIDE / 3, RED);
	draw_line(g, &(t_point_int){(int)(g->p_pos.x * MINIMAP_SCALE) + offset, \
	(int)(g->p_pos.y * MINIMAP_SCALE) + offset}, \
	&(t_point_int){(int)(g->p_pos.x * MINIMAP_SCALE + g->p_dir.x * 5) + offset, \
	(int)(g->p_pos.y * MINIMAP_SCALE + g->p_dir.y * 5) + offset}, RED);
}
