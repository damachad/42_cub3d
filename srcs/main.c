/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:22:00 by damachad          #+#    #+#             */
/*   Updated: 2024/03/18 18:34:46 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_msg(NULL, "Usage: ./cub3D <mapfile.cub>\n");
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) || \
	ft_strlen(argv[1]) <= 4)
		error_msg(NULL, "Invalid map file extension\n");
	else
		start_game(argv[1]);
	return (0);
}
