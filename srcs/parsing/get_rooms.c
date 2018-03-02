/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:34:23 by briviere          #+#    #+#             */
/*   Updated: 2018/03/02 11:44:18 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_manager.h"

static int8_t	check_nb_rooms(t_map *map, t_input *input, uint8_t flags)
{
	if (map->size_rooms == 0)
	{
		if (flags & (1 << FLAG_DEBUG))
			ft_print("line %d: no room\n", input->nb_lines);
		return (ERROR);
	}
	return (SUCCESS);
}

static int8_t	get_room_type(char *line, int8_t prev_type)
{
	int8_t	type;

	if (line [1] == '#')
		if ((type = parse_type(&(line[2]))) == START || type == END)
			return (type);
	return (prev_type);
}

static void		print_error(t_input *input, uint8_t flags)
{
	if (flags & (1 << FLAG_DEBUG))
		ft_print("line %d: invalid room\n", input->nb_lines);
}

int8_t			get_rooms(t_map *map, t_input *input, uint8_t flags)
{
	char	*line;
	int8_t	room_type;
	int8_t	status;

	room_type = ROOM;
	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (save_line(line, input) == ERROR)
			return (error_parsing(input, map));
		if (line[0] == '#')
			room_type = get_room_type(line, room_type);
		else
		{
			if (check_end_rooms(line) == SUCCESS)
				return (check_nb_rooms(map, input, flags));
			if (parse_room(line, map, room_type) == ERROR)
			{
				print_error(input, flags);
				return (error_parsing(input, map));
			}
			room_type = ROOM;
		}
	}
	free(line);
	return (SUCCESS);
}
