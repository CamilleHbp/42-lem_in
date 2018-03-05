/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:43:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 09:53:08 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdlib.h>
# include "libft.h"

# define FOUND				(int8_t)-2
# define ROOM				(int8_t)0
# define START				(int8_t)1
# define END				(int8_t)2

# define DEF_LINKS_ALLOC 	16

# define FLAG_INPUT			(uint8_t)1
# define FLAG_DEBUG			(uint8_t)2
# define FLAG_PATH			(uint8_t)3
# define FLAG_ANTS			(uint8_t)4

typedef struct		s_room
{
	char			*name;
	uint32_t		id;
	int8_t			type;
	int64_t			x;
	int64_t			y;
	uint8_t			visited;
	uint32_t		ant;
	struct s_room	**links;
	uint32_t		size_links;
	struct s_room	*prev;
}					t_room;

typedef struct		s_map
{
	t_room		**rooms;
	uint32_t	size_rooms;
	uint64_t	ways;
	int64_t		ants;
}					t_map;

typedef struct		s_way
{
	t_room			*room;
	struct s_way	*next;
	struct s_way	*prev;
	uint32_t		depth;
	uint32_t		ants;
}					t_way;

#endif
