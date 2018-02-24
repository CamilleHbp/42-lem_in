/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:44:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 15:04:47 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

/*
** We will probably need to implement BFS in a way that can return error if it
** reaches the end of the map.
** I am afraid that in this implementation, we will loop infinitely
*/

int8_t		breadth_first_seach(t_way *way)
{
	int8_t	status;
	int64_t	depth;

	depth = 1;
	status = ERROR;
	while (42)
	{
		if ((status = depth_first_seach(way, depth)) == SUCCESS)
			return (SUCCESS);
		++depth;
	}
	return (ERROR);
}
