/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:29:40 by damachad          #+#    #+#             */
/*   Updated: 2024/02/09 14:55:09 by damachad         ###   ########.fr       */
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

// void	draw_wall_test(t_game *game)
// {
// 	t_point a;

// 	a.x = -1;
// 	a.y = SCREEN_HEIGHT/2 + 64/2;
// 	while (++(a.x) < SCREEN_WIDTH)
// 		draw_line(game, &a, &(t_point){a.x, a.y - 64});
// }
