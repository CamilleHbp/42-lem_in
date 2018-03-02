/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:47:33 by briviere          #+#    #+#             */
/*   Updated: 2018/03/02 11:54:18 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error_manager.h"

static void		print_eof(int8_t status, uint8_t flags)
{
	if (flags & (1 << FLAG_DEBUG))
	{
		if (status == 0)
			ft_print("line 1: end of file\n");
		else
			perror("get_next_line");
	}
}

static void		print_eol(char *line, uint8_t flags)
{
	if (flags & (1 << FLAG_DEBUG) && *line == 0)
		ft_print("line 1: empty line\n");
	free(line);
}

static int8_t	is_invalid_int(char *line, uint8_t flags)
{
	int64_t	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isdigit(line[i])))
		{
			if (flags & (1 << FLAG_DEBUG))
				ft_print("line 1 col %d: not a digit\n", i - 1);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int64_t			get_ants(t_input *input, uint8_t flags)
{
	int8_t	status;
	char	*line;

	while ((status = get_next_line(0, &line)) > FILE_READ)
	{
		if (*line == '\0' || save_line(line, input) == ERROR)
		{
			print_eol(line, flags);
			return (error_parsing(input, NULL));
		}
		if (line[0] == '#')
			continue ;
		if (is_invalid_int(line, flags))
			return (error_parsing(input, NULL));
		return (ft_abs64(ft_atoi64(line)));
	}
	free(line);
	print_eof(status, flags);
	return (error_parsing(input, NULL));
}
