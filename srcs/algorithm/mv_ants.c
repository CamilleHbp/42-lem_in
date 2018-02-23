/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:07:53 by briviere          #+#    #+#             */
/*   Updated: 2018/02/23 09:37:00 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

// TODO: recursive to move from the end
int8_t		do_move(t_way *way, int8_t first)
{
	if (!way || !way->next ||
			(way->next->room->full && way->next->room->type != END))
		return (ERROR);
	if (way->room->type == END || !way->room->full)
		return (ERROR);
	way->room->full--;
	way->next->room->full++;
	if (!first)
		ft_putchar(' ');
	ft_print("L%s-%s", way->room->name, way->next->room->name);
	return (SUCCESS);
}

int8_t		mv_ants(t_way **ways)
{
	size_t	i;
	int8_t	first;
	int8_t	has_moved;
	t_way	*tmp;

	i = 0;
	first = 1;
	has_moved = 0;
	while (ways[i])
	{
		tmp = ways[i];
		while (tmp)
		{
			if (do_move(tmp, first) == SUCCESS)
			{
				first = 0;
				has_moved = 1;
				if (tmp->next)
					tmp = tmp->next->next;
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	if (has_moved)
	{
		ft_putchar('\n');
		return (SUCCESS);
	}
	return (ERROR);
}
