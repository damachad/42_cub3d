/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_limits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:13 by arepsa            #+#    #+#             */
/*   Updated: 2024/03/22 16:57:13 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_limits(t_game *game)
{
	size_t i;
	size_t j;

	i = -1;
	while (++i < (size_t)game->map_rows)
	{
		j = -1;
		while (++j < (size_t)game->map_cols && game->map[i][j])
		{
			if (game->map[i][j] == '1')
			{
				if (j < game->l_left)
					game->l_left = j;
				if (j > game->l_right)
					game->l_right = j;
			}
		}
		if (ft_strchr(game->map[i], '1'))
		{
			if (i > game->l_bottom)
				game->l_bottom = i;
		}
	}
}