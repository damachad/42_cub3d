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

bool is_texture_duplicate(t_game *game, t_dir dir)
{
	if (dir == N && game->input->no)
		return (true);
	else if (dir == S && game->input->so)
		return (true);
	else if (dir == W && game->input->we)
		return (true);
	else if (dir == E && game->input->ea)
		return (true);
	return (false);
}

void	parse_texture(t_game *game, char *line, t_dir dir)
{
	char	*path;
	int		i;

	i = 2;
	if (is_texture_duplicate(game, dir))
	{
		free(line);
		error_msg(game, "Duplicate texture.\n");
	}
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