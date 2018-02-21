/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:59:14 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 09:08:49 by cbaillat         ###   ########.fr       */
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

int8_t	error_parsing_room(char *line_cpy, t_room *room)
{
	if (line_cpy)
		free(line_cpy);
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
