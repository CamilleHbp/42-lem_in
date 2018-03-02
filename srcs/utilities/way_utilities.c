/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:45 by briviere          #+#    #+#             */
/*   Updated: 2018/03/02 17:10:40 by briviere         ###   ########.fr       */
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

void	free_ways(t_way **ways)
{
	size_t	i;

	i = 0;
	if (ways)
	{
		while (ways[i])
			free_way(ways[i++]);
		free(ways);
	}
}
