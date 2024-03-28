/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:29:40 by damachad          #+#    #+#             */
/*   Updated: 2024/03/28 10:17:18 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		draw_line(&game->img, &(t_point_int){x, 0}, \
				&(t_point_int){x, SCREEN_HEIGHT / 2}, game->input->c_color);
		draw_line(&game->img, &(t_point_int){x, SCREEN_HEIGHT / 2}, \
				&(t_point_int){x, SCREEN_HEIGHT}, game->input->f_color);
	}
}

int	get_texture_color(t_game *g, t_img *tex, int pixel_x, int pixel_y)
{
	if (tex == &g->sprites[S] || tex == &g->sprites[W])
		pixel_x = CUB_SIDE - pixel_x - 1;
	return (*(int *)(tex->addr + (pixel_y * tex->line_length) + \
	(pixel_x * tex->bpp / 8)));
}

void	draw_column(t_game *g, int x, float y_btm, float wall_h)
{
	int		text_x;
	int		y;
	int		text_y;
	float	step_y;
	float	pos;

	text_x = 0;
	text_y = 0;
	y = y_btm - wall_h;
	if (y < 0)
		y = 0;
	step_y = fabs((float)CUB_SIDE / wall_h);
	pos = (y - (SCREEN_HEIGHT / 2) + (wall_h / 2)) * step_y;
	if (g->draw_offset_x >= 0)
		text_x = g->draw_offset_x;
	else if (g->draw_offset_y >= 0)
		text_x = g->draw_offset_y;
	while (y < y_btm && y < SCREEN_HEIGHT)
	{
		text_y = (int)pos & (CUB_SIDE - 1);
		pos += step_y;
		put_pixel(&g->img, x, y, \
		get_texture_color(g, g->right_texture, text_x, text_y));
		y++;
	}
}
