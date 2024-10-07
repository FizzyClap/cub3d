/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:22:29 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:28:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	nb_start_pos(t_map *map, int y, int x)
{
	if (map->lines[y]->content[x] == 'N' || map->lines[y]->content[x] == 'S' \
		|| map->lines[y]->content[x] == 'W' || map->lines[y]->content[x] == 'E')
	{
		map->count_start_pos++;
		if (map->count_start_pos == 2)
		{
			ft_fprintf(2, "Error: There is too much start position\n");
			return (FAILURE);
		}
		map->start_x = x;
		map->start_y = y;
	}
	return (SUCCESS);
}

int	char_is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' \
		|| c == ' ' || (c >= '\t' && c <= '\r'))
		return (SUCCESS);
	ft_fprintf(STDERR_FILENO, "Error: %c is not a valid character\n", c);
	return (FAILURE);
}
