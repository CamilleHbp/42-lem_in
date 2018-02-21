/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 15:47:40 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int32_t	find_way_rec(t_way *way)
{
	size_t		idx;
	int			res;

	if (way->room->type == END)
		return (SUCCESS);
	if (way->room->size_links == 0)
		return (ERROR);
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (ALLOC_FAIL);
	idx = 0;
	while (idx < way->room->size_links)
	{
		way->next->room = way->room->links[idx];
		if (way->next->room->full == 0)
		{
			way->next->room->full++;
			res = find_way_rec(way->next);
			way->next->room->full--;
			if (res == SUCCESS)
				return (SUCCESS);
			if (res == ALLOC_FAIL)
				return (ALLOC_FAIL);
		}
		idx++;
	}
	free(way->next);
	way->next = 0;
	return (ERROR);
}

t_way	*find_way(const t_map *map)
{
	t_way	*way;
	int		res;

	if ((way = ft_memalloc(sizeof(t_way))) == 0)
		return (0);
	way->room = get_start_room(map);
	if (way->room == 0)
	{
		// TODO: recursive delete for t_way
		free(way);
		return (0);
	}
	way->room->full++;
	res = find_way_rec(way);
	way->room->full--;
	if (res == ERROR || res == ALLOC_FAIL)
	{
		free(way);
		return (0);
	}
	return (way);
}

int8_t	solve_map(t_map *map)
{
	t_way	*way;
	
	// TODO: this is a temp test
	way = find_way(map);
	if (way == 0 || way->room == 0)
		return (SUCCESS);
	printf("%lld %lld", way->room->x, way->room->y);
	way = way->next;
	while (way)
	{
		printf(" -> %lld %lld", way->room->x, way->room->y);
		way = way->next;
	}
	//save_way(way_array, way);
	return (SUCCESS);
}
