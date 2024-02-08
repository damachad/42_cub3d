/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:40:51 by damachad          #+#    #+#             */
/*   Updated: 2024/02/08 10:46:33 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//assuming that image size is the same as the window size
// where does line_length come from? probably same place as endian...
t_img	new_img(t_game *game)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (img.img == NULL)
		error_msg(game, "Failed to create image.");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, \
									&img.endian);
	img.width = SCREEN_WIDTH;
	img.height = SCREEN_HEIGHT;
	return (img);
}

// NOTE: Functions from So_long, need to be adapted

/* Initialize graphics using mlx_init() and mlx_new_window() */
void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_msg(game, "mlx_init() failed\n");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		error_msg(game, "mlx_new_window() failed\n");
}

void	load_sprites(t_game *game)
{
	game->sprites = ft_calloc(4, sizeof(t_sprite));
	if (!game->sprites)
		error_msg(game, "Could not allocate memory for sprites.\n");
	game->sprites[0].img = mlx_xpm_file_to_image(game->mlx, \
	NO, &(game->sprites[0].width), &(game->sprites[0].height));
	game->sprites[1].img = mlx_xpm_file_to_image(game->mlx, \
	SO, &(game->sprites[1].width), &(game->sprites[1].height));
	game->sprites[2].img = mlx_xpm_file_to_image(game->mlx, \
	EA, &(game->sprites[2].width), &(game->sprites[2].height));
	game->sprites[3].img = mlx_xpm_file_to_image(game->mlx, \
	WE, &(game->sprites[3].width), &(game->sprites[3].height));
}

/* Initialize 't_game' struct, load and check map,
   initialize graphics, load sprites, render map,
   and start game loop */
void	start_game(char	*mapfile)
{
	t_game	game;

	(void)mapfile;
	ft_bzero(&game, sizeof(t_game));
	// load_map(&game, mapfile);
	// validate_map(&game);
	init_graphics(&game);
	game.img = new_img(&game);
	draw_background(&game.img);
	draw_wall(&game);
	//load_sprites(&game);
	// render_map(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	// mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	// mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}
