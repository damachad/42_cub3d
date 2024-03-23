/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by damachad          #+#    #+#             */
/*   Updated: 2024/03/22 16:43:33 by arepsa           ###   ########.fr       */
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
	while (i < size * g->minimap_scale && \
	i + size * g->minimap_scale < img->height)
	{
		j = 0;
		while (j < size * g->minimap_scale && \
		j + size * g->minimap_scale < img->width)
		{
			put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	set_scale_minimap(t_game *g)
{
	int	bigger;
	int	rows;
	int	cols;

	rows = g->l_bottom - g->l_top + 1;
	cols = g->l_right - g->l_left + 1;
	if (rows > cols)
		bigger = rows;
	else
		bigger = cols;
	g->minimap_scale = MINIMAP_SCALE / (float)bigger;
}

void	mini_background(t_game *g, int offset)
{
	size_t i;
    size_t j;

	i = g->l_top;
    while (i <= g->l_bottom) {
        j = g->l_left;
        while (j <= g->l_right && g->map[i][j]) {
            if (g->map[i][j] == '1')
                draw_square(g, (j - g->l_left) * CUB_SIDE * g->minimap_scale + offset,
                            (i - g->l_top) * CUB_SIDE * g->minimap_scale + offset,
                            CUB_SIDE, WHITE);
            else if (ft_strchr("0NSWE", g->map[i][j]))
                draw_square(g, (j - g->l_left) * CUB_SIDE * g->minimap_scale + offset,
                            (i - g->l_top) * CUB_SIDE * g->minimap_scale + offset,
                            CUB_SIDE, BLACK);
            j++;
        }
        i++;
    }
}

void	draw_minimap(t_game *g)
{
	int		offset;

	offset = 5;
	set_scale_minimap(g);
	mini_background(g, offset);
	draw_square(g, (int)(g->p_pos.x * g->minimap_scale) + offset - 2.5, \
	(int)(g->p_pos.y * g->minimap_scale) + offset - 2.5, 5 / \
	g->minimap_scale, RED);
	draw_line(g, &(t_point_int){(int)(g->p_pos.x * g->minimap_scale) + \
	offset, (int)(g->p_pos.y * g->minimap_scale) + offset}, \
	&(t_point_int){(int)(g->p_pos.x * g->minimap_scale + g->p_dir.x * 5) + \
	offset, (int)(g->p_pos.y * g->minimap_scale + g->p_dir.y * 5) + offset}, \
	RED);
}
