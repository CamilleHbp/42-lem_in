/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:11:03 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/15 16:24:12 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int8_t	save_line(char *line, t_input *input)
{
	int32_t	nb_lines;

	nb_lines = input->nb_lines;
	if (!(input->lines = ft_realloc(input->lines,
										sizeof(char*) * nb_lines,
										sizeof(char*) * (nb_lines + 1))))
	{
		free(line);
		return (ERROR);
	}
	input->lines[nb_lines] = line;
	input->nb_lines += 1;
	return (SUCCESS);
}

void	print_and_free_input(t_input input)
{
	int32_t	i;

	i = 0;
	while (i < input.nb_lines)
	{
		ft_print("%s\n", input.lines[i]);
		free(input.lines[i]);
		++i;
	}
	free(input.lines);
}

//debug
void	print_input(t_input input)
{
	int32_t	i;

	i = 0;
	while (i < input.nb_lines)
	{
		ft_print("%s\n", input.lines[i]);
		++i;
	}
}
