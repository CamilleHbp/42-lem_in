/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:41:58 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 17:15:08 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "utilities.h"

//int64_t	find_shortest_way(t_way *way, int64_t depth)
//{
//	size_t	i;
//	t_way	*way_sh;
//	int64_t	way_sh_len;
//	t_way	*way_tmp;
//	int64_t	way_tmp_len;
//
//	if (way->room->type == END)
//		return (1);
//	if (way->room->full || depth == 0)
//		return (ERROR);
//	way_sh = 0;
//	way_sh_len = depth;
//	i = 0;
//	way->room->full = 1;
//	while (i < way->room->size_links)
//	{
//		if ((way_tmp = ft_memalloc(sizeof(t_way))) == 0)
//			return (ALLOC_FAIL);
//		way_tmp->room = way->room->links[i];
//		way_tmp_len = find_shortest_way(way_tmp, way_sh_len - 1);
//		if (way_tmp_len > 0 && way_tmp && (way_tmp_len < way_sh_len || way_sh_len < 0))
//		{
//			free_way(way_sh);
//			way_sh = way_tmp;
//			way_sh_len = way_tmp_len;
//		}
//		else
//			free_way(way_tmp);
//		i++;
//	}
//	way->next = way_sh;
//	if (!way_sh || way_sh_len <= 0)
//	{
//		way->room->full = 0;
//		return (ERROR);
//	}
//	return (way_sh_len + 1);
//}

int64_t		find_way_depth(t_way *way, int64_t depth)
{
	size_t	i;

	if (way->room->type == END)
		return (SUCCESS);
	if (way->room->full || depth == 0)
		return (ERROR);
	i = 0;
	if ((way->next = ft_memalloc(sizeof(t_way))) == 0)
		return (ALLOC_FAIL);
	way->room->full = 1;
	while (i < way->room->size_links)
	{
		way->next->room = way->room->links[i];
		if (find_way_depth(way->next, depth - 1) == SUCCESS)
			return (SUCCESS);
		i++;
	}
	way->room->full = 0;
	way->next->room = 0;
	free(way->next);
	way->next = 0;
	return (ERROR);
}

// TODO: not my problem
//t_way	**find_ways(const t_map *map)
//{
//	t_room	*start;
//	t_way	**all_ways;
//	size_t	i;
//	size_t	prev_deep;
//
//	start = get_start_room(map);
//	ft_print("nb links=%d\n", start->size_links);
//	if ((all_ways = ft_memalloc(sizeof(t_way *) * (start->size_links + 1))) == 0)
//		return (NULL);
//	i = 0;
//	while (i < start->size_links)
//	{
//		all_ways[i] = ft_memalloc(sizeof(t_way));
//		all_ways[i]->room = start;
//		if (build_way(all_ways[i]) == ERROR)
//			; // TODO: i - 1 and call rebuild way
//		i++;
//	}
//	return (all_ways);
//}

// debug ?
void	print_way(t_way *way)
{
	if (!way)
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
	//size_t	i;
	//t_way	**ways;
	//t_way	*way;
	//t_way	*tmp;
	t_way	*way;
	int64_t	depth;

	way = ft_memalloc(sizeof(t_way));
	way->room = get_start_room(map);
	depth = 1;
	ft_print("links=%d\n", way->room->size_links);
	while (find_way_depth(way, depth) != SUCCESS)
	{
		depth++;
		ft_print("depth: %d\n", depth);
	}
	print_way(way);
	free_way(way);
	// TODO: this is a temp test
	//i = 0;
	//ways = find_ways(map);
	//while (ways[i])
	//{
	//	way = ways[i];
	//	tmp = way;
	//	free_way(tmp);
	//	i++;
	//}
	//free(ways);
	//save_way(way_array, way);
	return (SUCCESS);
}
