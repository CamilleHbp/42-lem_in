/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:42:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 15:38:55 by cbaillat         ###   ########.fr       */
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

int			main(void)
{
	int8_t	status;
	t_map	map;

	init_map(&map);
	if ((status = parse_map(&map)) == ERROR)
		ft_print("error\n");
	status = SUCCESS;
	// ft_print("map address: %p\n", &map);
	free_map(&map);
	return (status);
}
