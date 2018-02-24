/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:07:53 by briviere          #+#    #+#             */
/*   Updated: 2018/02/24 15:19:21 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

// TODO: recursive to move from the end
int8_t		do_move(t_way *way, int8_t *first)
{
	int8_t		res;

	if (!way || !way->next)
		return (ERROR);
	res = do_move(way->next, first);
	if (way->room->type == END || !way->room->full ||
			(way->next->room->full && way->next->room->type != END))
		return (res);
	way->room->full--;
	way->next->room->full++;
	if (!*first)
		ft_putchar(' ');
	ft_print("L%d-%s", way->room->name, way->next->room->name);
	*first = 0;
	return (SUCCESS);
}

int8_t		mv_ants(t_way **ways)
{
	size_t	i;
	int8_t	first;
	int8_t	has_moved;

	i = 0;
	first = 1;
	has_moved = 0;
	while (ways[i])
	{
		if (do_move(ways[i], &first) == SUCCESS)
		{
			first = 0;
			has_moved = 1;
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
