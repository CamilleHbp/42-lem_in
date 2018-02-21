/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:04:43 by briviere          #+#    #+#             */
/*   Updated: 2018/02/21 17:19:37 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

t_room		*get_start_room(const t_map *map)
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

t_room		*get_end_room(const t_map *map)
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

// FIXME: i have an error but i don't know why, please don't this to my mom
// error found: calculate multiple times the same path
// maybe duplicate in parsing?
uint64_t	room_count_poss_way(t_room *room, uint64_t deep)
{
	t_room		*tmp;
	size_t		idx;

	if (room == 0)
		return (0);
	if (room->type == END)
		return (1);
	if (room->full == 1)
		return (0);
	if (deep == 0)
		return (0);
	idx = 0;
	room->full = 1;
	while (idx < room->size_links)
	{
		tmp = room->links[idx];
		if (tmp->full == 0 || tmp->type == END)
			room->poss_way += room_count_poss_way(room->links[idx], deep - 1);
		idx++;
	}
	room->full = 0;
	return (room->poss_way);
}
