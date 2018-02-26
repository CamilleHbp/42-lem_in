/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/26 16:45:49 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

//debug
void	print_way(t_way *way)
{
	if (!way)
		return ;
	ft_print("%s -> ", way->room->name);
	way = way->next;
	while (way && way->room->type != END)
	{
		ft_print("%s -> ", way->room->name);
		way = way->next;
	}
	ft_print("%s\n", way->room->name);
}

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
	// t_room	*start;
	t_way	***ways;
	int64_t i;
	int64_t j;

	ways = NULL;
	map->ways = get_max_ways(map);
	// if (breadth_first_search(map, &way, get_start_room(map)) != FOUND)
		// return (ERROR);
	if ((ways = find_da_wae(map)) == NULL)
		return (ERROR);
	//debug
	i = 0;
	j = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j])
		{
			print_way(ways[i][j]);
			clear_way(ways[i][j]);
			free_way(ways[i][j]);
			++j;
		}
		++i;
	}
	// start = get_start_room(map);
	// start->visited = map->ants;
	// while (mv_ants(ways) == SUCCESS)
		// ;
	return (SUCCESS);
}
