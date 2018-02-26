/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:11:03 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/26 09:04:17 by cbaillat         ###   ########.fr       */
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
	if (input.lines)
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

//debug
void	print_map(t_map map)
{
	uint64_t	i;

	i = 0;
	while (i < map.size_rooms)
	{
		print_room(*(map.rooms[i]));
		ft_print("Matrix: \n%b\n", map.adj_matrix[i]);
		++i;
	}
}

//debug
void	print_room(t_room room)
{
	ft_print("------------\nROOM\n");
	ft_print("Name: %s\n", room.name);
	ft_print("ID: %d\n", room.id);
	if (room.type == ROOM)
		ft_print("Type: room\n");
	else if (room.type == START)
		ft_print("Type: start\n");
	else if (room.type == END)
		ft_print("Type: end\n");
	else
		ft_print("Type: *unkown*\n");
	ft_print("X: %d\n", (int64_t)room.x);
	ft_print("Y: %d\n", (int64_t)room.y);
}

//debug
void	print_reverse_way(t_room *end)
{
	ft_print("------------\nReverse Way\n");
	while (end->prev)
	{
		ft_print("%s <- %s\n", end->name, end->prev->name);
		end = end->prev;
	}
}
