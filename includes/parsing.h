/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 09:12:42 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/18 17:42:37 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lem_in.h"

# define INVALID	(int8_t)-1

typedef struct	s_input
{
	char	**lines;
	int32_t	nb_lines;
}				t_input;

int8_t			check_end_rooms(char *line);
int8_t			parse_map(t_map *map);
int8_t			parse_room(char *line, t_map *map, int8_t room_type);
int8_t			parse_type(char *cmd_line);
void			print_and_free_input(t_input input);
int8_t			save_line(char *line, t_input *input);

//debug
void	print_input(t_input input);
void	print_map(t_map map);

#endif
