/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:43 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 16:49:15 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_manager.h"
#include "utilities.h"

static int64_t	get_ants(t_input *input)
{
	int32_t	i;
	int32_t	status;
	char	*line;

	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (*line == '\0' || save_line(line, input) == ERROR)
		{
			free(line);
			return (error_parsing(*input, NULL));
		}
		if (line[0] == '#')
			continue ;
		i = 0;
		while (line[i])
		{
			if (!(ft_isdigit(line[i++])))
			{
				free(line);
				return (error_parsing(*input, NULL));
			}
		}
		return (ft_atoi64(line));
	}
	free(line);
	return (error_parsing(*input, NULL));
}

static int8_t	get_rooms(t_map *map, t_input *input)
{
	char	*line;
	int8_t	room_type;
	int8_t	type;
	int8_t	status;

	room_type = ROOM;
	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (save_line(line, input) == ERROR)
			return (error_parsing(*input, map));
		if (line[0] == '#')
		{
			if (line [1] == '#')
				if ((type = parse_type(&(line[2]))) == START || type == END)
					room_type = type;
		}
		else
		{
			if (parse_room(line, map, room_type) == ERROR)
				return (error_parsing(*input, map));
			room_type = ROOM;
		}
	}
	free(line);
	return (SUCCESS);
}

// static int8_t	get_tubes(t_map *map, t_input *input)
// {
	// return (SUCCESS);
// }

int8_t			parse_map(t_map *map)
{
	t_input	input;

	init_input(&input);
	if ((map->ants = get_ants(&input)) <= 0)
		return (ERROR);
	if (get_rooms(map, &input) == ERROR)
		return (ERROR);
	// get_tubes(map, &input);
	//debug
	ft_print("Printing input:\n");
	//debug
	print_and_free_input(input);
	//debug
	ft_print("Printing map:\n");
	//debug
	print_map(*map);
	return (SUCCESS);
}
