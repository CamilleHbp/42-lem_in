/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:59:14 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 15:59:15 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "utilities.h"

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
		free(room);
	return (ERROR);
}

int8_t	error_parsing_tube(char *name)
{
	if (name)
		free(name);
	return (ERROR);
}
