/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:40:51 by damachad          #+#    #+#             */
/*   Updated: 2024/02/26 13:26:28 by damachad         ###   ########.fr       */
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
		error_msg(game, "Failed to create image.\n");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, \
									&img.endian);
	img.width = SCREEN_WIDTH;
	img.height = SCREEN_HEIGHT;
	return (img);
}

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

void	load_sprites(t_game *g)
{
	g->sprites = ft_calloc(4, sizeof(t_img));
	if (!g->sprites)
		error_msg(g, "Could not allocate memory for sprites.\n");
	g->sprites[N].img = mlx_xpm_file_to_image(g->mlx, \
	NO, &(g->sprites[N].width), &(g->sprites[N].height));
	g->sprites[S].img = mlx_xpm_file_to_image(g->mlx, \
	SO, &(g->sprites[S].width), &(g->sprites[S].height));
	g->sprites[E].img = mlx_xpm_file_to_image(g->mlx, \
	EA, &(g->sprites[E].width), &(g->sprites[E].height));
	g->sprites[W].img = mlx_xpm_file_to_image(g->mlx, \
	WE, &(g->sprites[W].width), &(g->sprites[W].height));
	if (!g->sprites[N].img || !g->sprites[S].img || \
	!g->sprites[E].img || !g->sprites[W].img)
		error_msg(g, "Invalid texture file.\n");
	g->sprites[N].addr = mlx_get_data_addr(g->sprites[N].img, \
	&g->sprites[N].bpp, &g->sprites[N].line_length, &g->sprites[N].endian);
	g->sprites[S].addr = mlx_get_data_addr(g->sprites[S].img, \
	&g->sprites[S].bpp, &g->sprites[S].line_length, &g->sprites[S].endian);
	g->sprites[E].addr = mlx_get_data_addr(g->sprites[E].img, \
	&g->sprites[E].bpp, &g->sprites[E].line_length, &g->sprites[E].endian);
	g->sprites[W].addr = mlx_get_data_addr(g->sprites[W].img, \
	&g->sprites[W].bpp, &g->sprites[W].line_length, &g->sprites[W].endian);
}

void	init_player(t_game *g)// later get values from mapfile
{
	g->p_angle = START_ANGLE;
	g->p_pos = (t_point){(float)3 * CUB_SIDE + CUB_SIDE/2, (float)3 * CUB_SIDE + CUB_SIDE/2};
	g->p_dir = (t_point){cos(g->p_angle) * SPEED, sin(g->p_angle) * -1 * SPEED};
	g->wall_side = -1;
	g->back_wall = -1;
	g->draw_offset_x = -1;
	g->draw_offset_y = -1;
}

/* Initialize 't_game' struct, load and check map,
   initialize graphics, load sprites,
   and start game loop */
void	start_game(char	*mapfile)
{
	t_game	game;

	(void)mapfile;
	ft_bzero(&game, sizeof(t_game));
	// load_map(&game, mapfile);
	// validate_map(&game);
	init_graphics(&game);
	init_player(&game);
	game.img = new_img(&game);
	draw_background(&game.img);
	load_sprites(&game);
	draw_wall(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, handle_keyrelease, &game);
	mlx_hook(game.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	mlx_loop_hook(game.mlx, render_movement, &game);
	mlx_loop(game.mlx);
}
