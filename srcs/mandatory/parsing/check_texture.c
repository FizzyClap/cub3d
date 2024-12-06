/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:11 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:13 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	get_texture(t_texture *texture, char *line);
static int	right_order(t_texture *texture);
static int	path_texture(t_texture *texture, char *line);
static int	fill_path(t_texture *texture, char *line);

int	read_textures(t_texture *texture, char *file)
{
	char	*line;
	int		fd;

	fd = open_map(file);
	texture->order = NO_ORDER;
	while (1)
	{
		if (texture->order == DONE)
			break ;
		line = get_next_line(fd);
		if (texture->order != DONE && \
			ft_iswhitespace(line) == (int)ft_strlen(line))
		{
			free(line);
			continue ;
		}
		if (get_texture(texture, line) == FAILURE)
			return (free(line), close(fd), FAILURE);
		free(line);
	}
	return (fd);
}

static int	get_texture(t_texture *texture, char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line + i))
		i++;
	line += i;
	i = 0;
	while (!ft_iswhitespace(line + i))
		i++;
	texture->id = ft_strndup(line, i);
	if (right_order(texture) == FAILURE)
		return (FAILURE);
	if (path_texture(texture, line) == FAILURE)
		return (FAILURE);
	line += i + ft_iswhitespace(line + i);
	if (fill_path(texture, line) == FAILURE)
		return (FAILURE);
	free(texture->id);
	texture->id = NULL;
	return (SUCCESS);
}

static int	right_order(t_texture *texture)
{
	if (ft_strcmp(texture->id, "NO") == 0 && texture->order == NO_ORDER)
		texture->order = SO_ORDER;
	else if (ft_strcmp(texture->id, "SO") == 0 && texture->order == SO_ORDER)
		texture->order = WE_ORDER;
	else if (ft_strcmp(texture->id, "WE") == 0 && texture->order == WE_ORDER)
		texture->order = EA_ORDER;
	else if (ft_strcmp(texture->id, "EA") == 0 && texture->order == EA_ORDER)
		texture->order = F_ORDER;
	else if (ft_strcmp(texture->id, "F") == 0 && texture->order == F_ORDER)
		texture->order = C_ORDER;
	else if (ft_strcmp(texture->id, "C") == 0 && texture->order == C_ORDER)
		texture->order = DONE;
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: datas are not in the right order\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	path_texture(t_texture *texture, char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (len >= 0 && ft_char_iswhitespace(line[len]))
	{
		line[len] = '\0';
		len--;
	}
	if (texture->order != C_ORDER && texture->order != DONE)
	{
		len -= ft_iswhitespace(line + 2);
		if (check_len(len, 2, line) == FAILURE)
			return (FAILURE);
		line += 2 + ft_iswhitespace(line + 2);
		if (path_exist(line) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	len -= ft_iswhitespace(line + 1);
	if (check_len(len, 1, line) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	fill_path(t_texture *texture, char *line)
{
	if (ft_strcmp(texture->id, "NO") == 0)
		texture->north_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "SO") == 0)
		texture->south_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "WE") == 0)
		texture->west_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "EA") == 0)
		texture->east_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "F") == 0)
	{
		if (color_format(texture->id, line) == FAILURE)
			return (FAILURE);
		texture->floor_color = ft_strdup(line);
	}
	else if (ft_strcmp(texture->id, "C") == 0)
	{
		if (color_format(texture->id, line) == FAILURE)
			return (FAILURE);
		texture->ceiling_color = ft_strdup(line);
	}
	return (SUCCESS);
}
