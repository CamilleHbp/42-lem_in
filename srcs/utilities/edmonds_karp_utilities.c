/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds-karp_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 07:57:52 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 08:35:37 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	init_edmonds_karp(uint64_t *moves, uint32_t *way, t_way ***ways,
			int64_t ***path)
{
	*moves = UINT64_MAX;
	*way = 0;
	*ways = NULL;
	*path = ft_memalloc(sizeof(int64_t**));

}

void	free_edmonds_karp(int64_t ***path, t_way **way, t_deque **deque)
{
	if (path && *path && **path)
	{
		free(**path);
		**path = NULL;
	}
	if (way && *way)
	{
		free_way(*way);
		*way = NULL;
	}
	if (deque && *deque)
	{
		ft_deque_delete(*deque);
		*deque = NULL;
	}
}

int8_t	is_less_moves(uint64_t *moves, t_map *map, t_way **way_array)
{
	long double	new_moves;
	uint64_t	array_length;
	uint64_t	i;

	i = 0;
	array_length = 0;
	if (way_array)
		while (way_array[i])
		{
			array_length += way_array[i]->depth;
			++i;
		}
	new_moves = ((long double)(map->ants + array_length)) / (long double)i;
	if ((new_moves - (uint64_t)new_moves))
		new_moves += 1;
	if (new_moves >= *moves)
		return (0);
	else
	{
		*moves = (long long int)new_moves;
		return (1);
	}
}
