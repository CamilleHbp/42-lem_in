/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 15:06:16 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

//debug
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

	start = get_start_room(map);
	way = ft_memalloc(sizeof(t_way));
	way->room = start;
	if (breadth_first_seach(way) == ERROR)
	{
		free_way(way);
		return (ERROR);
	}
	//debug
	//print_way(way);
	ways[0] = way;
	ways[1] = 0;
	clear_way(way);
	start->full = map->ants;
	while (mv_ants(ways) == SUCCESS)
		;
	free_way(way);
	return (SUCCESS);
}
