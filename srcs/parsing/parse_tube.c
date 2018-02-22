/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:51 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 15:32:59 by briviere         ###   ########.fr       */
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

static int8_t	link_rooms(t_room *room, t_room *to_link)
{
	uint64_t	i;

	i = 0;
	while (i < room->size_links)
	{
		if (!ft_strcmp(room->links[i]->name, to_link->name))
			return (SUCCESS);
		++i;
	}
	if ((room->size_links + 1) >= room->alloc_links)
	{
		if (!(room->links = ft_realloc(room->links,
								sizeof(t_room *) * room->alloc_links,
								sizeof(t_room *) * (room->alloc_links * 2))))
			return (ERROR);
		room->alloc_links *= 2;
	}
	room->links[room->size_links] = to_link;
	room->size_links += 1;
	return (SUCCESS);
}

int8_t		parse_tube(char *line, t_map *map)
{
	t_room	*room1;
	t_room	*room2;
	char	*name;
	char	*div;

	if ((div = ft_strchr(line, '-')) != ft_strrchr(line, '-') || !div)
		return (ERROR);
	// search first name
	name = ft_strsub(line, 0, (div - line));
	if (*name == '\0' || (room1 = return_room(name, *map)) == NULL)
		return (error_parsing_tube(name));
	free(name);
	// if found, search second name
	name = ft_strsub(line, (div - line + 1), (ft_strlen(line) - (div - line)));
	if (*name == '\0' || (room2 = return_room(name, *map)) == NULL)
		return (error_parsing_tube(name));
	free(name);
	// if found create a link by taking the pointer of one and putting it in
	// the links of the other.
	if (link_rooms(room1, room2) == ERROR || link_rooms(room2, room1) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
