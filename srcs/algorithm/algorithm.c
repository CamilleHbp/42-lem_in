/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/23 11:19:54 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int8_t		find_way_depth(t_way *way, int64_t depth)
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
		if (find_way_depth(way->next, depth - 1) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	way->room->full = 0;
	way->next->room = 0;
	free(way->next);
	way->next = 0;
	return (ERROR);
}

// NOTE: name is weird
void	unfull_way(t_way *way)
{
	if (!way || !way->room)
		return ;
	way->room->full = 0;
	unfull_way(way->next);
}

// debug ?
void	print_way(t_way *way)
{
	if (!way)
		return ;
	ft_print("%d %d", way->room->x, way->room->y);
	way = way->next;
	while (way)
	{
		ft_print(" -> %d %d", way->room->x, way->room->y);
		way = way->next;
	}
	ft_print("\n");
}



int8_t	solve_map(t_map *map)
{
	t_room	*start;
	t_way	*way;
	t_way	*ways[2];
	int64_t	depth;

	start = get_start_room(map);
	way = ft_memalloc(sizeof(t_way));
	way->room = start;
	depth = 1;
	while (find_way_depth(way, depth) != SUCCESS)
		depth++;
	//debug
	//print_way(way);
	ways[0] = way;
	ways[1] = 0;
	unfull_way(way);
	start->full = map->ants;
	while (mv_ants(ways) == SUCCESS)
		;
	free_way(way);
	return (SUCCESS);
}
