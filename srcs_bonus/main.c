/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:22:00 by damachad          #+#    #+#             */
/*   Updated: 2024/04/01 17:58:38 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/* 
** Initialize 't_game' struct, load and check map,
** initialize graphics, load sprites,
** and start game loop
*/
void	start_game(char	*file)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.input = safe_malloc(sizeof(t_input));
	game.calc = ft_calloc(1, sizeof(t_calc));
	if (!game.input || !game.calc)
		error_msg(&game, "Could not allocate memory.\n");
	init_input(game.input);
	parse_file(&game, file);
	init_player(&game);
	init_graphics(&game);
	load_sprites(&game);
	draw_background(&game);
	draw_wall(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, handle_keyrelease, &game);
	mlx_hook(game.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	mlx_loop_hook(game.mlx, render_movement, &game);
	mlx_loop(game.mlx);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_msg(NULL, "Usage: ./cub3D <mapfile.cub>\n");
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) || \
	ft_strlen(argv[1]) <= 4 || \
	!ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, "/.cub", 5))
		error_msg(NULL, "Invalid map file extension\n");
	else
		start_game(argv[1]);
	return (0);
}
