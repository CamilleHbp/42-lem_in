/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:43 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 11:55:38 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_manager.h"
#include "utilities.h"

static int8_t	check_map(t_map *map, uint8_t flags)
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
	{
		if (flags & (1 << FLAG_DEBUG))
		{
			if (start > 1)
				ft_print("map: there is more than 1 start room\n");
			if (end > 1)
				ft_print("map: there is more than 1 end room\n");
		}
		return (ERROR);
	}
	return (SUCCESS);
}

static int8_t	get_tubes(t_map *map, t_input *input, uint8_t flags)
{
	char	*line;
	int8_t	status;

	if (parse_tube(input->lines[input->nb_lines - 1], map) == ERROR)
	{
		if (flags & (1 << FLAG_DEBUG))
			ft_print("line %d: invalid tube\n", input->nb_lines);
		free(input->lines[--(input->nb_lines)]);
		return (ERROR);
	}
	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (save_line(line, input) == ERROR)
			return (error_parsing(input, map));
		if (line[0] == '#')
			continue ;
		else if (parse_tube(line, map) == ERROR)
		{
			free(input->lines[--(input->nb_lines)]);
			return (SUCCESS);
		}
	}
	free(line);
	return (SUCCESS);
}

int8_t			parse_map(t_map *map, t_input *input, uint8_t flags)
{
	init_input(input);
	if ((map->ants = get_ants(input, flags)) <= 0)
		return (ERROR);
	if (get_rooms(map, input, flags) == ERROR)
		return (ERROR);
	if (!(map->adj_matrix = ft_memalloc(sizeof(uint64_t) * map->size_rooms)))
		return (ERROR);
	if (get_tubes(map, input, flags) == ERROR)
		return (ERROR);
	if (check_map(map, flags) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
