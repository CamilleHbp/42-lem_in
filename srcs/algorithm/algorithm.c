/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 13:43:34 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int64_t	find_way(t_way *way)
{
	size_t		idx;

	if (way->room->full)
		return (ERROR);
	if (way->room->type == END)
		return (SUCCESS);
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (ALLOC_FAIL);
	idx = 0;
	way->room->full = 1;
	while (idx < way->room->size_links)
	{
		way->next->room = way->room->links[idx];
		if (find_way(way->next) == SUCCESS)
			return (SUCCESS);
		idx++;
	}
	way->room->full = 0;
	return (ERROR);
}





int8_t	solve_map(t_map *map)
{
	size_t	idx;
	t_way	**ways;
	t_way	*way;
	t_way	*tmp;

	// TODO: this is a temp test
	idx = 0;
	ways = find_ways(map);
	while (ways[idx])
	{
		way = ways[idx];
		tmp = way;
		printf("%lld %lld", way->room->x, way->room->y);
		way = way->next;
		while (way)
		{
			printf(" -> %lld %lld", way->room->x, way->room->y);
			way = way->next;
		}
		printf("\nlen=%zu\n", way_len(tmp));
		free_way(tmp);
		idx++;
	}
	free(ways);
	//save_way(way_array, way);
	return (SUCCESS);
}
