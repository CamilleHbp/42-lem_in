/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:42:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 11:40:26 by cbaillat         ###   ########.fr       */
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

/*
** usage
*/

uint8_t	return_flags(int ac, char **av)
{
	uint8_t	flags;
	int	i;

	static const char	usage[] = "Usage:\n-d : debug mode -> displays the line"
					" where the parsing failed\n-p : displays the possible "
					"paths for the number of ants\n-a : hides the ants moves\n"
					"-i : hides the original input\n";

	flags = 0;
	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-a"))
			flags |= 1 << FLAG_ANTS;
		else if (!ft_strcmp(av[i], "-i"))
			flags |= 1 << FLAG_INPUT;
		else if (!ft_strcmp(av[i], "-p"))
			flags |= 1 << FLAG_PATH;
		else if (!ft_strcmp(av[i], "-d"))
			flags |= 1 << FLAG_DEBUG;
		else
		{
			ft_print("%s", usage);
			return (0);
		}
		++i;
	}
	return (flags);
}

static void	resolve_lem_in(t_map *map, t_input input, uint8_t flags)
{
	t_way	**ways;
	uint8_t	output;

	ways = NULL;
	output = 0;
	if (!(ways = solve_map(map)))
		ft_print("error\n");
	else
	{
		if (!(flags & 1 << FLAG_INPUT))
		{
			print_input(input);
			++output;
		}
		if (!(flags & 1 << FLAG_ANTS))
		{
			if (output)
				ft_putchar('\n');
			mv_ants(ways, (uint32_t)map->ants);
		}
		if (flags & 1 << FLAG_PATH)
		{
			if (output)
				ft_putchar('\n');
			print_ways(ways);
		}
	}
	free_ways(ways);
}
int			main(int ac, char **av)
{
	t_map	map;
	t_input	input;
	uint8_t	flags;
	int32_t	i;

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
	i = 0;
	while (i < input.nb_lines)
		free(input.lines[i++]);
	free(input.lines);
	return (SUCCESS);
}
