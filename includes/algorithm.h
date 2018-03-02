/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 09:12:48 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 14:15:46 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_H
# define ALGORITHM_H

# include "lem_in.h"

t_way	*breadth_first_search(t_map *map, t_room *room);
int8_t	depth_first_seach(t_way *way, int64_t depth);
t_way	**edmonds_karp(t_map *map);
t_way	***find_da_wae(t_map *map);
void	mv_ants(t_way **ways, uint32_t ants);
t_way	**solve_map(t_map *map);

#endif
