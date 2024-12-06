/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:38 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:39 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	keycode_launcher(int keycode, t_game *game);
static int	launch_game(t_game *game);
static int	loop_launcher(t_game *game);

int	open_launcher(t_game *game)
{
	game->file = NULL;
	game->texture = NULL;
	game->map = NULL;
	game->launcher_animation = false;
	game->launcher_is_running = true;
	init_struct_game_sound(game);
	game->launcher_start_animation = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "Cub3D Launcher");
	if (!create_launcher_images(game, "textures/launcher/launcher"))
		return (FAILURE);
	if (game->launcher_is_running == true)
	{
		if (sound(game) == FAILURE)
			return (close_launcher(game));
		mlx_hook(game->win, KeyPress, KeyPressMask, keycode_launcher, game);
		mlx_hook(game->win, ButtonPress, ButtonPressMask, mouse_click, game);
		mlx_hook(game->win, DestroyNotify, NoEventMask, close_launcher, game);
		mlx_loop_hook(game->mlx, loop_launcher, game);
	}
	mlx_loop(game->mlx);
	return (SUCCESS);
}

static int	keycode_launcher(int keycode, t_game *game)
{
	if (keycode == LEFT)
	{
		game->file = "maps/moria_bonus.cub";
		free_launcher_image(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_moria"))
			return (FAILURE);
	}
	if (keycode == RIGHT)
	{
		game->file = "maps/morgul_bonus.cub";
		free_launcher_image(game);
		if (!create_launcher_images(game, "textures/launcher/launcher_morgul"))
			return (FAILURE);
	}
	if (keycode == SPACE && game->file)
		if (launch_game(game) == FAILURE)
			close_game(game);
	if (keycode == ESC)
		close_launcher(game);
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
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	mlx_destroy_window(game->mlx, game->win);
	init_game(game, game->texture, game->map, true);
	get_map_type(game);
	if (start_game(game, true) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	loop_launcher(t_game *game)
{
	if (game->show_gollum && !Mix_Playing(-1))
	{
		game->nb_gollum++;
		game->show_gollum = false;
		Mix_PlayChannel(-1, game->music->gollum, 0);
		game->launcher_animation = true;
		game->launcher_start_animation = get_current_time();
	}
	if (game->nb_gollum == 3 && !Mix_Playing(-1))
	{
		game->nb_gollum = 1;
		Mix_HaltMusic();
		Mix_PlayMusic(game->music->gollum_song, 0);
		game->gollum_time = get_current_time();
		game->restart_music = true;
	}
	game->time = get_current_time();
	if (game->time - game->gollum_time >= 12 && game->restart_music == true)
	{
		Mix_PlayMusic(game->music->launcher, -1);
		game->restart_music = false;
	}
	mlx_put_image_to_window(game->mlx, game->win, gollum(game), 0, 0);
	return (SUCCESS);
}

void	get_map_type(t_game *game)
{
	if (ft_strcmp(game->file, "maps/moria_bonus.cub") == 0 || \
		ft_strcmp(game->file, "maps/moria.cub") == 0)
	{
		game->map_type = "moria";
		game->minimap_floor.a = 0x808080;
		game->minimap_wall.a = 0x000001;
	}
	else
	{
		game->map_type = "morgul";
		game->minimap_floor.a = 0x000001;
		game->minimap_wall.a = 0x5FCBB1;
	}
}
