/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:00:09 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 16:37:58 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

/* Logic:
**
** Dans cet exemple il y a deux chemins max. Sinon on lance une recursive par
** chenmin max possible.
**
** F1:
** On lance rec 1 et on sauve dans WA-1.
** F2:
** On lance rec 2 et on sauve dans WB-1.
**
** Si F2 retourne FALSE, on relance F1 avec une copie de WA-1 appelee WA-2.
** WA-2 est une copie de WA-1 avec ces differences:
**	- tant que les rooms ont un seul link, on revient en arriere.
**	- Des qu'on trouve une room avec plus d'un link, on set way a cette piece.
**	- La room next reste full, tout le reste de WA-1 est libere (full=0).
**
** On trouve le chemin le plus court pour F1. Si il est bon, on cherche un
** chemin de longueur identique, et on incremente si on ne trouve pas.
**
*/

t_way	**init_2darray(int64_t nb_ways)
{
	t_way	***ways;
	int64_t	i;

	if (!(ways = ft_memalloc(sizeof(t_way **) * nb_ways)))
		return (NULL);
	i = 0;
	while (i < ways)
		if (!(ways[i] = ft_memalloc(sizeof(t_way *) * (i + 1))))
			return (error_overwatch(nb_ways, ways));
	return (ways);
}

t_way	**find_all_ways_from_room(t_way *way)
{

}

t_way	***find_me_da_weay(const t_map *map)
{
	t_room	*start;
	t_way	***ways;
	size_t	way;
	size_t	way_array;

	start = get_start_room(map);
	ft_print("nb ways=%u\n", map->ways);

	if (!(ways = init_2darray(map->ways)))
		return (NULL);

	// maintenant que le chemin le plus court est trouvé, on tente de trouve le
	// reste des chemins.
	// Si on fail pour le chemin N, on revient au chemin N-1 et on copie le
	// chemin jusqu'à ce que les rooms aient plusieurs links.
	way_array = 0;
	while (way < map->ways)
	{
		way = 0;
		while (way <= way_array)
		{
			if (!(ways[way_array][way] = ft_memalloc(sizeof(t_way))))
				return (error_overwatch(map->ways, ways));
			ways[way_array][way]->room = start;
			if (find_way(ways[way_array][way], depth) == ERROR)
			{
				// si on
				if (way == 0)
					return (ways);
				else
				{
					free_way(ways[way_array][way]);
					--way_array;
					backtrack_way(ways[way_array][way_array]);
				}
			}
			way++;
		}
		++way_array;
	}
	return (ways);
}
