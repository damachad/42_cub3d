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

void	free_line_end_game(t_game *game, char *line, char *msg)
{
	if (line && line != game->line)
		free(line);
	if (game->line)
		free(game->line);
	if (game->line_tmp)
		free(game->line_tmp);
	if (game->fd > 0)
		close(game->fd);
	error_msg(game, msg);
}

/* initialize limits to extreme values */
static void	map_limit_init(t_game *game)
{
	game->l_left = game->map_cols;
	game->l_right = 0;
	game->l_top = game->map_rows;
	game->l_bottom = 0;
}

static void	set_vertical_limits(t_game *game, size_t i)
{
	if (i < game->l_top)
		game->l_top = i;
	if (i > game->l_bottom)
		game->l_bottom = i;
}

static void	set_horizontal_limits(t_game *game, size_t j)
{
	if (j < game->l_left)
		game->l_left = j;
	if (j > game->l_right)
		game->l_right = j;
}

/* get map limits that do not include spaces around */
void	get_map_limits(t_game *game)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	map_limit_init(game);
	while (++i < (size_t)game->map_rows)
	{
		if (ft_strchr(game->map[i], '1'))
		{
			set_vertical_limits(game, i);
			j = -1;
			while (++j < (size_t)game->map_cols)
			{
				if (game->map[i][j] == '1')
					set_horizontal_limits(game, j);
			}
		}
	}
}
