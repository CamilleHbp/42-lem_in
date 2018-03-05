/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds-karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 11:48:24 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 08:39:07 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "error_manager.h"
#include "utilities.h"

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

static int64_t	*enqueu_valid_children(t_deque *deque, t_map *map,
					int64_t *path, uint8_t *visited)
{
	t_room	*parent;
	t_room	*child;
	size_t	i;

	parent = ft_deque_pop_front(deque);
	i = 0;
	while (i < parent->size_links)
	{
		child = parent->links[i];
		if (!visited[child->id] && !map->rooms[child->id]->visited)
		{
			visited[child->id] = TRUE;
			path[child->id] = parent->id;
			ft_deque_push_back(deque, (void*)child);
			if (child->type == END)
				return (path);
		}
		++i;
	}
	return (NULL);
}

static int64_t	*find_augmenting_path(t_deque *deque, t_map *map)
{
	int64_t		*path;
	int64_t		*finished_path;
	uint8_t		*visited;

	if (!(visited = ft_memalloc(sizeof(uint8_t) * map->size_rooms)))
		return (NULL);
	ft_deque_push_back(deque, get_start_room(map));
	if (!(path = init_path(map->size_rooms)))
	{
		free(visited);
		return (NULL);
	}
	while (deque->head)
		if ((finished_path = enqueu_valid_children(deque, map, path, visited)))
			break ;
	free(visited);
	return (path);
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

static t_way	**find_new_way(uint32_t way, t_way **ways, int64_t **path,
					t_map *map)
{
	t_deque		*deque;

	deque = NULL;
	if (!(way % 10))
		if (!(ways = ft_realloc(ways, sizeof(t_way*) * way,
						sizeof(t_way*) * (way + 10))))
		{
			free_edmonds_karp(&path, NULL, &deque);
			return (NULL);
		}
	if (!(deque = ft_deque_create())
		|| !(*path = find_augmenting_path(deque, map))
		|| ((*path)[get_end_room(map)->id] == -1)
		|| (!(ways[way] = build_way_from_path(*path, map))))
	{
		free_edmonds_karp(&path, NULL, &deque);
		return (ways);
	}
	ft_deque_delete(deque);
	return (ways);
}

t_way				**edmonds_karp(t_map *map)
{
	int64_t		**path;
	t_way		**ways;
	uint64_t	moves;
	uint32_t	way;

	init_edmonds_karp(&moves, &way, &ways, &path);
	while (TRUE)
	{
		if (!(ways = find_new_way(way, ways, path, map)))
			break ;
		if (!is_less_moves(&moves, map, ways))
		{
			free_edmonds_karp(&path, &ways[way], NULL);
			break ;
		}
		free_edmonds_karp(&path, NULL, NULL);
		++way;
	}
	free(path);
	if (!ways[0])
	{
		free(ways);
		return (NULL);
	}
	return (ways);
}
