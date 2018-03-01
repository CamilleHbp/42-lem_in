/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds-karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:48:24 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/01 12:47:54 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

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

/*
** We check if there is a way forward between ROOM and NEIGHBOUR.
** If there is, we check if there still is capacity on the edge.
** We check if there is a way backward between NEIGHBOUR and ROOM.
** If there is, we check if the backward flow exists.
**
** An idea that didn't work was to check that all the grand-children of the
** child room are free, otherwise, we can't use it. It messed up the algorithm.
**
** Instead, I set the room as visited when building the found path, and check
** for it in my algo.
** It causes the algo to sometimes find a path that blocks other paths, but this
** is due to the way Edmonds-Karp works: it uses edges, not vertices, to limit
** the flow in the graph.
*/

static int64_t	*find_augmenting_path(t_deque *deque, t_map *map,
					uint32_t **flow)
{
	int64_t		*path;
	uint32_t	child_id;
	uint8_t		*visited;
	t_room		*parent;
	t_room		*child;

	if (!(visited = ft_memalloc(sizeof(uint8_t) * map->size_rooms)))
		return (NULL);
	ft_deque_push_back(deque, get_start_room(map));
	if (!(path = init_path(map->size_rooms)))
	{
		free(visited);
		return (NULL);
	}
	while (deque->head)
	{
		parent = ft_deque_pop_front(deque);
		child_id = 0;
		while (child_id < map->size_rooms)
		{
			if (!visited[child_id] && !map->rooms[child_id]->visited)
				if ((((map->adj_matrix[parent->id] & (1ULL << child_id)) && !((*flow)[parent->id] & (1ULL << child_id)))
					|| ((map->adj_matrix[child_id] & (1ULL << parent->id)) && ((*flow)[child_id] & (1ULL << parent->id)))))
				{
					child = get_room_by_id(map, child_id);
					visited[child_id] = TRUE;
					path[child_id] = parent->id;
					ft_deque_push_back(deque, (void*)child);
					if (child->type == END)
					{
						free(visited);
						return (path);
					}
				}
			++child_id;
		}
	}
	free(visited);
	return (path);
}

static void	free_edmonds_karp(uint32_t **flow, int64_t **path, t_way **way,
			t_deque **deque)
{
	if (flow && *flow)
	{
		free(*flow);
		*flow = NULL;
	}
	if (path && *path)
	{
		free(*path);
		*path = NULL;
	}
	if (way && *way)
	{
		free_way(*way);
		*way = NULL;
	}
	if (deque && *deque)
	{
		ft_deque_delete(*deque);
		*deque = NULL;
	}
}

static int8_t	is_less_moves(uint64_t *moves, t_map *map, t_way **way_array)
{
	long double	new_moves;
	uint64_t	array_length;
	uint64_t	i;

	i = 0;
	array_length = 0;
	if (way_array)
		while (way_array[i])
		{
			array_length += way_array[i]->depth;
			++i;
		}
	new_moves = ((long double)(map->ants + array_length)) / (long double)i;
	if ((new_moves - (uint64_t)new_moves))
		new_moves += 1;
	if (new_moves >= *moves)
		return (0);
	else
	{
		*moves = (long long int)new_moves;
		return (1);
	}
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

t_way			**edmonds_karp(t_map *map)
{
	t_deque		*deque;
	uint32_t	*flow;
	int64_t 	*path;
	t_way		**ways;
	uint64_t	moves;
	uint32_t	way;

	if (!(flow = ft_memalloc(sizeof(uint32_t) * map->size_rooms)))
		return (NULL);
	moves = UINT64_MAX;
	way = 0;
	path = NULL;
	ways = NULL;
	while (TRUE)
	{
		if (!(way % 10))
			if (!(ways = ft_realloc(ways, sizeof(t_way*) * way, sizeof(t_way*) * (way + 10))))
			{
				free_edmonds_karp(&flow, &path, NULL, &deque);
				break ;
			}
		if (!(deque = ft_deque_create())
			|| !(path = find_augmenting_path(deque, map, &flow))
			|| path[get_end_room(map)->id] == -1)
		{
			free_edmonds_karp(&flow, &path, NULL, &deque);
			break ;
		}
		apply_augmenting_path(map, &flow, path);
		if (!(ways[way] = build_way_from_path(path, map)))
		{
			free_edmonds_karp(&flow, &path, NULL, &deque);
			break ;
		}
		if (!is_less_moves(&moves, map, ways))
		{
			free_edmonds_karp(&flow, &path, &ways[way], &deque);
			break ;
		}
		free_edmonds_karp(NULL, &path, NULL, &deque);
		++way;
	}
	if (flow)
		free(flow);
	return (ways);
}
