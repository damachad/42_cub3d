/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:29:40 by damachad          #+#    #+#             */
/*   Updated: 2024/02/16 11:58:45 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_img *img)
{
	int x;
	int y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT/2)
			put_pixel(img, x, y, BLUE_LIGHT);
		while (++y < SCREEN_HEIGHT)
			put_pixel(img, x, y, GREEN_ALT);
	}
}


