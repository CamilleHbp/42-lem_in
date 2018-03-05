/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:07:53 by briviere          #+#    #+#             */
/*   Updated: 2018/03/05 09:54:04 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

static void	ants_distribution(t_way **ways, uint32_t ants)
{
	uint32_t	max_depth;
	uint32_t	i;

	i = 0;
	max_depth = 0;
	while (ways[i])
		max_depth = ft_max(max_depth, ways[i++]->depth);
	i = 0;
	while (ways[i])
	{
		ways[i]->ants = max_depth - ways[i]->depth;
		ants -= ways[i++]->ants;
	}
	max_depth = ants / (!i ? 1 : i);
	i = 0;
	while (ways[i + 1])
	{
		ways[i++]->ants += max_depth;
		ants -= max_depth;
	}
	ways[i]->ants += ants;
}

static void	move_ants(t_way **ways)
{
	size_t	i;
	t_way	*end;

	i = 0;
	while (ways[i])
	{
		end = ways[i];
		while (end->next->next)
			end = end->next;
		while (end->prev)
		{
			if (end->room->ant)
			{
				end->next->room->ant = end->room->ant;
				end->room->ant = 0;
				ft_print("L%u-%s ", end->next->room->ant,
					end->next->room->name);
			}
			end = end->prev;
		}
		++i;
	}
}

static uint8_t	is_empty(t_way **ways)
{
	size_t	i;
	t_way	*way;

	i = 0;
	while (ways[i])
	{
		way = ways[i];
		while (way->next)
		{
			if (way->room->ant)
				return (0);
			way = way->next;
		}
		++i;
	}
	return (1);
}

void		mv_ants(t_way **ways, uint32_t ants)
{
	size_t		i;
	uint32_t	ant_factory;

	ants_distribution(ways, ants);
	ant_factory = 1;
	while (TRUE)
	{
		i = 0;
		move_ants(ways);
		while (ant_factory <= ants && ways[i])
		{
			if (ways[i]->ants)
				if (!ways[i]->next->room->ant)
				{
					ways[i]->next->room->ant = ant_factory++;
					ways[i]->ants -= 1;
					ft_print("L%u-%s ", ways[i]->next->room->ant,
						ways[i]->next->room->name);
				}
			++i;
		}
		ft_putchar('\n');
		if (is_empty(ways))
			break ;
	}
}
