/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 08:22:51 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 09:45:14 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

t_way	*init_build_way_values(t_map *map, t_room **start, uint32_t *depth,
			uint32_t *id)
{
	t_way		*way;

	if (!(way = ft_memalloc(sizeof(t_way))))
		return (NULL);
	if (!(way->room = get_end_room(map)))
	{
		free(way);
		return (NULL);
	}
	*id = way->room->id;
	*start = get_start_room(map);
	*depth = 0;
	return (way);
}

t_way	*build_way_from_path(int64_t *path, t_map *map)
{
	t_way		*way;
	t_way		*tmp;
	t_room		*start;
	uint32_t	id;
	uint32_t	depth;

	if (!(way = init_build_way_values(map, &start, &depth, &id)))
		return (NULL);
	while (++depth)
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
		way->room->visited = 1;
	}
	way->depth = depth;
	return (way);
}

int64_t	*init_path(uint32_t map_size)
{
	uint32_t	i;
	int64_t		*path;

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
