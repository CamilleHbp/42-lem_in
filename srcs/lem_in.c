/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:42:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 09:48:32 by cbaillat         ###   ########.fr       */
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
**
** usage
*/

uint8_t		return_flags(int ac, char **av)
{
	uint8_t		flags;
	int			i;
	static char	usage[] = "Usage:\n-d : debug mode -> displays the line "
					"where the parsing failed\n-p : displays the possible "
					"paths for the number of ants\n-a : hides the ants moves\n"
					"-i : hides the original input\n";

	flags = 0;
	i = 1;
	while (i < ac)
	{
		if ((flags = is_flag(av[i])))
			++i;
		else
		{
			ft_print("%s", usage);
			return (0);
		}
	}
	return (flags);
}

static void	print_output(uint8_t flags, t_input input, uint32_t ants,
				t_way **ways)
{
	uint8_t	output;

	output = 0;
	if (!(flags & 1 << FLAG_INPUT))
	{
		print_input(input);
		++output;
	}
	if (!(flags & 1 << FLAG_ANTS))
	{
		if (output)
			ft_putchar('\n');
		mv_ants(ways, ants);
		++output;
	}
	if (flags & 1 << FLAG_PATH)
	{
		if (output)
			ft_putchar('\n');
		print_ways(ways);
	}
}

static void	resolve_lem_in(t_map *map, t_input input, uint8_t flags)
{
	t_way	**ways;

	ways = NULL;
	if (!(ways = solve_map(map)))
		ft_print("error\n");
	else
		print_output(flags, input, (uint32_t)map->ants, ways);
	free_ways(ways);
}

int			main(int ac, char **av)
{
	t_map	map;
	t_input	input;
	uint8_t	flags;

	init_map(&map);
	flags = 0;
	if (ac > 1)
		if (!(flags = return_flags(ac, av)))
			return (SUCCESS);
	if (parse_map(&map, &input, flags) == ERROR)
		ft_print("error\n");
	else
		resolve_lem_in(&map, input, flags);
	free_map(&map);
	free_input(input);
	return (SUCCESS);
}
