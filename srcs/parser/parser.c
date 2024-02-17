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

void parse_textures_and_colors(t_game *game, char *line)
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
	else if (line[0] != '\0' && !is_space(line[0]))
		error_msg(game, "Invalid line in map file.\n");
}

void	read_textures_and_colors(t_game *game, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open input file.\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		line = ft_strtrim(line, "\n");
		if (all_textures_and_colors_set(game))
			break;
		parse_textures_and_colors(game, line);
		free(line);
	}
	close(fd);
	if (!all_textures_and_colors_set(game))
		error_msg(game, "Missing info in map file.\n");
}

void parse_file(t_game *game, char *file) {
   read_textures_and_colors(game, file);
   //read_map(game, file);
}