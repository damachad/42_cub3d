/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:00:40 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/17 11:00:40 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* 
** copy map row to game->map 
** and set player coordinates and direction 
*/
static void	copy_row(t_game *game, char *line, int row)
{
	int	i;

	i = 0;
	game->map[row] = safe_malloc(sizeof(char) * (game->map_cols + 1));
	game->map[row][game->map_cols] = '\0';
	while (line[i])
	{
		if (!(is_valid_char(game, line[i])))
		{
			free_partial_map(game, row);
			free_line_end_game(game, line, "Invalid character in map file.\n");
		}
		game->map[row][i] = line[i];
		if (ft_strchr("NSEW", line[i]))
		{
			set_player(game, line[i], i, row);
		}
		i++;
	}
	while (i < game->map_cols)
	{
		game->map[row][i] = ' ';
		i++;
	}
}

static void	process_line(t_game *game, char *line, int *row, int *start_map)
{
	if (is_empty_line(line))
	{
		if (*start_map)
		{
			free_partial_map(game, *row - 1);
			free_line_end_game(game, line, "Empty line in map file.\n");
		}
		return ;
	}
	if (line[0] == '1' || line[0] == ' ')
	{
		*start_map = 1;
		copy_row(game, line, *row);
		(*row)++;
		if (*row == game->map_rows)
			*start_map = 0;
	}
}

static void	fill_map(t_game *game, int *row, int *start_map)
{
	char	*line;
	char	*tmp_line;

	line = get_next_line(game->fd);
	tmp_line = NULL;
	while (line != NULL)
	{
		if (ft_strchr(line, '.') || ft_strchr(line, ','))
		{
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		tmp_line = ft_strtrim(line, "\r\n");
		free(line);
		process_line(game, tmp_line, row, start_map);
		free(tmp_line);
		line = get_next_line(game->fd);
	}
	if (game->player == 0)
		error_msg(game, "Player missing.\n");
}

/* 
** assuming maps can contain spaces, not tabs 
** and all spaces are considered par of the map
*/
static void	fill_map_init(t_game *game, char *file)
{
	int		row;
	int		start_map;

	row = 0;
	start_map = 0;
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		error_msg(game, "Could not open input file.\n");
	fill_map(game, &row, &start_map);
	close(game->fd);
}

void	parse_map(t_game *game, char *file)
{
	game->map = safe_malloc(sizeof(char *) * (game->map_rows + 1));
	game->map[game->map_rows] = NULL;
	fill_map_init(game, file);
	check_map(game);
	get_map_limits(game);
}
