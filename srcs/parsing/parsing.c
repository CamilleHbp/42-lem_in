/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:43 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 12:54:46 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_manager.h"
#include "utilities.h"

static int8_t	check_map(t_map *map)
{
	uint8_t		start;
	uint8_t		end;
	uint64_t	i;

	i = 0;
	start = 0;
	end = 0;
	while (i < map->size_rooms)
	{
		if (map->rooms[i]->type == START)
			++start;
		else if (map->rooms[i]->type == END)
			++end;
		++i;
	}
	if (start != 1 || end != 1)
		return (ERROR);
	return (SUCCESS);
}

static int64_t	get_ants(t_input *input)
{
	int64_t	i;
	int8_t	status;
	char	*line;

	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (*line == '\0' || save_line(line, input) == ERROR)
		{
			free(line);
			return (error_parsing(input, NULL));
		}
		if (line[0] == '#')
			continue ;
		i = 0;
		while (line[i])
			if (!(ft_isdigit(line[i++])))
				return (error_parsing(input, NULL));
		if ((i = ft_atoi64(line)) <= 0)
			return (ERROR);
		return (ft_abs64(i));
	}
	free(line);
	return (error_parsing(input, NULL));
}

static int8_t	get_rooms(t_map *map, t_input *input)
{
	char	*line;
	int8_t	room_type;
	int8_t	status;
	int8_t	type;

	room_type = ROOM;
	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (save_line(line, input) == ERROR)
			return (error_parsing(input, map));
		if (line[0] == '#')
		{
			if (line [1] == '#')
				if ((type = parse_type(&(line[2]))) == START || type == END)
					room_type = type;
		}
		else
		{
			if (check_end_rooms(line) == SUCCESS)
				return (SUCCESS);
			if (parse_room(line, map, room_type) == ERROR)
				return (error_parsing(input, map));
			room_type = ROOM;
		}
	}
	free(line);
	return (SUCCESS);
}

static int8_t	get_tubes(t_map *map, t_input *input)
{
	char	*line;
	int8_t	status;

	if (parse_tube(input->lines[input->nb_lines - 1], map) == ERROR)
	{
		free(input->lines[--(input->nb_lines)]);
		return (ERROR);
	}
	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (save_line(line, input) == ERROR)
			return (error_parsing(input, map));
		if (line[0] == '#')
			continue ;
		else
		{
			if (parse_tube(line, map) == ERROR)
			{
				free(input->lines[--(input->nb_lines)]);
				return (SUCCESS);
			}
		}
	}
	free(line);
	return (SUCCESS);
}

int8_t			parse_map(t_map *map, t_input *input)
{
	init_input(input);
	if ((map->ants = get_ants(input)) <= 0)
		return (ERROR);
	if (get_rooms(map, input) == ERROR)
		return (ERROR);
	if (!(map->adj_matrix = ft_memalloc(sizeof(uint64_t) * map->size_rooms)))
		return (ERROR);
	if (get_tubes(map, input) == ERROR)
		return (ERROR);
	if (check_map(map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
