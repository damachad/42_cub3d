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

int get_color_hex(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

void parse_color_components(char *line, int *i, int *color)
{
	int j;

	j = 0;
	while (j < 3) 
	{
		while (line[*i] != '\0' && is_space(line[*i])) {
			(*i)++;
		}
		while (line[*i] != '\0' && line[*i] >= '0' && line[*i] <= '9') {
			color[j] = color[j] * 10 + (line[*i] - '0');
			(*i)++;
		}
		while (line[*i] != '\0' && (is_space(line[*i]) || line[*i] == ',')) {
			(*i)++;
		}
		j++;
	}
} 

void parse_color(t_game *game, char *line, t_color_type color_type)
{
    int i;
    int color[3];
	int color_hex;

	i = 1;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	while (line[i] != '\0' && (line[i] == ',' || is_space(line[i]))) {
        i++;
    }
	parse_color_components(line, &i, color);

    color_hex = get_color_hex(color[0], color[1], color[2]);

    if (color_type == FLOOR) {
        game->input->floor_color = color_hex;
    } else if (color_type == CEILING) {
        game->input->ceiling_color = color_hex;
    }
}

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
 	else if (line[0] == 'F')
		parse_color(game, line, FLOOR);
	else if (line[0] == 'C')
		parse_color(game, line, CEILING);
	/* else if (line[0] == '1' || line[0] == '\0' || is_space(line[0]))
		parse_map(game, line); */
	else if (line[0] != '\0' && !is_space(line[0]))
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