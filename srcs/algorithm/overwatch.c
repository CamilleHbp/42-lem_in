/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:00:09 by cbaillat          #+#    #+#             */
/*   Updated: 2018/02/22 18:28:52 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

/* Logic:
**
** WARNING: cette technique risque de prendre un temps extremement long si
** les chemins possibles sont nombreux. Peut etre prevoir un nombre de recursions
** maximum ?
**
** Dans cet exemple il y a trois chemins max. Sinon on lance une recursive par
** chemin max possible.
**
** On fait un tableau en 2d.
** way[0] => meilleur chemin pour 1 seul chemin
** way[1] => tableau des 2 meilleur chemins possibles qui fonctionnent ensemble
** way[2] => tableau des 3 meilleur chemins possibles qui fonctionnent ensemble
**
** On lance la recursive pour recuperer le meilleur chemin. Si on ne trouve pas,
** la carte est fausse, on imprime 'error'.
**
** Si on trouve le chemin le plus rapide, on revient dans la fonction principale
** On copie le chemin le plus rapide dans l'index way[1][0] et on lance la
** recursive pour trouver un autre chemin vers END.
** Si on trouve c'est cool, sinon on backtrack sur le premier way et on relance
** la recursive. Ainsi de suite. Si on ne trouve rien alors le seul chemin possibl
** est celui sauvegarde dans l'index way[0].
**
** On procede de meme
**
** CE QUI SUIT EST OBSOLETE UN EXEMPLE DE CE QUI POURRAIT SE PASSER DANS LE
** BACKTRACK
**
** F1:
** On a deja le chemin le plus court dans way[1][0]
** F2:
** On lance rec 2 et on sauve dans way[1][1].
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
