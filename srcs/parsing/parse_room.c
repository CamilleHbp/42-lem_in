/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:17:34 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 14:18:04 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "parsing.h"
#include "utilities.h"

int8_t			check_end_rooms(char *line)
{
	if (ft_strchr(line, '-'))
		return (SUCCESS);
	return (ERROR);
}

static int8_t	find_and_replace_room(t_map *map, t_room room)
{
	uint64_t	i;
	if (!map->rooms)
		return (ERROR);
	i = 0;
	while (i < map->size_rooms)
	{
		if (!ft_strcmp(map->rooms[i]->name, room.name))
		{
			map->rooms[i]->type = room.type;
			map->rooms[i]->x = room.x;
			map->rooms[i]->y = room.y;
			return (SUCCESS);
		}
		++i;
	}
	return (ERROR);
}

char			*get_coordinate(char *line, int64_t *coordinate)
{
	line = rev_skip_whitespace(line);
	if (!line || !ft_isdigit(*line))
		return (NULL);
	line = rev_skip_number(line);
	*coordinate = ft_atoi64(line);
	if (!line || !ft_isspace(*(--line)))
		return (NULL);
	line = rev_skip_whitespace(line);
	*(line + 1) = '\0';
	return (line);
}

int8_t			parse_room(char *line, t_map *map, int8_t room_type)
{
	char	*start_cpy;
	char	*end_cpy;
	t_room	*room;

	if (!line || *line == '\0' || !(room = init_room()))
		return (ERROR);
	if (!(start_cpy = ft_strdup((line))))
		return (error_parsing_room(start_cpy, room));
	end_cpy = start_cpy + ft_strlen(start_cpy) - 1;
	if (!end_cpy || !(end_cpy = get_coordinate(end_cpy, &(room->y)))
		|| !(end_cpy = get_coordinate(end_cpy, &(room->x)))
		|| ft_strlen(end_cpy) == 0)
		return (error_parsing_room(start_cpy, room));
	room->name = start_cpy;
	room->type = room_type;
	if (find_and_replace_room(map, *room) == SUCCESS)
		free_room(room);
	else
		if (add_room(map, room) == ERROR)
			return (error_parsing_room(NULL, room));
	return (SUCCESS);
}

int8_t			parse_type(char *cmd_line)
{
	if (!(ft_strcmp(cmd_line, "start")))
		return (START);
	else if (!(ft_strcmp(cmd_line, "end")))
		return (END);
	return (ROOM);
}
