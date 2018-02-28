/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:44:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/28 14:06:33 by cbaillat         ###   ########.fr       */
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
	// Il ne faut que Start et End soient visites.
	while (way->room->prev && way->room->type != START)
	{
		tmp = way;
		if (!(way = ft_memalloc(sizeof(t_way))))
		{
			free_way(tmp);
			return (NULL);
		}
		way->room = tmp->room->prev;
		way->room->visited = 1;
		way->next = tmp;
		tmp->prev = way;
	}
	if (prev_way)
	{
		tmp = prev_way;
		while (tmp->next)
			tmp = tmp->next;
		ft_print("prev: %s\n", tmp->room->name);
		tmp->next = way;
		way->prev = tmp;
		return (prev_way);
	}
	return (way);
}

int8_t			is_in_way(uint32_t id, t_way *way)
{
	while (way)
	{
		if (way->room->id == id)
			return (1);
		way = way->next;
	}
	return (0);
}

void			clear_parents(t_map *map, t_way *way)
{
	uint32_t	i;

	i = 0;
	while (i < map->size_rooms)
	{
		if (!is_in_way(map->rooms[i]->id, way))
			map->rooms[i]->prev = NULL;
		++i;
	}
}

static int64_t	return_shortest_path(t_deque *deque, t_map *map,
					int64_t *collision_prev)
{
	uint64_t	child_id;
	int64_t		collision;
	t_room		*room;
	t_room		*child;

	collision = ERROR;
	while (deque->head)
	{
		room = ft_deque_pop_front(deque);
		if (room->type == END)
			return (FOUND);
		else
		{
			child_id = 0;
			while (child_id < map->size_rooms)
			{
				if (map->adj_matrix[room->id] & (1ULL << child_id))
				{
					child = get_room_by_id(map, child_id);
					// if (!child->prev && child->type != START)
					if (!child->visited && child->type != START)
					{
						child->prev = room;
						ft_deque_push_back(deque, (void*)child);
					}
					// else if (child->prev && collision == ERROR)
					else if (room->type != START && child->visited && collision == ERROR)
					{
						collision = child->id;
						*collision_prev = room->id;
					}
				}
				++child_id;
			}
		}
	}
	return (collision);
}

int64_t			breadth_first_search(t_map *map, t_way **way, t_room *room)
{
	t_deque		*deque;
	int64_t	collision;
	int64_t	collision_prev;

	deque = ft_deque_create();
	if (ft_deque_push_back(deque, room) == ERROR)
	{
		ft_deque_delete(deque);
		return (ERROR);
	}
	// return shortest will either return FOUND, ERROR (negative)
	// or a positive number that will represent the room where the first
	// collision took place
	// If a collision took place but no way was found, we build the way up to
	if ((collision = return_shortest_path(deque, map, &collision_prev)) == FOUND)
		*way = build_way_from_end(*way, get_end_room(map));
	else if (collision > 0)
		*way = build_way_from_end(*way, get_room_by_id(map, collision_prev));
	clear_parents(map, *way);
	ft_deque_delete(deque);
	return (collision);
}
