#include "../../includes/cub3D.h"

static void	file_format(char *file);

int	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		if (argc == 1)
			ft_fprintf(STDERR_FILENO, "Error: there is 1 argument missing\n");
		else if (argc == 3)
			ft_fprintf(2, "Error: there is 1 argument more than expected\n");
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
		ft_fprintf(STDERR_FILENO, "Error: file is not a \".cub\" extension\n");
	else if (len_file < 5)
		ft_fprintf(STDERR_FILENO, "Error: file has no name\n");
	else
		return ;
	exit(EXIT_FAILURE);
}

int	open_map(char *file)
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
