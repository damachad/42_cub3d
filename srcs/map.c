/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:46:15 by damachad          #+#    #+#             */
/*   Updated: 2024/01/31 11:14:12 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// NOTE: Functions from So_long, need to be adapted

/* Allocate memory for map, with nbr of rows as nbr of
   strings in '**bytes'. Null pointer at the end in case
   free_matrix needs to be called */
t_map	*new_map(unsigned int rows)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->bytes = ft_calloc(rows + 1, sizeof(char *));
	if (!map->bytes)
	{
		free(map);
		return (NULL);
	}
	map->rows = rows;
	return (map);
}

// TODO: How to get nr_lines, how to get the map from the file that has 
// other info
/* Count nbr of lines in mapfile */
int	nr_lines(t_game *game, char *mapfile)
{
	int		fd;
	int		lines;
	char	*tmp;

	lines = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open map file.\n");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		lines++;
		free(tmp);
	}
	close(fd);
	return (lines);
}

/* Load map from file into '**bytes', removing the
   '\n' at the end of each line */
void	load_map(t_game *game, char *mapfile)
{
	int					fd;
	char				*line;
	unsigned int		i;

	i = 0;
	game->map = new_map(nr_lines(game, mapfile));
	if (!game->map)
		error_msg(game, "Could not allocate memory for map.\n");
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open map file.\n");
	while (i < game->map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg(game, "Could not read map file.\n");
		game->map->bytes[i] = ft_strtrim(line, "\n");
		if (!game->map->bytes[i++])
			error_msg(game, "Could not trim line.\n");
		free(line);
	}
	close(fd);
}
