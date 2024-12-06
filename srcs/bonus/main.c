/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:11:02 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:11:04 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	parsing(t_texture **texture, t_map **map, int argc, char **argv);
static int	loop(t_game *game);

int	main(int argc, char **argv)
{
	t_texture	*texture;
	t_map		*map;
	t_game		*game;

	if (parsing(&texture, &map, argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	init_sound();
	if (argc == 1 && open_launcher(game) == FAILURE)
		return (EXIT_FAILURE);
	else if (argc == 2)
	{
		init_game(game, texture, map, false);
		game->file = argv[1];
		get_map_type(game);
		if (start_game(game, false) == FAILURE)
			return (close_game(game), EXIT_FAILURE);
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

int	parse_texture_and_map(t_texture **texture, t_map **map, char *file,
	bool launcher)
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

int	start_game(t_game *game, bool launcher)
{
	if (launcher == false)
		game->mlx = mlx_init();
	if (load_textures(game) == FAILURE)
	{
		ft_fprintf(STDERR_FILENO, "Error: textures can't be loaded\n");
		close_game(game);
	}
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "cub3D");
	if (sound(game) == FAILURE || init_sound_effects(game) == FAILURE)
		return (FAILURE);
	mlx_mouse_move(game->mlx, game->win, 960, 540);
	player_init(game);
	minimap(game);
	game->raycast.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->raycast.addr = mlx_get_data_addr(game->raycast.img, \
	&game->raycast.bpp, &game->raycast.line_len, &game->raycast.endian);
	mlx_hook(game->win, ButtonPress, ButtonPressMask, mouse_game, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, keyrelease, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, keycode, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_loop(game->mlx);
	return (SUCCESS);
}

static int	loop(t_game *game)
{
	int	x;
	int	y;

	game->time = get_current_time();
	if ((long long)(game->time * 1000) - \
		(long long)(game->old_time * 1000) > 15)
	{
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
		raycasting(game);
		move_div(game);
		make_actions(game);
		mouse_move(game);
		mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
		my_put_image(game, &game->ring, -40, -35);
		my_put_image(game, weapon_animation(game), 0, 0);
		mlx_put_image_to_window(game->mlx, game->win, game->player.cursor.img, \
			118, 118);
		game->time = get_current_time();
		game->old_time = get_current_time();
	}
	return (SUCCESS);
}
