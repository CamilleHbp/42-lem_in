/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:45 by briviere          #+#    #+#             */
/*   Updated: 2018/02/26 15:43:03 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	clear_way(t_way *way)
{
	if (!way || !way->room)
		return ;
	way->room->visited = 0;
	clear_way(way->next);
}

t_way	*dup_way(const t_way *way)
{
	t_way	*new_way;

	if (way == 0)
		return (0);
	if ((new_way = malloc(sizeof(t_way))) == 0)
		return (0);
	new_way->room = way->room;
	new_way->next = dup_way(way->next);
	return (new_way);
}

void	free_way(t_way *way)
{
	if (way == 0)
		return ;
	if (way->next)
		free_way(way->next);
	free(way);
}

int8_t	is_valid_way(t_way *way)
{
	if (way)
	{
		while (way->next)
			way = way->next;
		if (way->room->type == END)
			return (1);
	}
	return (0);
}

size_t	way_len(const t_way *way)
{
	if (way == 0 || way->room == 0)
		return (0);
	if (way->room->type == END)
		return (1);
	return (way_len(way->next) + 1);
}
