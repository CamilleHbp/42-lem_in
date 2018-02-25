/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:32:51 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 10:48:32 by cbaillat         ###   ########.fr       */
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

static void		link_rooms(t_room *room1, t_room *room2, uint64_t *matrix)
{
	matrix[room1->id] |= 1ULL << room2->id;
	matrix[room2->id] |= 1ULL << room1->id;
}

int8_t		parse_tube(char *line, t_map *map)
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
	link_rooms(room1, room2, map->adj_matrix);
	return (SUCCESS);
}
