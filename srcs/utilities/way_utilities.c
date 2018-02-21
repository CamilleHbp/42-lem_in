/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:45 by briviere          #+#    #+#             */
/*   Updated: 2018/02/21 16:31:03 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	free_way(t_way *way)
{
	if (way->next)
		free_way(way->next);
	free(way);
}

size_t	way_len(t_way *way)
{
	if (way == 0)
		return (0);
	return (way_len(way->next) + 1);
}
