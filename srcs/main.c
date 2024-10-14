#include "../includes/cub3D.h"

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv);

int	main(int argc, char **argv)
{
	t_texture	*texture;
	t_map		*map;
	t_game		*game;

	if (parsing(&texture, &map, argc, argv) == FAILURE)
		return (1);
	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D LOTR");
	//mlx_hook(game->win, 2, 1L << 0, keycode, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
	close_game(game);
}

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv)
{
	int	fd;

	if (check_arg(argc, argv) == FAILURE)
		return (FAILURE);
	*texture = malloc(sizeof(t_texture));
	init_texture(*texture);
	fd = read_textures(*texture, argv[1]);
	if (fd == FAILURE)
		return (free_texture(*texture), FAILURE);
	*map = malloc(sizeof(t_map));
	init_map(*map, argv[1]);
	if (read_map(*map, fd) == FAILURE)
		return (free_texture(*texture), free_map(*map), FAILURE);
	return (SUCCESS);
}
