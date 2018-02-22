/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 13:40:21 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

int64_t	find_shortest_way(t_way *way, int64_t depth)
{
	size_t	idx;
	t_way	*way_sh;
	size_t	way_sh_len;
	t_way	*way_tmp;
	size_t	way_tmp_len;

	if (way->room->type == END)
		return (1);
	if (depth == 0)
		return (ERROR);
	if (way->room->full)
		return (ERROR);
	way_sh = 0;
	way_sh_len = (size_t)-1;
	idx = 0;
	way->room->full = 1;
	while (idx < way->room->size_links)
	{
		if ((way_tmp = ft_memalloc(sizeof(t_way))) == 0)
			return (ALLOC_FAIL);
		way_tmp->room = way->room->links[idx];
		way_tmp_len = find_shortest_way(way_tmp, (depth < 0 ? -1 : depth - 1));
		if (way_tmp_len > 0 && way_tmp && (way_tmp_len < way_sh_len || way_sh_len == (size_t)-1))
		{
			free_way(way_sh);
			way_sh = way_tmp;
			way_sh_len = way_tmp_len;
		}
		else
			free_way(way_tmp);
		idx++;
	}
	way->next = way_sh;
	if (way_sh == 0)
	{
		way->room->full = 0;
		return (ERROR);
	}
	return (way_sh_len + 1);
}

// TODO: not my problem
//t_way	**find_ways(const t_map *map)
//{
//	t_room	*start;
//	t_way	**all_ways;
//	size_t	idx;
//	size_t	prev_deep;
//
//	start = get_start_room(map);
//	ft_print("nb links=%d\n", start->size_links);
//	if ((all_ways = ft_memalloc(sizeof(t_way *) * (start->size_links + 1))) == 0)
//		return (NULL);
//	idx = 0;
//	while (idx < start->size_links)
//	{
//		all_ways[idx] = ft_memalloc(sizeof(t_way));
//		all_ways[idx]->room = start;
//		if (build_way(all_ways[idx]) == ERROR)
//			; // TODO: idx - 1 and call rebuild way
//		idx++;
//	}
//	return (all_ways);
//}

// debug ?
void	print_way(t_way *way)
{
	if (way == 0)
		return ;
	ft_print("%d %d", way->room->x, way->room->y);
	way = way->next;
	while (way)
	{
		ft_print(" -> %d %d", way->room->x, way->room->y);
		way = way->next;
	}
	ft_print("\n");
}

int8_t	solve_map(t_map *map)
{
	//size_t	idx;
	//t_way	**ways;
	//t_way	*way;
	//t_way	*tmp;
	t_way	*way;

	way = ft_memalloc(sizeof(t_way));
	way->room = get_start_room(map);
	ft_print("%d\n", find_shortest_way(way, -1));
	print_way(way);
	free_way(way);
	// TODO: this is a temp test
	//idx = 0;
	//ways = find_ways(map);
	//while (ways[idx])
	//{
	//	way = ways[idx];
	//	tmp = way;
	//	free_way(tmp);
	//	idx++;
	//}
	//free(ways);
	//save_way(way_array, way);
	return (SUCCESS);
}
