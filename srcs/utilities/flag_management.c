/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 07:26:14 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/05 09:39:13 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

uint8_t	is_flag(char *str)
{
	uint8_t	flags;

	flags = 0;
	if (!ft_strcmp(str, "-a"))
		flags |= 1 << FLAG_ANTS;
	else if (!ft_strcmp(str, "-i"))
		flags |= 1 << FLAG_INPUT;
	else if (!ft_strcmp(str, "-p"))
		flags |= 1 << FLAG_PATH;
	else if (!ft_strcmp(str, "-d"))
		flags |= 1 << FLAG_DEBUG;
	return (flags);
}
