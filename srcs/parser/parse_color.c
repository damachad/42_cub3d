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

/* 
** only whitespace before first number
** mandatory comma between first and second number
** optional whitspace before and after comma
** only whitespace or eof after third number
*/
static void	validate_color_format(t_game *game, char *line, int *i, int j)
{
	while (is_space(line[*i]))
		(*i)++;
	if (j < 2 && line[*i] == ',')
	{
		(*i)++;
		while (is_space(line[*i]))
			(*i)++;
	}
	else if (j == 2)
	{
		if (line[*i] != '\0' && !is_space(line[*i]))
			free_line_end_game(game, line, "Invalid color format.\n");
	}
	else
		free_line_end_game(game, line, "Invalid color format.\n");
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
			free_line_end_game(game, line, "Invalid color value.\n");
		while (line[*i] != '\0' && line[*i] >= '0' && line[*i] <= '9')
		{
			color[j] = color[j] * 10 + (line[*i] - '0');
			(*i)++;
		}
		if (color[j] > 255 || color[j] < 0)
			free_line_end_game(game, line, "Invalid color value.\n");
		validate_color_format(game, line, i, j);
		j++;
		if (j == 3 && line[*i] != '\0')
			free_line_end_game(game, line, "Invalid color format.\n");
	}
	if (j != 3)
		free_line_end_game(game, line, "Invalid color format.\n");
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
	if (game->input->c_color != -1 && game->input->f_color != -1)
		error_msg(game, "Duplicate color.\n");
	while (line[i] != '\0' && is_space(line[i]))
		i++;
	parse_color_components(game, line, &i, color);
	color_hex = get_color_hex(color[0], color[1], color[2]);
	if (color_type == FLOOR)
		game->input->f_color = color_hex;
	else if (color_type == CEILING)
		game->input->c_color = color_hex;
}
