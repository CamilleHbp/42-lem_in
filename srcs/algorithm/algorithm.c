/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 13:25:14 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int		find_way_rec(t_way *way)
{
	size_t		idx;
	int			res;

	if (way->room->type == END)
		return (1);
	if (way->room->size_links == 0)
		return (0);
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (0);
	idx = 0;
	while (idx < way->room->size_links)
	{
		way->next->room = way->room->links[idx];
		if (way->next->room->full == 0)
		{
			way->next->room->full++;
			res = find_way_rec(way->next);
			way->next->room->full--;
			if (res == 1)
				return (1);
		}
		idx++;
	}
	return (0);
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
		free(way);
		return (0);
	}
	way->room->full++;
	res = find_way_rec(way);
	way->room->full--;
	if (res == 0)
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
