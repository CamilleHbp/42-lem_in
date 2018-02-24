/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:42:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 20:12:24 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"
#include "parsing.h"
#include "utilities.h"

/*
** -h --help: rules
**
** 1 - You need to specify the number of ants int the maze.
** This number must be an integer that can fit in a signed 64 bits value.
** The absolute value will used.
**
** 2 - You need to specify a number of rooms, with at least a start and an end
** room.
** You can specify a start or end room by using the ##start or ##end command
** before the room definition.
** A room definition is as follows: name [space] x [space] y
** All parameters are separated by at least one space or tab.
** The name is a string of characters that CANNOT have a '-' in their names
** as it is reserved for tubes. It cannot have a ' ' in their names as well
** before they are used to delimit parameters.
**
** Coordinates are integers that can fit in a signed 64 bits value.
** The number of rooms must fit in a 64 bits unsigned integer.
**
** If a room is redefined, the last occurence erases the first one.
** This means if a room is defined with the command start, and then redefined
** without the command, it will be a simple room. not start nor end.
**
*/

int			main(void)
{
	t_map	map;
	t_input	input;
	int32_t	i;

	init_map(&map);
	if (parse_map(&map, &input) == ERROR)
		ft_print("error\n");
	// if (solve_map(&map) == ERROR)
		// ft_print("map error\n");
	//debug
	//ft_print("Printing input:\n");
	//debug
	//print_and_free_input(input);
	//debug
	ft_print("Printing map:\n");
	//debug
	print_map(map);
	free_map(&map);
	i = 0;
	while (i < input.nb_lines)
		free(input.lines[i++]);
	free(input.lines);
	return (SUCCESS);
}
