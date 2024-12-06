/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:04 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	file_format(char *file);

int	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		if (argc == 1)
			ft_fprintf(STDERR_FILENO, "Error: there is 1 argument missing\n");
		else if (argc == 3)
			ft_fprintf(STDERR_FILENO, ERR_ARG);
		else
			ft_fprintf(STDERR_FILENO, "Error: there are %d arguments" \
			" more than expected\n", argc - 2);
		exit(EXIT_FAILURE);
	}
	file_format(argv[1]);
	open_map(argv[1]);
	return (SUCCESS);
}

static void	file_format(char *file)
{
	int	len_file;

	len_file = ft_strlen(file);
	if (ft_strcmp(file + len_file - 4, ".cub") != 0)
		ft_fprintf(2, "Error: %s is not a \".cub\" extension\n", file);
	else if (len_file < 5)
		ft_fprintf(STDERR_FILENO, "Error: %s has no name\n", file);
	else
		return ;
	exit(EXIT_FAILURE);
}

int	open_map(char *file)
{
	int		fd;
	int		bytes_read;
	char	buffer[1];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s : ", file);
		perror("");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(fd, buffer, 1);
	if (bytes_read <= 0)
	{
		if (bytes_read == -1)
			ft_fprintf(STDERR_FILENO, "Error: %s : Is a directory\n", file);
		else if (bytes_read == 0)
			ft_fprintf(STDERR_FILENO, "Error: %s : Is empty\n", file);
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	return (fd);
}
