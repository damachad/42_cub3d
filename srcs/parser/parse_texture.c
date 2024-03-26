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

static void	set_player_direction(t_game *game, char *path, t_dir dir)
{
	if (dir == N)
		game->input->no = path;
	else if (dir == S)
		game->input->so = path;
	else if (dir == W)
		game->input->we = path;
	else if (dir == E)
		game->input->ea = path;
}

static bool	is_texture_duplicate(t_game *game, t_dir dir)
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

static void	check_file_extension(t_game *game, char *path)
{
	int		len;
	char	*filename;

	filename = ft_strrchr(path, '/');
	if (filename)
		filename++;
	else
		filename = path;
	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		free_line_end_game(game, path, "Invalid texture file.\n");
}

void	parse_texture(t_game *game, char *line, t_dir dir)
{
	char	*path;
	int		i;
	int		fd;

	i = 2;
	if (is_texture_duplicate(game, dir))
		free_line_end_game(game, line, "Duplicate texture.\n");
	if (!line[i] || !is_space(line[i]))
		free_line_end_game(game, line, "Invalid texture line.\n");
	while (line[i] && is_space(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		free_line_end_game(game, line, "Memory fail for texture path.\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_line_end_game(game, path, "Invalid texture file.\n");
	close(fd);
	check_file_extension(game, path);
	set_player_direction(game, path, dir);
}
