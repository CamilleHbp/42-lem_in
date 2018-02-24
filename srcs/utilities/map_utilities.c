/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:07:00 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 20:11:51 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void		free_map(t_map *map)
{
	if (map->rooms)
	{
		while (map->size_rooms > 0)
		{
			map->size_rooms -= 1;
			free_room(map->rooms[map->size_rooms]);
			map->rooms[map->size_rooms] = NULL;
		}
		free(map->rooms);
		map->rooms = NULL;
	}
	if (map->adj_matrix)
		free(map->adj_matrix);
}

void		init_input(t_input *input)
{
	input->lines = NULL;
	input->nb_lines = 0;
}

void	init_map(t_map *map)
{
	map->ants = 0;
	map->rooms = NULL;
	map->size_rooms = 0;
	map->ways = 0;
	map->adj_matrix = NULL;
}
