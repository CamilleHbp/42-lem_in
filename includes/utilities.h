/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:03:33 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 15:42:10 by cbaillat         ###   ########.fr       */
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

#endif
