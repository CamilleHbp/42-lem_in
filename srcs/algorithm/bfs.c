/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:44:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 14:39:59 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

static t_way	*build_way_from_end(t_room *end)
{
	t_way	*way;
	t_way	*tmp;

	if (!(way = ft_memalloc(sizeof(t_way))))
		return (NULL);
	way->room = end;
	while (way->room->prev && way->room->type != START)
	{
		tmp = way;
		ft_print("room name: %s\n", tmp->room->name);
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
	return (way);
}

static int64_t	return_shortest_path(t_deque *deque, t_map *map)
{
	uint64_t	child_id;
	t_room		*parent;
	t_room		*child;

	while (deque->head)
	{
		parent = ft_deque_pop_front(deque);
			ft_print("Parent is %s\n", parent->name);
		if (parent->type == END)
		{
			ft_print("FOUND\n");
			return (FOUND);
		}
		else
		{
			child_id = 0;
			while (child_id < map->size_rooms)
			{
				if (map->adj_matrix[parent->id] & (1ULL << child_id))
				{
					child = get_room_by_id(map, child_id);
					// if (!child->prev && child->type != START)
					// if (!child->visited && child->type != START)
					if (!child->visited)
					{
						ft_print("Child id #%d is %s\n", child->id, child->name);
				sleep(1);
						child->prev = parent;
						ft_deque_push_back(deque, (void*)child);
					}
				}
				++child_id;
			}
		}
	}
	return (ERROR);
}

t_way	*breadth_first_search(t_map *map, t_room *parent)
{
	t_deque		*deque;
	t_way		*way;

	way = NULL;
	deque = ft_deque_create();
	if (ft_deque_push_back(deque, parent) == ERROR)
	{
		ft_deque_delete(deque);
		return (NULL);
	}
	// return shortest will either return FOUND, ERROR (negative)
	// or a positive number that will represent the parent where the first
	// collision took place
	// If a collision took place but no way was found, we build the way up to
	if ((return_shortest_path(deque, map)) == FOUND)
		way = build_way_from_end(get_end_room(map));
	ft_deque_delete(deque);
	return (way);
}
