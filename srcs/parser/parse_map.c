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

/* void	parse_map(t_game *game, char *line, int row)
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
} */

void	get_map_size(t_game *game, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > game->map_cols)
		game->map_cols = line_len;
	game->map_rows++;
}

/* check for valid map chars and duplicate players */
bool    is_valid_char(char c, int *player)
{
    if (ft_strchr("01NSEW ", c))
    {
        if (ft_isalpha(c))
        {
            if (*player == 1)
                return (false); 
            *player = 1;
        }
        return (true);
    }
    return (false);
}

void copy_row(t_game *game, char *line, int row, int *player)
{
    int i;

    i = 0;
    game->map[row] = safe_malloc(sizeof(char) * (game->map_cols + 1));
    game->map[row][game->map_cols] = '\0';
    while (line[i])
    {
       if (!(is_valid_char(line[i], player)))
        {
            free(line);
            error_msg(game, "Invalid character in map file.\n");
        }
        game->map[row][i] = line[i];
        i++;
    }
}

/* 
** assuming spaces before characters are only in map lines 
** assuming maps can contain spaces, not tabs 
*/
void fill_map(t_game *game, char *file)
{
    int fd;
    int row;
    int player;
    int start_map;
    char *line;
    char *tmp_line;

    row = 0;
    player = 0;
    start_map = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error_msg(game, "Could not open input file.\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        tmp_line = ft_strtrim(line, "\r\n");
        free(line);
        if (is_empty_line(tmp_line) && !start_map)
        {
            free(tmp_line);
            continue;
        }
        if (is_empty_line(tmp_line) && start_map)
        {
            free(tmp_line);
            error_msg(game, "Invalid line in map file.\n");
        }
        if (tmp_line[0] == '1' || is_space(tmp_line[0]))
        {
            start_map = 1;
            copy_row(game, tmp_line, row, &player);
            row++;
            if (row == game->map_rows)
                start_map = 0;
        }
        free(tmp_line);
    }
    close(fd);
}

void parse_map(t_game *game, char *file)
{
    game->map = safe_malloc(sizeof(char *) * (game->map_rows + 1)); 
    game->map[game->map_rows] = NULL;
    fill_map(game, file);
}
