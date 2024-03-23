/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:39:19 by arepsa            #+#    #+#             */
/*   Updated: 2024/03/07 20:39:19 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_edges_content(t_game *game, char cell)
{
	if ((cell == ' ') || (cell == '1'))
		return ;
	else
		error_msg(game, "Invalid map.\n");
}

/* check if coordinate is on the perimeter of the map */
static bool	is_edge(int row, int col, t_game *game)
{
	if ((row == 0) || (col == 0)
		|| (row == (game->map_rows - 1))
		|| (col == (game->map_cols - 1)))
		return (true);
	return (false);
}

/* check if coordinates are within map boundaries */
static bool	is_valid_point(int row, int col, t_game *game)
{
	if (row < 0 || row > (game->map_rows - 1)
		|| col < 0 || col > (game->map_cols - 1))
		return (false);
	return (true);
}

/* 
** check is spaces ouside the map have
** only spaces or '1' around in 3x3 grid
** ensures that all map parts are surrounded by walls
*/
static void	check_neighbours(char **map, int row, int col, t_game *game)
{
	int		col_offset;
	int		row_offset;

	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (is_valid_point((row + row_offset), (col + col_offset), game))
			{
				if (!(map[row + row_offset][col + col_offset] == ' ')
				&& !(map[row + row_offset][col + col_offset] == '1'))
					error_msg(game, "Invalid map.\n");
			}
			col_offset++;
		}
		row_offset++;
	}
}

void	check_map(t_game *game)
{
	char	**map;
	int		row;
	int		col;

	row = -1;
	map = game->map;
	while (map[++row])
	{
		col = -1;
		while (map[row][++col])
		{
			if (is_edge(row, col, game))
				check_edges_content(game, map[row][col]);
			if (map[row][col] == ' ')
				check_neighbours(map, row, col, game);
		}
	}
}
