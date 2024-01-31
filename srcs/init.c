/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:40:51 by damachad          #+#    #+#             */
/*   Updated: 2024/01/31 11:18:13 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// NOTE: Functions from So_long, need to be adapted

/* Initialize 't_game' struct, load and check map,
   initialize graphics, load sprites, render map,
   and start game loop */
void	start_game(char	*mapfile)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	load_map(&game, mapfile);
	validate_map(&game);
	// init_graphics(&game);
	// load_sprites(&game);
	// render_map(&game);
	// mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	// mlx_hook(game.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	// mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}
