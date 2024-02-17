/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:49:10 by marvin            #+#    #+#             */
/*   Updated: 2024/02/17 10:49:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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