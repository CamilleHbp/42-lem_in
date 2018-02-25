/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:04:43 by briviere          #+#    #+#             */
/*   Updated: 2018/02/25 09:50:14 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

int8_t	add_room(t_map *map, t_room *room)
{
	static uint64_t	i;

	if (!(map->rooms = ft_realloc(map->rooms,
								sizeof(t_room*) * map->size_rooms,
								sizeof(t_room*) * (map->size_rooms + 1))))
		return (ERROR);
	map->rooms[map->size_rooms] = room;
	map->size_rooms += 1;
	room->id = i++;
	return (SUCCESS);
}

void	free_room(t_room *room)
{
	if (room)
	{
		if (room->name)
			free(room->name);
		free(room);
	}
}

t_room	*init_room(void)
{
	t_room	*room;

	if (!(room = malloc(sizeof(t_room))))
		return (NULL);
	room->name = NULL;
	room->x = -1;
	room->y = -1;
	room->type = ROOM;
	room->id = 0;
	room->visited = 0;
	room->prev = NULL;
	return (room);
}
