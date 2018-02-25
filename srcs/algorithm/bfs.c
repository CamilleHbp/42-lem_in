/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:44:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 10:38:59 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

// uint64_t	return_first_collision_id(t_deque *deque, t_map *map, t_way *way)
// {
	// ;
// }

int8_t	return_shortest_path(t_deque *deque, t_map *map)
{
	uint64_t	neighbour_id;
	t_room		*room;
	t_room		*neighbour;

	while (deque->head)
	{
		room = ft_deque_pop_front(deque);
		if (room->type == END)
			return (SUCCESS); //we found the room
		else
		{
			// find a way to get the id of neighbours
			neighbour_id = 0;
			while (neighbour_id < map->size_rooms)
			{
				if (map->adj_matrix[room->id] & (1ULL << neighbour_id))
				{
					neighbour = get_room_by_id(map, neighbour_id);
					if (!neighbour->prev && neighbour->type != START)
					{
						neighbour->prev = room;
						ft_deque_push_back(deque, (void*)neighbour);
					}
				}
				++neighbour_id;
			}
		}
	}
	return (ERROR);
}

/*
** We will probably need to implement BFS in a way that can return error if it
** reaches the end of the map.
** I am afraid that in this implementation, we will loop infinitely
*/

int8_t		breadth_first_search(t_map *map, t_way *way)
{
	t_deque	*deque;

	deque = ft_deque_create();
	if (ft_deque_push_back(deque, (void*)get_start_room(map)) == ERROR)
		return (error_bfs(deque));
	if (return_shortest_path(deque, map) == SUCCESS)
		print_reverse_way(get_end_room(map)); //go back from end to start with prev pointers and build the way
	ft_deque_delete(deque);
	return (ERROR);
}
