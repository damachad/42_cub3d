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

#include "../includes/cub3d.h"



void	parse_texture(t_game *game, char *line, t_dir dir)
{
	char	*path;
	int		i;

	i = 2;
	while (is_space(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		error_msg(game, "Could not allocate memory for texture path.\n");
	if (dir == NO)
		game->input->no = path;
	else if (dir == SO)
		game->input->so = path;
	else if (dir == WE)
		game->input->we = path;
	else if (dir == EA)
		game->input->ea = path;
}

void parse_line(t_game *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		parse_texture(game, line, NO);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_texture(game, line, SO);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_texture(game, line, WE);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_texture(game, line, EA);
/* 	else if (line[0] == 'F')
		parse_color(game, line, FLOOR);
	else if (line[0] == 'C')
		parse_color(game, line, CEILING);
	else if (line[0] == '1' || line[0] == '\0' || is_space(line[0]))
		parse_map(game, line); */
	else if (line[0] != '\0' || !is_space(line[0]))
		error_msg(game, "Invalid line in map file.\n");
}

void	parse_file(t_game *game, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open input file.\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(game, line);
		free(line);
	}
	close(fd);
}