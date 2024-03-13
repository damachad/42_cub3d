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

void check_texture_duplicates(t_game *game, t_dir dir)
{
	if (dir == N && game->input->no)
		error_msg(game, "Duplicate texture.\n");
	else if (dir == S && game->input->so)
		error_msg(game, "Duplicate texture.\n");
	else if (dir == W && game->input->we)
		error_msg(game, "Duplicate texture.\n");
	else if (dir == E && game->input->ea)
		error_msg(game, "Duplicate texture.\n");
}

void	parse_texture(t_game *game, char *line, t_dir dir)
{
	char	*path;
	int		i;

	i = 2;
	check_texture_duplicates(game, dir);
	while (is_space(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		error_msg(game, "Could not allocate memory for texture path.\n");
	if (dir == N)
		game->input->no = ft_strdup(path);
	else if (dir == S)
		game->input->so = ft_strdup(path);
	else if (dir == W)
		game->input->we = ft_strdup(path);
	else if (dir == E)
		game->input->ea = ft_strdup(path);
	free(path);
}