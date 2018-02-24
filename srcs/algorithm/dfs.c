/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:43:27 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 15:04:47 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

int8_t		depth_first_seach(t_way *way, int64_t depth)
{
	size_t	i;

	if (way->room->type == END)
		return (SUCCESS);
	if (way->room->full || depth == 0)
		return (ERROR);
	i = 0;
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (ALLOC_FAIL);
	way->room->full = 1;
	while (i < way->room->size_links)
	{
		way->next->room = way->room->links[i];
		if (depth_first_seach(way->next, depth - 1) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	way->room->full = 0;
	way->next->room = 0;
	free(way->next);
	way->next = 0;
	return (ERROR);
}
