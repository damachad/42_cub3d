/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:11:38 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 09:11:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float fmodule(float i) {
    if (i < 0)
        return -i;
    else
        return i;
}

void	drawl_line_dda(t_point a, t_point b, t_game *game)
{
	float	step_x;
	float	step_y;
	float	max;

	//if map needs some transformation, place it here
	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = MAX(fmodule(step_x), fmodule(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		put_pixel(&game->img, a.x, a.y, RED);
		a.x += step_x;
		a.y += step_y;
		if (a.x > SCREEN_WIDTH || a.y > SCREEN_HEIGHT || a.y < 0 || a.x < 0)
			break ;
	}
}