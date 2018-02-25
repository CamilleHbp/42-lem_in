/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 09:12:48 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/25 10:23:06 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_H
# define ALGORITHM_H

# include "lem_in.h"

int8_t	breadth_first_search(t_map *map, t_way *way);
int8_t	depth_first_seach(t_way *way, int64_t depth);
int8_t	mv_ants(t_way **ways);
int8_t	solve_map(t_map *map);

#endif
