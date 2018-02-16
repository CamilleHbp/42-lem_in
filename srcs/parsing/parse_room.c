/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:17:34 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 13:37:05 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utilities.h"

static t_room	*check_room_double(t_map *map)
{
	return (NULL);
}

static void		copy_and_free_room(t_room *src, t_room *dst)
{
	dst->type = src->type;
	dst->x = src->x;
	dst->y = src->y;
	free(src);
}

int8_t			parse_room(char *line, t_map *map, int8_t room_type)
{
	size_t	line_len;
	size_t	i;
	t_room	*room;
	t_room	*tmp;

	// line_len = ft_strlen(line);
	// i = line_len;
	if (!(tmp = init_room()))
			return (ERROR);
	// while (--i)
		// if (!(is_digit()))
	tmp->x = 10;
	tmp->y = 20;
	tmp->name = "room1";
	// if ((room = check_room_double(map)))
	// {
		// copy_and_free_room(tmp, room);
		// free(tmp);
	// }
	// else
		// room = tmp;
		//debug
	if (add_room(map, tmp) == ERROR)
	{
		free(tmp);
		return (ERROR);
	}
	return (SUCCESS);
}

int8_t			parse_type(char *cmd_line, t_map *map)
{
	if (!(ft_strcmp(cmd_line, "start")))
		return (START);
	else if (!(ft_strcmp(cmd_line, "end")))
		return (END);
	return (ROOM);
}
