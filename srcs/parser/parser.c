/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:06:42 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/10 17:06:42 by arepsa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int all_textures_and_colors_set(t_game *game)
{
	if (game->input->no && game->input->so && game->input->we && game->input->ea
		&& game->input->floor_color != -1 && game->input->ceiling_color != -1)
		return (1);
	return (0);
}

bool is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void parse_textures_and_colors(t_game *game, char *line, int fd)
{
	if (line[0] == 'N' && line[1] == 'O')
		parse_texture(game, line, NO);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_texture(game, line, SO);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_texture(game, line, WE);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_texture(game, line, EA);
 	else if (line[0] == 'F')
		parse_color(game, line, FLOOR);
	else if (line[0] == 'C')
		parse_color(game, line, CEILING);
	else if ((line[0] == '1' || line[0] == ' ') && (all_textures_and_colors_set(game)))
		get_map_size(game, line);
	else if (!is_empty_line(line))
	{
		free(line);
		close(fd);
		error_msg(game, "Invalid line in input file.\n");
	}
}

void	parse_file(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char 	*tmp_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open input file.\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp_line = ft_strtrim(line, "\n");
		free(line);
		parse_textures_and_colors(game, tmp_line, fd);
		free(tmp_line);
	}
	if (!all_textures_and_colors_set(game))
	{
		close(fd);
		error_msg(game, "Missing info in map file.\n");
	}
	close(fd);
	parse_map(game, file);
}
