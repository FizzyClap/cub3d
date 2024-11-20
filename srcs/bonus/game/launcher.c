#include "../includes/cub3D.h"

static int	keycode_launcher(int keycode, t_game *game);
static void	launch_game(t_game *game);
static int	close_launcher(t_game *game);

int	open_launcher(t_game *game)
{
	int	width;
	int	height;

	game->file = NULL;
	struct_game_sound(game);
	game->launcher_is_running = true;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D Launcher");
	game->launcher.img = mlx_xpm_file_to_image(game->mlx, "textures/launcher.xpm", &width, &height);
	mlx_put_image_to_window(game->mlx, game->win, game->launcher.img, 0, 0);
	if (game->launcher_is_running == true)
	{
		init_sound();
		sound(game);
		mlx_hook(game->win, KeyPress, KeyPressMask, keycode_launcher, game);
		mlx_hook(game->win, DestroyNotify, NoEventMask, close_launcher, game);
	}
	mlx_loop(game->mlx);
	return (SUCCESS);
}

static int	keycode_launcher(int keycode, t_game *game)
{
	int	width;
	int	height;

	if (keycode == LEFT)
	{
		game->file = "maps/moria.cub";
		mlx_destroy_image(game->mlx, game->launcher.img);
		game->launcher.img = mlx_xpm_file_to_image(game->mlx, "textures/launcher_moria.xpm", &width, &height);
		mlx_put_image_to_window(game->mlx, game->win, game->launcher.img, 0, 0);
	}
	if (keycode == RIGHT)
	{
		game->file = "maps/morgul.cub";
		mlx_destroy_image(game->mlx, game->launcher.img);
		game->launcher.img = mlx_xpm_file_to_image(game->mlx, "textures/launcher_morgul.xpm", &width, &height);
		mlx_put_image_to_window(game->mlx, game->win, game->launcher.img, 0, 0);
	}
	if (keycode == SPACE && game->file)
		launch_game(game);
	if (keycode == ESC)
		close_launcher(game);
	return (SUCCESS);
}

static void	launch_game(t_game *game)
{
	int	width;
	int	height;

	mlx_destroy_image(game->mlx, game->launcher.img);
	game->texture = malloc(sizeof(t_texture));
	game->map = malloc(sizeof(t_map));
	game->select = mlx_xpm_file_to_image(game->mlx, game->file, &width, &height);
	if (parse_texture_and_map(&game->texture, &game->map, game->file, true) == FAILURE)
		close_launcher(game);
	game->launcher_is_running = false;
	mlx_destroy_window(game->mlx, game->win);
	init_game(game, game->texture, game->map, true);
	start_game(game, true);
}

static int	close_launcher(t_game *game)
{
	mlx_destroy_image(game->mlx, game->launcher.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}
