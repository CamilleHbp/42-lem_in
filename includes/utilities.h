/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:03:33 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/24 15:05:54 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

#include "lem_in.h"
#include "parsing.h"

/*
** map utilities
*/

int8_t	add_room(t_map *map, t_room *room);
void	free_map(t_map *map);
void	free_room(t_room *room);
void	init_input(t_input *input);
t_room	*init_room(void);

/*
** string utilities
*/

char	*rev_skip_number(char *s);
char	*rev_skip_whitespace(char *s);

/*
** room utilities
*/

t_room		*get_start_room(const t_map *map);
t_room		*get_end_room(const t_map *map);

/*
** way utilities
*/

void	clear_way(t_way *way);
void	free_way(t_way *way);
size_t	way_len(const t_way *way);
t_way	*dup_way(const t_way *way);

#endif
