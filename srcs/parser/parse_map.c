/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:00:40 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/17 11:00:40 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_map(t_game *game, char *line, int row)
{
    int col;
    int i;

    col = 0;
    i = 0;
    if (game->map == NULL)
    {
        game->map = safe_malloc(sizeof(char *));
    }
    else
    {
        // Allocate memory for the new row
        char **temp = safe_malloc((row + 1) * sizeof(char *));
        // Copy existing rows to the new memory location
        while (i < row) {
            temp[i] = game->map[i];
            i++;
        }
        // Free the old memory
        free(game->map);
        // Assign the new memory to game->map
        game->map = temp;
    }
    game->map[row] = ft_strdup(line);
    if (row == 0)
        game->map_cols = ft_strlen(line);
    // Check if the current row has more columns than previous rows
    col = ft_strlen(line);
    if (col > game->map_cols)
        game->map_cols = col;
}
