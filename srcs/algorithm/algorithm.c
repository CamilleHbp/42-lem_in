/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/01 15:39:38 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

uint64_t	get_max_ways(t_map *map)
{
	t_room		*start;
	t_room		*end;
	uint32_t	start_ways;
	uint32_t	end_ways;
	uint32_t	i;

	start = get_start_room(map);
	end = get_end_room(map);
	start_ways = 0;
	end_ways = 0;
	i = 0;
	while (i < map->size_rooms)
	{
		if (map->adj_matrix[start->id] & 1ULL << i)
			++start_ways;
		if (map->adj_matrix[end->id] & 1ULL << i)
			++end_ways;
		++i;
	}
	return (ft_min(start_ways, end_ways));
}


int8_t	solve_map(t_map *map)
{
	t_room	*start;
	t_way	**ways;
	int64_t	i;

	ways = NULL;
	map->ways = get_max_ways(map);
	ways = edmonds_karp(map);
	start = get_start_room(map);
	mv_ants(ways, (uint32_t)map->ants);
	if (ways)
	{
		i = 0;
		while (ways[i])
			free_way(ways[i++]);
		free (ways);
	}
	return (SUCCESS);
}
