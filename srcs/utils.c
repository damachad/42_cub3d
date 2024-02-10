/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:57:20 by arepsa            #+#    #+#             */
/*   Updated: 2024/02/10 17:57:20 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*safe_malloc(int bytes)
{
	void	*result;
	
	result = malloc(bytes);
	if (!result)
	{
		return(NULL);
	}
	return (result);
		
}