/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:28:24 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/05 20:28:24 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//customized mlx_pixel_put.... 
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

///in case t_point will contain color....
/* int	get_color(t_dot *a, t_dot *z)
{
	if (a->color != WHITE)
		return (a->color);
	return (WHITE);
} */

/* Set the starting point and decide weather to increment or decrement
* each axis, based on difference between starting and ending points*/
static void	bresenham_define(t_bresenham *param, t_point *a, t_point *b)
{
	param->dx = abs(b->x - a->x);
	param->dy = -1 * abs(b->y - a->y);
	if (a->x <= b->x)
		param->sx = 1;
	else
		param->sx = -1;
	if (a->y <= b->y)
		param->sy = 1;
	else
		param->sy = -1;
	param->err = param->dx + param->dy;
	param->x0 = a->x;
	param->y0 = a->y;
}

/* Check if the current point is within image boundaries
* Check if we have reached the end point
* Increment or decrement x and y coordinates based on error parameter*/
void	draw_line(t_game *game, t_point *a, t_point *b)
{
	t_bresenham	param;

	//if map needs some transformation, place it here
	bresenham_define(&param, a, b);
	while (1)
	{
		//WIDTH and HEIGHT are the dimensions of the image, not screen,
		//unless the size is one and the same
		if (param.x0 < SCREEN_WIDTH && param.x0 > 0
			&& param.y0 < SCREEN_HEIGHT && param.y0 > 0)
			//for now draw GREEN by default
			put_pixel(&game->img, param.x0, param.y0, GREEN);
		if (param.x0 == b->x && param.y0 == b->y)
			break ;
		if (2 * param.err >= param.dy && param.x0 != b->x)
		{
			param.err += param.dy;
			param.x0 += param.sx;
		}
		if (2 * param.err <= param.dx && param.y0 != b->y)
		{
			param.err += param.dx;
			param.y0 += param.sy;
		}
	}
}
