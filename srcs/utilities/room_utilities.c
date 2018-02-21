/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:04:43 by briviere          #+#    #+#             */
/*   Updated: 2018/02/21 13:15:47 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

t_room	*get_start_room(const t_map *map)
{
	t_room		*tmp;
	size_t		idx;

	idx = 0;
	while (idx < map->size_rooms)
	{
		tmp = map->rooms[idx];
		if (tmp->type == START)
			return (tmp);
		idx++;
	}
	return (0);
}

t_room	*get_end_room(const t_map *map)
{
	t_room		*tmp;
	size_t		idx;

	idx = 0;
	while (idx < map->size_rooms)
	{
		tmp = map->rooms[idx];
		if (tmp->type == END)
			return (tmp);
		idx++;
	}
	return (0);
}
