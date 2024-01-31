/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:53:47 by damachad          #+#    #+#             */
/*   Updated: 2024/01/31 11:14:43 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// NOTE: Functions from So_long, need to be adapted

// TODO: Function to check if map is bordered
/* Check if map is bordered with '1' */
// bool	is_bordered(t_map *map)
// {
// 	return (true);
// }

// TODO: Function to check if components are only "1,0, ,N,S,E,W", decide
// how to treat spaces (remove them or treat as 0?)

/* Check if map is valid */
void	validate_map(t_game *game)
{
	if (game->map->rows == 0)
		error_msg(game, "Map is empty.\n");
	// if (!is_bordered(game->map))
	// 	error_msg(game, "Map is not completely surrounded by walls.\n");
	// if (!load_components(game))
	// 	error_msg(game, "Map has invalid number of components.\n");
}
