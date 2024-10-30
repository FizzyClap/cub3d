#include "../includes/cub3D.h"

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv);
static int	loop(t_game *game, t_ray *ray);

int	main(int argc, char **argv)
{
	t_texture	*texture;
	t_map		*map;
	t_game		*game;

	if (parsing(&texture, &map, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	init_game(&game, texture, map);
	game->mlx = mlx_init();
	if (load_textures(game) == FAILURE)
	{
		ft_fprintf(STDERR_FILENO, "Error: textures can't be loaded\n");
		close_game(game);
	}
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
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

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv)
{
	int	fd;

	if (check_arg(argc, argv) == FAILURE)
		return (FAILURE);
	*texture = malloc(sizeof(t_texture));
	init_texture(*texture);
	fd = read_textures(*texture, argv[1]);
	if (fd == FAILURE)
	{
		free_texture(*texture);
		return (FAILURE);
	}
	*map = malloc(sizeof(t_map));
	init_map(*map, argv[1]);
	if (read_map(*map, fd) == FAILURE)
	{
		free_texture(*texture);
		free_map(*map);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	clear_image(char *address, int height, int width, int color)
{
	int		*image_data;
	int		pixels;
	int		i;

	image_data = (int *)address;
	pixels = height * width;
	i = -1;
	while (++i < pixels)
		image_data[i] = color;
}

static int	loop(t_game *game, t_ray *ray)
{
	clear_image(game->raycast.addr, SCREEN_HEIGHT, SCREEN_WIDTH, game->floor.color);
	raycasting(ray, game);
	clear_image(game->minimap.addr, MMH, MMW, BLACK);
	draw_minimap(game, game->minimap);
	make_actions(game);
	mouse_move(game);
	jump(game);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 20, 20);
	mlx_put_image_to_window(game->mlx, game->win, game->player.cursor.img, \
		118, 118);
	return (SUCCESS);
}
