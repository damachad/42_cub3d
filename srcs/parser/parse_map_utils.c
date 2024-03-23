/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:32:01 by arepsa            #+#    #+#             */
/*   Updated: 2024/03/23 15:32:05 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_partial_map(t_game *game, int rows_allocated)
{
	if (game->map)
	{
		while (rows_allocated >= 0)
		{
			if (game->map[rows_allocated])
			{
				free(game->map[rows_allocated]);
				game->map[rows_allocated] = NULL;
			}
			rows_allocated--;
		}
		free(game->map);
		game->map = NULL;
	}
}

/* check for valid map chars and duplicate players */
bool	is_valid_char(t_game *game, char c)
{
	if (ft_strchr("01NSEW ", c))
	{
		if (ft_isalpha(c))
		{
			if (game->player == 1)
				return (false);
			game->player = 1;
		}
		return (true);
	}
	return (false);
}

void	set_player(t_game *game, char c, int x, int y)
{
	game->p_pos = (t_point){(float)x * CUB_SIDE + CUB_SIDE / 2, \
				(float)y * CUB_SIDE + CUB_SIDE / 2};
	if (c == 'N')
		game->p_angle = PI_HALF;
	else if (c == 'S')
		game->p_angle = PI_THREE_HALFS;
	else if (c == 'E')
		game->p_angle = 0;
	else if (c == 'W')
		game->p_angle = PI;
	else
		error_msg(game, "Invalid player character in map file.\n");
}

void	get_map_size(t_game *game, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > game->map_cols)
		game->map_cols = line_len;
	game->map_rows++;
}

void	*safe_malloc(int bytes)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
	{
		return (NULL);
	}
	return (result);
}
