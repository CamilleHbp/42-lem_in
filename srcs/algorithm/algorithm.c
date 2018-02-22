/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 11:30:32 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int64_t	find_way(t_way *way)
{
	size_t		idx;

	if (way->room->full)
		return (ERROR);
	if (way->room->type == END)
		return (SUCCESS);
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (ALLOC_FAIL);
	idx = 0;
	way->room->full = 1;
	while (idx < way->room->size_links)
	{
		way->next->room = way->room->links[idx];
		if (find_way(way->next) == SUCCESS)
			return (SUCCESS);
		idx++;
	}
	way->room->full = 0;
	return (ERROR);
}

/* Logic:
**
** Dans cet exemple il y a deux chemins max. Sinon on lance une recursive par
** chenmin max possible.
**
** F1:
** On lance rec 1 et on sauve dans WA-1.
** F2:
** On lance rec 2 et on sauve dans WB-1.
**
** Si F2 retourne FALSE, on relance F1 avec une copie de WA-1 appelee WA-2.
** WA-2 est une copie de WA-1 avec ces differences:
**	- tant que les rooms ont un seul link, on revient en arriere.
**	- Des qu'on trouve une room avec plus d'un link, on set way a cette piece.
**	- La room next reste full, tout le reste de WA-1 est libere (full=0).
*/

t_way	**find_ways(const t_map *map)
{
	t_room	*start;
	t_way	**all_ways;
	size_t	idx;

	start = get_start_room(map);
	printf("nb links=%llu\n", start->size_links);
	if ((all_ways = ft_memalloc(sizeof(t_way *) * (start->size_links + 1))) == 0)
		return (NULL);
	idx = 0;
	while (idx < start->size_links)
	{
		all_ways[idx] = ft_memalloc(sizeof(t_way));
		all_ways[idx]->room = start;
		if (find_way(all_ways[idx]) == ERROR)
			; // TODO:
		idx++;
	}
	return (all_ways);
}

int8_t	solve_map(t_map *map)
{
	size_t	idx;
	t_way	**ways;
	t_way	*way;
	t_way	*tmp;

	// TODO: this is a temp test
	idx = 0;
	ways = find_ways(map);
	while (ways[idx])
	{
		way = ways[idx];
		tmp = way;
		printf("%lld %lld", way->room->x, way->room->y);
		way = way->next;
		while (way)
		{
			printf(" -> %lld %lld", way->room->x, way->room->y);
			way = way->next;
		}
		printf("\nlen=%zu\n", way_len(tmp));
		free_way(tmp);
		idx++;
	}
	free(ways);
	//save_way(way_array, way);
	return (SUCCESS);
}
