#include "../includes/cub3D.h"

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv);
void		start_game(t_game *game, bool launcher);
static int	loop(t_game *game, t_ray *ray);

int	main(int argc, char **argv)
{
	t_texture	*texture;
	t_map		*map;
	t_game		*game;

	if (parsing(&texture, &map, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	game = malloc(sizeof(t_game));
	if (argc == 1 && open_launcher(game) == FAILURE)
		return (EXIT_FAILURE);
	else if (argc == 2)
	{
		init_game(game, texture, map, false);
		game->file = argv[1];
		init_sound();
		start_game(game, false);
	}
	return (EXIT_SUCCESS);
}

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv)
{
	if (check_arg(argc, argv) == FAILURE)
		return (FAILURE);
	if (argc == 2)
		if (parse_texture_and_map(texture, map, argv[1], false) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	parse_texture_and_map(t_texture **texture, t_map **map, char *file, bool launcher)
{
	int	fd;

	if (launcher == false)
		*texture = malloc(sizeof(t_texture));
	if (!*texture)
		return (FAILURE);
	init_texture(*texture);
	fd = read_textures(*texture, file);
	if (fd == FAILURE)
	{
		free_texture(*texture);
		return (FAILURE);
	}
	if (launcher == false)
		*map = malloc(sizeof(t_map));
	if (!*map)
		return (FAILURE);
	init_map(*map, file);
	if (read_map(*map, fd) == FAILURE)
	{
		free_texture(*texture);
		free_map(*map);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	start_game(t_game *game, bool launcher)
{
	if (launcher == false)
		game->mlx = mlx_init();
	if (load_textures(game) == FAILURE)
	{
		ft_fprintf(STDERR_FILENO, "Error: textures can't be loaded\n");
		close_game(game);
	}
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	init_sound_effects(game);
	sound(game);
	player_init(game);
	minimap(game);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
	game->raycast.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->raycast.addr = mlx_get_data_addr(game->raycast.img, \
	&game->raycast.bpp, &game->raycast.line_len, &game->raycast.endian);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, keyrelease, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, keycode, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_loop(game->mlx);
}

static int	loop(t_game *game, t_ray *ray)
{
	game->time = get_current_time();
	move_div(game);
	make_actions(game, ray);
	mouse_move(game);
	jump(game);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->player.cursor.img, \
		118, 118);
	//mlx_put_image_to_window(game->mlx, game->win, game->balrog.img, 0, 0);
	return (SUCCESS);
}
