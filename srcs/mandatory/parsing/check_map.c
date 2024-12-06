/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:08 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:09 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	get_size(t_map *map, int fd);
static void	create_line(t_map *map, char *line, int y, int fd);
static int	map_is_valid(t_map *map);

int	read_map(t_map *map, int fd)
{
	char	*line;
	int		y;

	if (get_size(map, fd) == FAILURE)
		return (FAILURE);
	if (map->start_read == false)
	{
		ft_fprintf(STDERR_FILENO, "Error: map is missing\n");
		return (FAILURE);
	}
	fd = open_map(map->file);
	line = get_next_line(fd);
	while (ft_strcmp(map->first_line, line) != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	map->lines = ft_calloc(sizeof(char *), map->y);
	y = 0;
	create_line(map, line, y, fd);
	while (++y < map->y)
		create_line(map, line, y, fd);
	if (map_is_valid(map) == FAILURE)
		return (close(fd), FAILURE);
	return (SUCCESS);
}

static int	get_size(t_map *map, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_iswhitespace(line) == (int)ft_strlen(line))
		{
			free(line);
			if (map->start_read == true)
				map->end_read = true;
			continue ;
		}
		if (map->end_read == true)
			return (free(line), ft_fprintf(STDERR_FILENO, ERR_EMPTY), FAILURE);
		if (map->start_read == false)
			map->first_line = ft_strdup(line);
		map->start_read = true;
		map->y++;
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

static void	create_line(t_map *map, char *line, int y, int fd)
{
	if (y != 0)
		line = get_next_line(fd);
	map->lines[y] = malloc(sizeof(t_line));
	map->lines[y]->content = ft_strdup(line);
	map->lines[y]->x = ft_strlen(line) - 1;
	free(line);
}

static int	map_is_valid(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->lines[y]->x)
		{
			if (char_is_valid(map->lines[y]->content[x]) == FAILURE)
				return (FAILURE);
			if (nb_start_pos(map, y, x) == FAILURE)
				return (FAILURE);
			if (check_walls(map, y, x) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
