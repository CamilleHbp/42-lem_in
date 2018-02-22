/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:45 by briviere          #+#    #+#             */
/*   Updated: 2018/02/22 14:16:09 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	free_way(t_way *way)
{
	if (way == 0)
		return ;
	if (way->next)
		free_way(way->next);
	free(way);
}

size_t	way_len(const t_way *way)
{
	if (way == 0 || way->room == 0)
		return (0);
	if (way->room->type == END)
		return (1);
	return (way_len(way->next) + 1);
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
