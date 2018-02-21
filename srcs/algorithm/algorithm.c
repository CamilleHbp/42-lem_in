/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/21 17:21:29 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"


// NOTE POUR CAMILLE:
// j'ajoute dans la structure room in variable poss_way qui va me permettre de savoir combien de chemin son possible
// elle me permet de connaitre le nombre de chemin possible
// je fais une recursive qui va compter tous les chemins possibles et ensuite je decremente de 1 pour dire que j'ai fabrique 1 "chemin"

// FIXME: maybe this is one has a bug too
int8_t	build_way(t_way *way)
{
	t_room		*tmp;
	size_t		idx;
	int8_t		res;

	if (way == 0 || way->room == 0)
		return (ERROR);
	if (way->room->type == END)
		return (SUCCESS);
	if (way->room->full || way->room->poss_way == 0)
		return (ERROR);
	res = ERROR;
	way->room->poss_way -= 1;
	way->room->full = 1;
	idx = 0;
	while (idx < way->room->size_links)
	{
		tmp = way->room->links[idx];
		if ((tmp->full == 0 && tmp->poss_way > 0) || tmp->type == END)
		{
			if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
				return (ALLOC_FAIL);
			way->next->room = tmp;
			res = build_way(way->next);
			break ;
		}
		idx++;
	}
	way->room->full = 0;
	return (res);
}

t_way	**find_ways(const t_map *map)
{
	t_room	*start;
	t_way	**all_ways;
	size_t	ways;
	size_t	idx;

	start = get_start_room(map);
	if ((all_ways = ft_memalloc(sizeof(t_way *) * (start->poss_way + 1))) == 0)
		return (NULL);
	ways = start->poss_way;
	idx = 0;
	while (idx < ways)
	{
		all_ways[idx] = ft_memalloc(sizeof(t_way));
		all_ways[idx]->room = start;
		if (build_way(all_ways[idx]) == SUCCESS)
			idx++;
		else
		{
			free(all_ways[idx]);
			all_ways[idx] = 0;
			ways--;
		}
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
	printf("possible ways: %llu\n", room_count_poss_way(get_start_room(map), map->size_rooms));
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
