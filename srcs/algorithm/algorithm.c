/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 12:24:46 by cbaillat         ###   ########.fr       */
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

	if (!(way = breadth_first_search(map, NULL, get_start_room(map))))
		return (ERROR);
	//debug
	print_way(way);
	clear_way(way);
	start = get_start_room(map);
	start->visited = map->ants;
	// while (mv_ants(ways) == SUCCESS)
		// ;
	free_way(way);
	return (SUCCESS);
}
