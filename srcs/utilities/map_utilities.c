/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:07:00 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/26 11:05:47 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	free_map(t_map *map)
{
	if (map->rooms)
	{
		while (map->size_rooms > 0)
		{
			map->size_rooms -= 1;
			free_room(map->rooms[map->size_rooms]);
			map->rooms[map->size_rooms] = NULL;
		}
		free(map->rooms);
		map->rooms = NULL;
	}
	if (map->adj_matrix)
		free(map->adj_matrix);
}

t_room	*get_end_room(const t_map *map)
{
	t_room		*tmp;
	size_t		idx;

	idx = 0;
	while (idx < map->size_rooms)
	{
		tmp = map->rooms[idx];
		if (tmp->type == END)
			return (tmp);
		idx++;
	}
	return (0);
}

t_room	*get_room_by_id(t_map	*map, uint64_t id)
{
	uint64_t	i;

	i = 0;
	while (i < map->size_rooms)
	{
		if (map->rooms[i]->id == id)
			return (map->rooms[i]);
		++i;
	}
	return (NULL);
}

t_room	*get_start_room(const t_map *map)
{
	t_room		*tmp;
	size_t		idx;

	idx = 0;
	while (idx < map->size_rooms)
	{
		tmp = map->rooms[idx];
		if (tmp->type == START)
			return (tmp);
		idx++;
	}
	return (0);
}

void	init_map(t_map *map)
{
	map->ants = 0;
	map->rooms = NULL;
	map->size_rooms = 0;
	map->ways = 0;
	map->adj_matrix = NULL;
}
