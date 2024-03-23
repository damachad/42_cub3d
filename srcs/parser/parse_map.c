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

void free_partial_map(t_game *game, int rows_allocated) {
    if (game->map) {
        while (rows_allocated >= 0) {
            if (game->map[rows_allocated]) {
                free(game->map[rows_allocated]);
                game->map[rows_allocated] = NULL;
            }
            rows_allocated--;
        }
        free(game->map);
        game->map = NULL;
    } 
}

void    set_player(t_game *game, char c, int x, int y)
{
    game->p_pos = (t_point){(float)x * CUB_SIDE + CUB_SIDE/2, (float)y * CUB_SIDE + CUB_SIDE/2};
    if (c == 'N')
        game->p_angle = PI_HALF;
    else if (c == 'S')
        game->p_angle = PI_THREE_HALFS;
    else if (c == 'E')
        game->p_angle = 0;
    else if (c == 'W')
        game->p_angle = PI;
    else
        error_msg(game, "Invalid player character in map file.\n");
}

void	get_map_size(t_game *game, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > game->map_cols)
		game->map_cols = line_len;
	game->map_rows++;
}

/* check for valid map chars and duplicate players */
bool    is_valid_char(t_game *game, char c)
{
    if (ft_strchr("01NSEW ", c))
    {
        if (ft_isalpha(c))
        {
            if (game->player == 1)
                return (false); 
            game->player = 1;
        }
        return (true);
    }
    return (false);
}

/* 
** copy map row to game->map 
** and set player coordinates and direction 
*/
void copy_row(t_game *game, char *line, int row)
{
    int i;

    i = 0;
    game->map[row] = safe_malloc(sizeof(char) * (game->map_cols + 1));
    game->map[row][game->map_cols] = '\0';
    while (line[i])
    {
       if (!(is_valid_char(game, line[i])))
        {
            free_partial_map(game, row); 
            free(line);
            error_msg(game, "Invalid character in map file.\n");
        }
        game->map[row][i] = line[i];
        if (ft_strchr("NSEW", line[i]))
        {
            set_player(game, line[i], i, row);
        }
        i++;
    }
    while (i < game->map_cols)
    {
        game->map[row][i] = ' ';
        i++;
    }
}

void process_line (t_game *game, char *line, int *row, int *start_map)
{
    if (is_empty_line(line))
    {
        if (*start_map)
        {
            free_partial_map(game, *row - 1);
            free(line);
            error_msg(game, "Empty line in map file.\n");
        }
        return;
    }
    if (line[0] == '1' || (line[0] == ' ' && ft_strchr(line, '1')))
    {
        *start_map = 1;
        copy_row(game, line, *row);
        (*row)++;
        if (*row == game->map_rows)
            *start_map = 0;
    }
}

/* 
** assuming maps can contain spaces, not tabs 
** and all spaces are considered par of the map
*/
void fill_map(t_game *game, char *file)
{
    int fd;
    int row;
    char *line;
    char *tmp_line;
    int start_map;

    row = 0;
    start_map = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        error_msg(game, "Could not open input file.\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        if (ft_strchr(line, '.') || ft_strchr(line, ','))
        {
            free(line);
            continue ;
        }
        tmp_line = ft_strtrim(line, "\r\n");
        free(line);
        process_line(game, tmp_line, &row, &start_map);
        free(tmp_line);
    }
    if (game->player == 0)
        error_msg(game, "Player missing.\n");
    close(fd);
}

void parse_map(t_game *game, char *file)
{
    game->map = safe_malloc(sizeof(char *) * (game->map_rows + 1)); 
    game->map[game->map_rows] = NULL;
    fill_map(game, file);
    check_map(game);
   
}
