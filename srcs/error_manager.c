/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:59:14 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/01 16:52:49 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "utilities.h"

void	*error_flow_control(uint64_t nb_ways, t_way ***ways)
{
	uint64_t	i;
	uint64_t	j;

	if (ways)
	{
		i = 0;
		while (i < nb_ways)
		{
			j = 0;
			if (ways[i])
			{
				while (j <= i)
					if (ways[i][j])
						free_way(ways[i][j]);
				free(ways[i]);
			}
		}
		free(ways);
		ways = NULL;
	}
	return (NULL);
}

int8_t	error_parsing(t_input *input, t_map *map)
{
	if (input->lines)
	{
		while (input->nb_lines > 0)
		{
			input->nb_lines -= 1;
			free(input->lines[input->nb_lines]);
		}
		free(input->lines);
		input->lines = NULL;
	}
	if (map)
	{
		free_map(map);
		map = NULL;
	}
	return (ERROR);
}

int8_t	error_parsing_room(t_room *room)
{
	if (room)
	{
		if (room->name)
			free(room->name);
		free(room);
	}
	return (ERROR);
}

int8_t	error_parsing_tube(char *name)
{
	if (name)
		free(name);
	return (ERROR);
}
