/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:31 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:32 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	load_walls(t_game *game);
static int	load_doors(t_game *game, char **map);
static int	load_game_over(t_game *game);

int	load_textures(t_game *game)
{
	static char	**map = NULL;

	if (!load_walls(game) || !init_weapon(game) || !load_game_over(game))
		return (FAILURE);
	if (ft_strcmp(game->map_type, "moria") == 0)
	{
		if (init_enemy(game, "textures/enemy/dwarf") == FAILURE)
			return (FAILURE);
		map = create_moria_tab(game);
		if (!map)
			return (FAILURE);
	}
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		if (init_enemy(game, "textures/enemy/nazgul") == FAILURE)
			return (FAILURE);
		map = create_morgul_tab(game);
		if (!map)
			return (FAILURE);
	}
	if (map && load_doors(game, map) == FAILURE)
		return (FAILURE);
	if (load_xpm(game, &game->ring, "textures/ring.xpm") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	load_walls(t_game *game)
{
	int		i;
	char	*file[4];

	file[NORTH] = game->texture->north_path;
	file[SOUTH] = game->texture->south_path;
	file[WEST] = game->texture->west_path;
	file[EAST] = game->texture->east_path;
	i = -1;
	while (++i < 4)
		if (load_xpm(game, &game->texture->image[i], file[i]) == FAILURE)
			return (FAILURE);
	if (game->texture->f_textured == true)
		if (!load_xpm(game, &game->floor_txt, game->texture->floor_color))
			return (FAILURE);
	if (game->texture->c_textured == true)
		if (!load_xpm(game, &game->ceil_txt, game->texture->ceiling_color))
			return (FAILURE);
	return (SUCCESS);
}

static int	load_doors(t_game *game, char **map)
{
	int	i;

	game->door = ft_calloc(sizeof(t_image), game->doors_frames);
	if (!game->door)
		return (FAILURE);
	i = -1;
	while (++i < game->doors_frames)
		if (load_xpm(game, &game->door[i], map[i]) == FAILURE)
			return (FAILURE);
	free(map);
	return (SUCCESS);
}

static int	load_game_over(t_game *game)
{
	if (ft_strcmp(game->map_type, "moria") == 0)
	{
		if (!load_xpm(game, &game->game_over, "textures/end_moria.xpm"))
			return (FAILURE);
	}
	else
	{
		if (!load_xpm(game, &game->game_over, "textures/end_morgul.xpm"))
			return (FAILURE);
	}
	return (SUCCESS);
}

void	game_over(t_game *game)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	Mix_PlayMusic(game->music->game_over, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->game_over.img, 0, 0);
	mlx_do_sync(game->mlx);
	usleep(4500000);
	close_game(game);
	exit(EXIT_SUCCESS);
}
