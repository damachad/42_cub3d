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

static int	all_textures_and_colors_set(t_game *game)
{
	if (game->input->no && game->input->so && game->input->we && game->input->ea
		&& game->input->f_color != -1 && game->input->c_color != -1)
		return (1);
	return (0);
}

/* consider empty only if has newline or return carriage */
bool	is_empty_line(char *line)
{
	while (*line != '\0')
	{
		if (*line != '\n' && *line != '\r')
			return (false);
		line++;
	}
	return (true);
}

static void	parse_textures_and_colors(t_game *game, char *trim_line)
{
	if (trim_line && trim_line[0] == 'N' && trim_line[1] == 'O')
		parse_texture(game, trim_line, N);
	else if (trim_line && trim_line[0] == 'S' && trim_line[1] == 'O')
		parse_texture(game, trim_line, S);
	else if (trim_line && trim_line[0] == 'W' && trim_line[1] == 'E')
		parse_texture(game, trim_line, W);
	else if (trim_line && trim_line[0] == 'E' && trim_line[1] == 'A')
		parse_texture(game, trim_line, E);
	else if (trim_line && trim_line[0] == 'F' && game->input->f_color == -1)
		parse_color(game, trim_line, FLOOR);
	else if (trim_line && trim_line[0] == 'C' && game->input->c_color == -1)
		parse_color(game, trim_line, CEILING);
	else if (trim_line && trim_line[0] == 'F' && game->input->f_color != -1)
		free_line_end_game(game, trim_line, "Duplicate color.\n");
	else if (trim_line && trim_line[0] == 'C' && game->input->c_color != -1)
		free_line_end_game(game, trim_line, "Duplicate color.\n");
	else if (trim_line)
		free_line_end_game(game, trim_line, "Invalid input line.\n");
}

static void	route_lines(t_game *game, char *line)
{
	game->line = NULL;
	if (ft_strchr(line, '.') || ft_strchr(line, ','))
		game->line = ft_strtrim(line, " \t\r");
	game->line_tmp = line;
	parse_textures_and_colors(game, game->line);
	game->line_tmp = NULL;
	if (game->line)
		free(game->line);
	else if ((line[0] == '1' || line[0] == ' ') && \
			(all_textures_and_colors_set(game)))
		get_map_size(game, line);
	else if (!is_empty_line(line))
	{
		free(line);
		close(game->fd);
		error_msg(game, "Invalid line in input file.\n");
	}
	free(line);
}

void	parse_file(t_game *game, char *file)
{
	char	*line;
	char	*tmp_line;

	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		error_msg(game, "Could not open input file.\n");
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		tmp_line = ft_strtrim(line, "\r\n");
		free(line);
		route_lines(game, tmp_line);
		line = get_next_line(game->fd);
	}
	if (!all_textures_and_colors_set(game))
	{
		close(game->fd);
		error_msg(game, "Missing info in map file.\n");
	}
	close(game->fd);
	parse_map(game, file);
}
