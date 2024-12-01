#include "../includes/cub3D_bonus.h"

static int	keycode_launcher(int keycode, t_game *game);
static void	launch_game(t_game *game);
static int	close_launcher(t_game *game);

int	open_launcher(t_game *game)
{
	game->file = NULL;
	game->texture = NULL;
	game->map = NULL;
	struct_game_sound(game);
	game->launcher_is_running = true;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D Launcher");
	if (load_xpm(game, &game->launcher, "textures/launcher.xpm") == FAILURE)
		return (FAILURE);
	mlx_put_image_to_window(game->mlx, game->win, game->launcher.img, 0, 0);
	if (game->launcher_is_running == true)
	{
		sound(game);
		mlx_hook(game->win, KeyPress, KeyPressMask, keycode_launcher, game);
		mlx_hook(game->win, DestroyNotify, NoEventMask, close_launcher, game);
	}
	mlx_loop(game->mlx);
	return (SUCCESS);
}

static int	keycode_launcher(int keycode, t_game *game)
{
	if (keycode == LEFT)
	{
		game->file = "maps/moria_bonus.cub";
		mlx_destroy_image(game->mlx, game->launcher.img);
		if (!load_xpm(game, &game->launcher, "textures/launcher_moria.xpm"))
			return (FAILURE);
		mlx_put_image_to_window(game->mlx, game->win, game->launcher.img, 0, 0);
	}
	if (keycode == RIGHT)
	{
		game->file = "maps/morgul_bonus.cub";
		mlx_destroy_image(game->mlx, game->launcher.img);
		if (!load_xpm(game, &game->launcher, "textures/launcher_morgul.xpm"))
			return (FAILURE);
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
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		return ;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return ;
	if (!parse_texture_and_map(&game->texture, &game->map, game->file, true))
		close_launcher(game);
	game->launcher_is_running = false;
	mlx_destroy_window(game->mlx, game->win);
	init_game(game, game->texture, game->map, true);
	start_game(game, true);
}

static int	close_launcher(t_game *game)
{
	if (game->launcher.img)
		mlx_destroy_image(game->mlx, game->launcher.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free(game->map);
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
}
