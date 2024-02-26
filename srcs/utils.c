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

bool	facing_up(float angle)
{
	if (angle > 0 && angle < PI)
		return (true);
	else
		return (false);
}

bool	facing_down(float angle)
{
	if (angle > PI && angle < PI_DOUBLE)
		return (true);
	else
		return (false);
}

bool	facing_left(float angle, float buffer)
{
	if (angle > PI_HALF + buffer && angle < PI_THREE_HALFS - buffer)
		return (true);
	else
		return (false);
}

bool	facing_right(float angle, float buffer)
{
	if (angle < PI_HALF - buffer || angle > PI_THREE_HALFS + buffer)
		return (true);
	else
		return (false);
}

// Given that when malloc fails it returns NULL, is this not the same as a normal malloc?
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