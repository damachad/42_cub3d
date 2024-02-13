/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:20:34 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/13 09:20:34 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_input(t_input *input) 
{
    printf("Input structure:\n");
    printf("NO: %s\n", input->no ? input->no : "NULL");
    printf("SO: %s\n", input->so ? input->so : "NULL");
    printf("WE: %s\n", input->we ? input->we : "NULL");
    printf("EA: %s\n", input->ea ? input->ea : "NULL");
    printf("Floor: [%x]\n", input->floor_color);
    printf("Ceiling: [%x]\n", input->ceiling_color);
}