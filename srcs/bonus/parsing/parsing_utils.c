/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:10:40 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:18:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

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
	if (ft_strchr("NSWE", map->lines[y]->content[x]))
	{
		if (++map->count_start_pos == 2)
		{
			ft_fprintf(STDERR_FILENO, ERR_PLAYERS);
			return (FAILURE);
		}
		map->start_x = x;
		map->start_y = y;
		map->orientation = map->lines[y]->content[x];
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
	if (ft_strchr("10NSWEDA ", c) || (c >= '\t' && c <= '\r'))
		return (SUCCESS);
	ft_fprintf(STDERR_FILENO, "Error: %c is not a valid character\n", c);
	return (FAILURE);
}

int	check_len(int len, int min, char *line)
{
	if (len <= min)
	{
		ft_fprintf(STDERR_FILENO, "Error: path for %s is missing\n", line);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	is_textured(t_texture *texture, char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line + i))
		i++;
	line += i;
	if (!ft_isdigit(line[0]))
	{
		if (ft_strcmp(texture->id, "F") == 0)
			texture->f_textured = true;
		if (ft_strcmp(texture->id, "C") == 0)
			texture->c_textured = true;
	}
}
