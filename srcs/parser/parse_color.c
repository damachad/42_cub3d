/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:46:38 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/17 10:46:38 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_color_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* place rgb input into integer array */
static void	parse_color_components(t_game *game, char *line, int *i, int *color)
{
	int	j;

	j = 0;
	while (line[*i] != '\0')
	{
		while (line[*i] != '\0' && is_space(line[*i]))
			(*i)++;
		if (!ft_isdigit(line[*i]))
			error_msg(game, "Invalid color value.\n");
		while (line[*i] != '\0' && line[*i] >= '0' && line[*i] <= '9')
		{
			color[j] = color[j] * 10 + (line[*i] - '0');
			(*i)++;
		}
		if (color[j] > 255 || color[j] < 0)
			error_msg(game, "Invalid color value.\n");
		if (line[*i] == ',')
			(*i)++;
		while (line[*i] != '\0' && is_space(line[*i]))
			(*i)++;
		j++;
		if (j == 3 && line[*i] != '\0')
			error_msg(game, "Invalid color format.\n");
	}
}

void	parse_color(t_game *game, char *line, t_color_type color_type)
{
    int	i;
    int	color[3];
	int	color_hex;

	i = 1;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	if (game->input->ceiling_color != -1 && game->input->floor_color != -1)
		error_msg(game, "Duplicate color.\n");
	while (line[i] != '\0' && is_space(line[i]))
        i++;
	parse_color_components(game, line, &i, color);
    color_hex = get_color_hex(color[0], color[1], color[2]);
    if (color_type == FLOOR)
        game->input->floor_color = color_hex;
    else if (color_type == CEILING)
        game->input->ceiling_color = color_hex;
}
