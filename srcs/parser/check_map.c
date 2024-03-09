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

static bool is_boundary(int check, int row, int col, t_game *game)
{
	if (check == '1')
	{
		if (row < 0 || row > (game->map_rows - 1)
			|| col < 0 || col > (game->map_cols - 1))
			return (false);
		return (true);
	}
	if (check == '0')
	{
		if ((row == 0) || (col == 0)
			|| (row == (game->map_rows - 1))
			|| (col == (game->map_cols - 1)))
			return (true);
		return (false);
	}
	return (false);
}

static void	check_neighbors(char **map, int row, int col, t_game *game)
{
	int		col_offset;
	int		row_offset;
	
	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (is_boundary('1', (row + row_offset),
					(col + col_offset), game))
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
			if (is_boundary('0', row, col, game))
				check_edges_content(game, map[row][col]);
			if (map[row][col] == ' ')
				check_neighbors(map, row, col, game);
		}
	}
}