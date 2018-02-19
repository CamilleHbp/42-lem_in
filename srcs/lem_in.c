/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:42:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/19 14:33:07 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "lem_in.h"
#include "parsing.h"
#include "utilities.h"

static void	init_map(t_map *map)
{
	map->ants = 0;
	map->rooms = NULL;
	map->size_rooms = 0;
	map->ways = 0;
}

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
** as it is reserved for tubes.
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
	int8_t	status;
	t_map	map;
	t_input	input;

	init_map(&map);
	if ((status = parse_map(&map, &input)) == ERROR)
		ft_print("error\n");
	//debug
	ft_print("Printing input:\n");
	//debug
	print_and_free_input(input);
	//debug
	ft_print("Printing map:\n");
	//debug
	print_map(map);
	status = SUCCESS;
	free_map(&map);
	return (status);
}
