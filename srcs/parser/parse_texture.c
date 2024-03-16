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

void	check_file_extension(t_game *game, char *path)
{
	int		len;
	char	*ext;

	len = ft_strlen(path);
	ext = path + len - 4;
	if (ft_strncmp(ext, ".xpm", 4) != 0)
	{
		free(path);
		error_msg(game, "Invalid texture file extension.\n");
	}
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
	check_file_extension(game, path);
	if (!path)
	{
		free(line);
		error_msg(game, "Could not allocate memory for texture path.\n");
	}
	if (dir == N)
		game->input->no = path;
	else if (dir == S)
		game->input->so = path;
	else if (dir == W)
		game->input->we = path;
	else if (dir == E)
		game->input->ea = path;
}