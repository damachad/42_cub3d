/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:16:23 by damachad          #+#    #+#             */
/*   Updated: 2024/04/01 16:41:46 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_square(t_game *g, t_point_int point, int size, int color)
{
	int		i;
	int		j;
	t_img	*img;

	i = 0;
	img = &g->img;
	while (i < size * g->mini_scale && \
	i + size * g->mini_scale < img->height)
	{
		j = 0;
		while (j < size * g->mini_scale && \
		j + size * g->mini_scale < img->width)
		{
			put_pixel(img, point.x + i, point.y + j, color);
			j++;
		}
		i++;
	}
}

static void	set_scale_minimap(t_game *g)
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
	g->mini_scale = MINIMAP_SCALE / (float)bigger;
}

static void	mini_background(t_game *g, int offset)
{
	size_t		i;
	size_t		j;
	t_point_int	point;

	i = g->l_top;
	while (i <= g->l_bottom)
	{
		j = g->l_left;
		while (j <= g->l_right && g->map[i][j])
		{
			point.x = (j - g->l_left) * CUB_SIDE * g->mini_scale + offset;
			point.y = (i - g->l_top) * CUB_SIDE * g->mini_scale + offset;
			if (g->map[i][j] == '1')
				draw_square(g, point, CUB_SIDE, WHITE);
			else if (ft_strchr("0NSWE", g->map[i][j]))
				draw_square(g, point, CUB_SIDE, BLACK);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *g)
{
	int			offset;
	t_point_int	point;

	offset = 5;
	set_scale_minimap(g);
	mini_background(g, offset);
	point.x = (int)((g->p_pos.x - g->l_left * CUB_SIDE) * \
	g->mini_scale) + offset - 2.5;
	point.y = (int)((g->p_pos.y - g->l_top * CUB_SIDE) * \
	g->mini_scale) + offset - 2.5;
	draw_square(g, point, 5 / g->mini_scale, RED);
	draw_line(&g->img, &(t_point_int){(int)(point.x + 2.5), \
	(int)(point.y + 2.5)}, &(t_point_int){(int)(point.x \
	- offset + 2.5 + g->p_dir.x * 5) + offset, \
	(int)(point.y - offset + 2.5 + g->p_dir.y * 5) + offset}, \
	RED);
}
