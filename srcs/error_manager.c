/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:59:14 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/16 13:36:04 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"
#include "utilities.h"

int8_t	error_parsing(t_input input, t_map *map)
{
	while (input.nb_lines >= 0)
	{
		input.nb_lines -= 1;
		free(input.lines[input.nb_lines]);
	}
	if (input.lines)
		free(input.lines);
	if (map)
		free_map(map);
	return (ERROR);
}
