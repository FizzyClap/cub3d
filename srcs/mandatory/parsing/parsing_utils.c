/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:21 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:22 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	path_exist(char *file)
{
	int	len_file;
	int	fd;

	len_file = ft_strlen(file);
	if (ft_strcmp(file + len_file - 4, ".xpm") != 0)
	{
		ft_fprintf(2, "Error: %s is not a \".xpm\" extension\n", file);
		return (FAILURE);
	}
	else if (len_file < 5)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s has no name\n", file);
		return (FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s : ", file);
		perror("");
		return (FAILURE);
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
	if (ft_strchr("10NSWE ", c) || (c >= '\t' && c <= '\r'))
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
