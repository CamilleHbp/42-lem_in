/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 16:27:30 by cbaillat         ###   ########.fr       */
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
		// if (map->adj_matrix[start->id] & (1ULL << i))
			++start_ways;
		// if (map->adj_matrix[end->id] & (1ULL << i))
			++end_ways;
		++i;
	}
	return (ft_min(start_ways, end_ways));
}


t_way	**solve_map(t_map *map)
{
	t_way	**ways;

	map->ways = get_max_ways(map);
	// if (!(ways = ft_memalloc(sizeof(t_way*) * map->ways)))
		// return (NULL);
	// ways[0] = breadth_first_search(map, get_start_room(map));
	ways = edmonds_karp(map);
	return (ways);
}
