#include "../includes/cub3D_bonus.h"

static int	keycode_launcher(int keycode, t_game *game);
static int	launch_game(t_game *game);
static int	close_launcher(t_game *game);
int	create_launcher_images(t_game *game, char *prefix);

int	loop_animation(t_game *game)
{
	game->time = get_current_time();
	mlx_put_image_to_window(game->mlx, game->win, gollum(game), 0, 0);
	return (SUCCESS);
}

int	open_launcher(t_game *game)
{
	game->file = NULL;
	game->texture = NULL;
	game->map = NULL;
	struct_game_sound(game);
	game->launcher_animation = false;
	game->launcher_is_running = true;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D Launcher");
	if (!create_launcher_images(game, "textures/launcher/launcher"))
		return (FAILURE);
	if (game->launcher_is_running == true)
	{
		if (sound(game) == FAILURE)
			return (close_launcher(game));
		mlx_hook(game->win, KeyPress, KeyPressMask, keycode_launcher, game);
		mlx_hook(game->win, DestroyNotify, NoEventMask, close_launcher, game);
		mlx_loop_hook(game->mlx, loop_animation, game);
	}
	mlx_loop(game->mlx);
	return (SUCCESS);
}

static int	keycode_launcher(int keycode, t_game *game)
{
	if (keycode == LEFT)
	{
		game->file = "maps/moria_bonus.cub";
		free_gollum(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_moria"))
			return (FAILURE);
	}
	if (keycode == RIGHT)
	{
		game->file = "maps/morgul_bonus.cub";
		free_gollum(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_morgul"))
			return (FAILURE);
	}
	if (keycode == SPACE && game->file)
		if (launch_game(game) == FAILURE)
			close_game(game);
	if (keycode == ESC)
		close_launcher(game);
	if (keycode == R)
	{
		Mix_PlayChannel(-1, game->music->gollum, 0);
		game->launcher_animation = true;
		game->launcher_start_animation = get_current_time();
	}
	return (SUCCESS);
}

static int	launch_game(t_game *game)
{
	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		return (FAILURE);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (FAILURE);
	if (!parse_texture_and_map(&game->texture, &game->map, game->file, true))
		close_launcher(game);
	game->launcher_is_running = false;
	mlx_destroy_window(game->mlx, game->win);
	init_game(game, game->texture, game->map, true);
	get_map_type(game);
	if (start_game(game, true) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	close_launcher(t_game *game)
{
	free_gollum(game);
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

void	get_map_type(t_game *game)
{
	if (ft_strcmp(game->file, "maps/moria_bonus.cub") == 0 || \
		ft_strcmp(game->file, "maps/moria.cub") == 0)
		game->map_type = "moria";
	else
		game->map_type = "morgul";
}

int	create_launcher_images(t_game *game, char *prefix)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * 9);
	if (!tab)
		return (FAILURE);
	tab[0] = ft_strjoin(prefix, ".xpm");
	tab[1] = ft_strjoin(prefix, "(1).xpm");
	tab[2] = ft_strjoin(prefix, "(2).xpm");
	tab[3] = ft_strjoin(prefix, "(3).xpm");
	tab[4] = ft_strjoin(prefix, "(4).xpm");
	tab[5] = ft_strjoin(prefix, "(3).xpm");
	tab[6] = ft_strjoin(prefix, "(2).xpm");
	tab[7] = ft_strjoin(prefix, "(1).xpm");
	tab[8] = NULL;
	game->launcher_frames = 8;
	game->launcher = ft_calloc(sizeof(t_image), (game->launcher_frames + 1));
	if (!game->launcher)
		return (ft_free_tab(tab), FAILURE);
	i = -1;
	while (++i < game->launcher_frames)
		if (load_xpm(game, &game->launcher[i], tab[i]) == FAILURE)
			return (ft_free_tab(tab), FAILURE);
	return (ft_free_tab(tab), SUCCESS);
}
