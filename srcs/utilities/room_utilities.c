/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:04:43 by briviere          #+#    #+#             */
/*   Updated: 2018/03/05 07:54:51 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

int8_t	add_room(t_map *map, t_room *room)
{
	static uint64_t	i;

	if (!(i % ROOM_ALLOC))
	{
		if (!(map->rooms = ft_realloc(map->rooms,
								sizeof(t_room*) * i,
								sizeof(t_room*) * (i + ROOM_ALLOC))))
			return (ERROR);
	}
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
		if (room->links)
			free(room->links);
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
	room->ant = 0;
	room->links = NULL;
	room->size_links = 0;
	room->prev = NULL;
	return (room);
}
