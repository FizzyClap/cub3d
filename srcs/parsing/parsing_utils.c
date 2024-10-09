/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:50:54 by roespici          #+#    #+#             */
/*   Updated: 2024/10/09 16:23:20 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s : ", file);
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	color_format(char *id, char *line)
{
	int	i;
	int	count_comma;

	i = -1;
	count_comma = 0;
	while (line[++i])
	{
		if (line[i] == ',' && i == 0)
			return (ft_fprintf(2, "Error: %s color bad format\n", id), FAILURE);
		while (ft_char_iswhitespace(line[i]))
			i++;
		if (ft_atoi(line + i) > 255 || !ft_strisnum(line + i))
			return (ft_fprintf(2, "Error: %s color bad format\n", id), FAILURE);
		while (line[i] && (line[i] >= '0' && line[i] <= '9'))
			i++;
		if (line[i] == ',')
		{
			if (++count_comma == 3 || !line[i + 1])
			{
				ft_fprintf(2, "Error: %s color bad format\n", id);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

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
	if (y == map->y - 1 && x == map->lines[y]->x - 1 && !map->count_start_pos)
	{
		ft_fprintf(STDERR_FILENO, "Error: there is no start position\n");
		return (FAILURE);
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
