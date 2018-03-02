/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:03:33 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 11:01:44 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "lem_in.h"
# include "parsing.h"

# define ROOM_ALLOC	1000
# define LINE_ALLOC	1000


/*
** print utilities
*/

void	print_input(t_input input);
void	print_way(t_way *way);
void	print_ways(t_way **ways);

/*
** map utilities
*/

void	free_map(t_map *map);
t_room	*get_end_room(const t_map *map);
t_room	*get_room_by_id(t_map	*map, uint64_t id);
t_room	*get_start_room(const t_map *map);
void	init_map(t_map *map);

/*
** path utilities
*/

t_way	*build_way_from_path(int64_t *path, t_map *map);
int64_t	*init_path(uint32_t map_size);

/*
** room utilities
*/

int8_t	add_room(t_map *map, t_room *room);
void	free_room(t_room *room);
t_room	*init_room(void);

/*
** string utilities
*/

void	init_input(t_input *input);
char	*rev_skip_number(char *s);
char	*rev_skip_whitespace(char *s);

/*
** way utilities
*/

void	clear_way(t_way *way);
t_way	*dup_way(const t_way *way);
void	free_way(t_way *way);
int8_t	is_valid_way(t_way *way);
size_t	way_len(const t_way *way);

#endif
