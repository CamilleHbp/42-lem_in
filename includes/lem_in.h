/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:43:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/15 14:01:30 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdlib.h>
# include "libft.h"

# define ROOM	(int8_t)-2
# define START	(int8_t)-1
# define END	(int8_t)0

struct s_room;

typedef struct	s_room
{
	char			*name;
	int8_t			type;
	int32_t			x;
	int32_t			y;
	struct s_room	**links;
	int32_t			size_links;
}				t_room;

typedef struct	s_map
{
	t_room	**rooms;
	int32_t	size_rooms;
	int32_t	*ways;
	int64_t	ants;
}				t_map;

#endif
