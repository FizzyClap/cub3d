/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:31 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:33 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, "cub3D");
	player_init(game);
	minimap(game);
	game->raycast.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
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

void	clear_image(char *address, int height, int width)
{
	int		*image_data;
	int		pixels;
	int		i;

	image_data = (int *)address;
	pixels = height * width;
	i = 0;
	while (i < pixels)
	{
		image_data[i] = 0x000000;
		i++;
	}
}

static int	loop(t_game *game, t_ray *ray)
{
	move_div(game);
	make_actions(game, ray);
	mouse_move(game);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->player.cursor.img, \
		118, 118);
	return (SUCCESS);
}
