/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:07:00 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 13:04:26 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

int8_t	add_room(t_map *map, t_room *room)
{
	if (!(map->rooms = ft_realloc(map->rooms,
								sizeof(t_room*) * map->size_rooms,
								sizeof(t_room*) * (map->size_rooms + 1))))
		return (ERROR);
	map->rooms[map->size_rooms] = room;
	map->size_rooms += 1;
	// ft_print("adding room\n");
	// ft_print("add_room map->size_rooms = %d\n", map->size_rooms);
	// ft_print("add_room map address: %p\n", map);
	// ft_print("add_room rooms address: %p\n", map->rooms);
	return (SUCCESS);
}

void	free_map(t_map *map)
{
	// ft_print("freeing map\n");
	// ft_print("free_map map->size_rooms = %d\n", map->size_rooms);
	// ft_print("free_map map address: %p\n", map);
	// ft_print("free_map rooms address: %p\n", map->rooms);
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

void	init_input(t_input *input)
{
	input->lines = NULL;
	input->nb_lines = 0;
}

t_room	*init_room(void)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = NULL;
	room->x = -1;
	room->y = -1;
	room->type = ROOM;
	room->links = NULL;
	room->size_links = 0;
	return (room);
}
