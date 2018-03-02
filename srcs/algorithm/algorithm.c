/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 17:17:04 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

uint64_t	get_max_ways(t_map *map)
{
	t_room		*start;
	t_room		*end;

	start = get_start_room(map);
	end = get_end_room(map);
	return (ft_min(start->size_links, end->size_links));
}

t_way		**solve_map(t_map *map)
{
	t_way	**ways;

	map->ways = get_max_ways(map);
	ways = edmonds_karp(map);
	return (ways);
}
