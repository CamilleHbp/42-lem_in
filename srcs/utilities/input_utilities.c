/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:44:01 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/02 17:09:49 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utilities.h"

int8_t	save_line(char *line, t_input *input)
{
	static uint64_t	i;
	int32_t			nb_lines;

	nb_lines = input->nb_lines;
	if (!(i % LINE_ALLOC))
	{
		if (!(input->lines = ft_realloc(input->lines,
										sizeof(char*) * i,
										sizeof(char*) * (i + LINE_ALLOC))))
		{
			free(line);
			return (ERROR);
		}
	}
	input->lines[nb_lines] = line;
	input->nb_lines += 1;
	++i;
	return (SUCCESS);
}

void	free_input(t_input input)
{
	size_t	i;

	i = 0;
	while ((int32_t)i < input.nb_lines)
		free(input.lines[i++]);
	free(input.lines);
}
