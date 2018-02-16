/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:17:34 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 15:46:33 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "parsing.h"
#include "utilities.h"

// static t_room	*check_room_double(t_map *map, t_room *room)
// {
	//find out if room already exist
	// map->rooms[i]->type = room->type;
	// map->rooms[i]->x = room->x;
	// map->rooms[i]->y = room->y;
	// free(room);
	// return (NULL);
// }

char			*get_coordinate(char *line, int32_t *coordinate)
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

	if (!(room = init_room()))
		return (ERROR);
	if (!(start_cpy = ft_strdup((line))))
		return (error_parsing_room(start_cpy, room));
	end_cpy = start_cpy + ft_strlen(start_cpy) - 1;
	if (!(end_cpy = get_coordinate(end_cpy, &(room->y)))
		|| !(end_cpy = get_coordinate(end_cpy, &(room->x)))
		|| (start_cpy == end_cpy))
		return (error_parsing_room(start_cpy, room));
	room->name = start_cpy;
	room->type = room_type;
	// if ((room = check_room_double(map)))
	// {
		// copy_and_free_room(tmp, room);
		// free(tmp);
	// }
	// else
		// room = tmp;
		//debug
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
