/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds-karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:48:24 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/28 18:52:29 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

static int64_t	*init_path(uint32_t map_size)
{
	uint32_t	i;
	int64_t		*path;

	if (!path)
		if (!(path = (int64_t*)malloc(sizeof(int64_t) * map_size)))
			return (NULL);
	i = 0;
	while (i < map_size)
	{
		path[i] = -1;
		++i;
	}
	return (path);
}

static void		apply_augmenting_path(t_map *map, uint32_t **flow, int64_t *path)
{
	t_room	*start;
	t_room	*parent;
	t_room	*child;

	start = get_start_room(map);
	child = get_end_room(map);
	while (child->id != start->id)
	{
		parent = get_room_by_id(map, path[child->id]);
		(*flow)[parent->id] |= 1ULL << child->id;
		(*flow)[child->id] |= 0ULL << parent->id;
		child = parent;
	}
}

static uint8_t	is_grandchildren_free(uint32_t *flow, uint32_t child_id,
					t_room *parent, t_map *map)
{
	uint32_t	i;

	i = 0;
	while (i < map->size_rooms)
	{
		if ((flow[child_id] & (1ULL << i)) && (i != parent->id))
		{
			// ft_print("Child %s to grandchild %s full\n", map->rooms[child_id]->name, map->rooms[i]->name);
			return (0);
		}
		++i;
	}
	return (1);
}

static int64_t	find_augmenting_path(t_deque *deque, t_map *map,
					uint32_t **flow, int64_t **path)
{
	uint32_t	child_id;
	uint8_t		*visited;
	t_room		*parent;
	t_room		*child;

	if (!(visited = ft_memalloc(sizeof(uint8_t) * map->size_rooms)))
		return (ERROR);
	*path = init_path(map->size_rooms);
	while (deque->head)
	{
		parent = ft_deque_pop_front(deque);
		child_id = 0;
		//debug
		// ft_print("\n-----------\nParent is %s\n", parent->name);
		// ft_print("\nflow parent is: %d\n", (*flow)
		while (child_id < map->size_rooms)
		{
			// We check if there is a way forward between ROOM and NEIGHBOUR.
			// If there is, we check if there still is capacity on the edge.
			// We check if there is a way backward between NEIGHBOUR and ROOM.
			// If there is, we check if the backward flow exists.
			// We need to check that all the grand-children of the child room are free, otherwise, we can't use it.
		//debug
		// ft_print("Child %s to parent %s is %s\n", map->rooms[child_id]->name, parent->name, ((*flow)[child_id] & (1ULL << parent->id)) ? "full" : "empty");
		// ft_print("Parent %s to child %s is %s\n", parent->name, map->rooms[child_id]->name, ((*flow)[parent->id] & (1ULL << child_id)) ? "full" : "empty");
			if (!visited[child_id] && !map->rooms[child_id]->visited)
				if ((((map->adj_matrix[parent->id] & (1ULL << child_id)) && !((*flow)[parent->id] & (1ULL << child_id)))
					|| ((map->adj_matrix[child_id] & (1ULL << parent->id)) && ((*flow)[child_id] & (1ULL << parent->id)))))
					// && is_grandchildren_free(*flow, child_id, parent, map))
					// all grand-children are free

				{
					child = get_room_by_id(map, child_id);
					visited[child_id] = TRUE;
					(*path)[child_id] = parent->id;
					ft_deque_push_back(deque, (void*)child);
					if (child->type == END)
					{
						//debug
						// ft_print("SUCCESS\n----------------------\n");
						return (SUCCESS);
					}
				}
			++child_id;
		}
	}
	//debug
	// ft_print("ERROR\n----------------------\n");
	return (ERROR);
}

t_way	*build_way_from_path(int64_t *path, t_map *map)
{
	t_way		*way;
	t_way		*tmp;
	t_room		*start;
	uint32_t	id;
	uint32_t	next;

	if (!(way = ft_memalloc(sizeof(t_way))))
		return (NULL);
	if (!(way->room = get_end_room(map)))
	{
		free(way);
		return (NULL);
	}
	id = way->room->id;
	start = get_start_room(map);
	// Il ne faut que Start et End soient visites.
	while (42)
	{
		id = path[id];
		tmp = way;
		if (!(way = ft_memalloc(sizeof(t_way))))
		{
			free_way(tmp);
			return (NULL);
		}
		way->room = get_room_by_id(map, id);
		way->next = tmp;
		tmp->prev = way;
		if (id == start->id)
			break ;
		//test
		way->room->visited = 1;
	}
	return (way);
}
/*
** We need to create a fake edge with the capacity of the vertex, for each
** vertex.
** The reason is that Edmonds-karp only limits itself by the capacity in the
** edges.
** If I have two edges of capacity one entering a room, and two edges of
** capacity 1 going out, Edmonds-Karp is going to use the room as if it was able
** to manage such a flow. Where if fact I can't.
** By create a new vertex of 1 in place of the room, I will force Edmond-Karps
** to use each room as if it could only flow 1 through it.
*/

int64_t			edmonds_karp(t_map *map)
{
	t_deque		*deque;
	uint32_t	*flow;
	int64_t 	*path;
	t_room		*start;
	t_way		*way;

	start = get_start_room(map);
	// ft_print("Start room: %s\n", start->name);
	path = NULL;
	if (!(path = init_path(map->size_rooms)))
		return (ERROR);
	if (!(flow = ft_memalloc(sizeof(uint32_t) * map->size_rooms)))
	{
		free(path);
		return (ERROR);
	}
	// return shortest will either return FOUND, ERROR (negative)
	// or a positive number that will represent the room where the first
	// collision took place
	// If a collision took place but no way was found, we build the way up to
	while (42)
	{
		if (!(deque = ft_deque_create()))
			return (ERROR);
		ft_deque_push_back(deque, start);
		find_augmenting_path(deque, map, &flow, &path);
		if (path[get_end_room(map)->id] == -1)
			break ;
		apply_augmenting_path(map, &flow, path);
		// print_path(path, map);
		way = build_way_from_path(path, map);
		print_way(way);
		if (way)
			free_way(way);
		ft_deque_delete(deque);
	}
	free(path);
	// print_flow(map, flow);
	return (SUCCESS);
}
