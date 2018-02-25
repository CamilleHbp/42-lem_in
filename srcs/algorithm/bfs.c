/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:44:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 12:23:33 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

static t_way	*build_way_from_end(t_way *prev_way, t_room *end)
{
	t_way	*way;
	t_way	*tmp;

	if (!(way = ft_memalloc(sizeof(t_way))))
		return (NULL);
	way->room = end;
	while (way->room->prev)
	{
		tmp = way;
		if (!(way = ft_memalloc(sizeof(t_way))))
		{
			free_way(tmp);
			return (NULL);
		}
		way->room = tmp->room->prev;
		way->next = tmp;
		tmp->prev = way;
	}
	if (prev_way)
	{
		tmp = prev_way;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = way;
		way->prev = tmp;
		return (prev_way);
	}
	return (way);
}

int8_t			return_shortest_path(t_deque *deque, t_map *map)
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

t_way			*breadth_first_search(t_map *map, t_way *way, t_room *room)
{
	t_deque	*deque;

	deque = ft_deque_create();
	if (ft_deque_push_back(deque, room) == ERROR)
	{
		ft_deque_delete(deque);
		return (NULL);
	}
	if (return_shortest_path(deque, map) == SUCCESS)
		way = build_way_from_end(way, get_end_room(map));
	ft_deque_delete(deque);
	return (way);
}
