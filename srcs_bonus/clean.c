/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:21:32 by damachad          #+#    #+#             */
/*   Updated: 2024/03/23 18:47:48 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	{
		if (game->sprites[i].img)
			mlx_destroy_image(game->mlx, game->sprites[i].img);
		i++;
	}
	free(game->sprites);
}

/* Free all used resources */
void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	if (game->sprites)
		destroy_sprites(game);
	if (game->map)
		free_matrix(game->map);
	if (game->input->no)
		free(game->input->no);
	if (game->input->so)
		free(game->input->so);
	if (game->input->we)
		free(game->input->we);
	if (game->input->ea)
		free(game->input->ea);
	if (game->input)
		free(game->input);
	if (game->calc)
		free(game->calc);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
