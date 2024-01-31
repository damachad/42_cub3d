/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:25:51 by damachad          #+#    #+#             */
/*   Updated: 2024/01/31 10:29:56 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Frees allocated space for a char matrix */
void	free_matrix(char **bytes)
{
	unsigned int	i;

	i = 0;
	if (!bytes)
		return ;
	while (bytes[i])
		free(bytes[i++]);
	free(bytes);
}
