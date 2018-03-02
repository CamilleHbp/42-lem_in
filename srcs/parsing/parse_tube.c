/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:51 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 17:23:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "parsing.h"
#include "utilities.h"

static t_room	*return_room(char *name, t_map map)
{
	uint64_t	i;

	i = 0;
	while (i < map.size_rooms)
	{
		if (!ft_strcmp(map.rooms[i]->name, name))
			return (map.rooms[i]);
		++i;
	}
	return (NULL);
}

static int8_t	link_rooms(t_room *room1, t_room *room2)
{
	size_t	i;

	if (!(room1->size_links % 5))
		if (!(room1->links = ft_realloc(room1->links,
			sizeof(t_room*) * room1->size_links,
			sizeof(t_room*) * room1->size_links + 5)))
			return (ERROR);
	if (!(room2->size_links % 5))
		if (!(room2->links = ft_realloc(room2->links,
			sizeof(t_room*) * room2->size_links,
			sizeof(t_room*) * room2->size_links + 5)))
			return (ERROR);
	i = 0;
	while (i < room1->size_links)
		if (room1->links[i++] == room2)
			return (SUCCESS);
	room1->links[room1->size_links] = room2;
	room1->size_links += 1;
	room2->links[room2->size_links] = room1;
	room2->size_links += 1;
	return (SUCCESS);
}

int8_t			parse_tube(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;
	char	*name;
	char	*div;

	if ((div = ft_strchr(line, '-')) != ft_strrchr(line, '-') || !div)
		return (ERROR);
	name = ft_strsub(line, 0, (div - line));
	if (*name == '\0' || (room1 = return_room(name, *map)) == NULL)
		return (error_parsing_tube(name));
	free(name);
	name = ft_strsub(line, (div - line + 1), (ft_strlen(line) - (div - line)));
	if (*name == '\0' || (room2 = return_room(name, *map)) == NULL)
		return (error_parsing_tube(name));
	free(name);
	if (link_rooms(room1, room2) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
