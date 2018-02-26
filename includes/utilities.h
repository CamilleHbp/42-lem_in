/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:03:33 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/26 13:54:38 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "lem_in.h"
# include "parsing.h"

# define ROOM_ALLOC	1000
# define LINE_ALLOC	1000
/*
** map utilities
*/

void	free_map(t_map *map);
t_room	*get_end_room(const t_map *map);
t_room	*get_room_by_id(t_map	*map, uint64_t id);
t_room	*get_start_room(const t_map *map);
void	init_map(t_map *map);

/*
** string utilities
*/

void	init_input(t_input *input);
char	*rev_skip_number(char *s);
char	*rev_skip_whitespace(char *s);

/*
** room utilities
*/

int8_t	add_room(t_map *map, t_room *room);
void	free_room(t_room *room);
t_room	*init_room(void);

/*
** way utilities
*/

void	clear_way(t_way *way);
t_way	*dup_way(const t_way *way);
void	free_way(t_way *way);
int8_t	is_valid_way(t_way *way);
size_t	way_len(const t_way *way);

#endif
