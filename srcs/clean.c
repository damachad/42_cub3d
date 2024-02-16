/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:32 by damachad          #+#    #+#             */
/*   Updated: 2024/02/16 20:39:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// NOTE: Functions from So_long, need to be adapted

/* Calls cleaning function, displays message in fd 2 and exits */
void	error_msg(t_game *game, char *msg)
{
	destroy_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

/* Calls function to free resources and exits program
   Called when game is over */
int	quit_prog(t_game *game)
{
	destroy_game(game);
	exit(EXIT_SUCCESS);
}

/* Destroy *img of every sprite and free *sprites */
void	destroy_sprites(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < NB_SPRITES)
		mlx_destroy_image(game->mlx, game->sprites[i++].img);
	free(game->sprites);
}

void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	free_matrix(map->bytes);
	free(map);
}

/* Free all used resources */
void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	if (game->sprites)
		destroy_sprites(game);
	if (game->map)
		destroy_map(game->map);
	// if (game->img.img)
	// 	mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
