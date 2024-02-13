/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:29:40 by damachad          #+#    #+#             */
/*   Updated: 2024/02/13 11:47:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_game *game)
{
	int x;
	int y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT/2)
			put_pixel(&game->img, x, y, game->input->ceiling_color);
		while (++y < SCREEN_HEIGHT)
			put_pixel(&game->img, x, y, game->input->floor_color);
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
