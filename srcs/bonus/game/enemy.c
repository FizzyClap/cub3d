/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:20 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:21 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	fill_struct_enemy(t_game *game, char *prefix);

int	init_enemy(t_game *game, char *prefix)
{
	int	y;
	int	x;

	game->nb_enemy = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
			if (game->map->lines[y]->content[x] == 'A')
				game->nb_enemy++;
	}
	if (game->nb_enemy == 0)
		return (SUCCESS);
	game->enemy = malloc(sizeof(t_enemy) * game->nb_enemy);
	if (!game->enemy)
		return (FAILURE);
	if (fill_struct_enemy(game, prefix) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	create_enemy_tab(t_game *game, char *prefix, int i)
{
	char	**enemy_tab;
	int		idx;

	enemy_tab = malloc(sizeof(char *) * 6);
	if (!enemy_tab)
		return (FAILURE);
	enemy_tab[0] = ft_strjoin(prefix, ".xpm");
	enemy_tab[1] = ft_strjoin(prefix, "(1).xpm");
	enemy_tab[2] = ft_strjoin(prefix, "(2).xpm");
	enemy_tab[3] = ft_strjoin(prefix, "(3).xpm");
	enemy_tab[4] = ft_strjoin(prefix, "(4).xpm");
	enemy_tab[5] = NULL;
	game->enemy_frames = 5;
	game->enemy[i].texture = ft_calloc(sizeof(t_image), \
	(game->enemy_frames + 1));
	idx = -1;
	while (++idx < game->enemy_frames)
		if (!load_xpm(game, &game->enemy[i].texture[idx], enemy_tab[idx]))
			return (FAILURE);
	ft_free_tab(enemy_tab);
	return (SUCCESS);
}

static int	fill_struct_enemy(t_game *game, char *prefix)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
		{
			if (game->map->lines[y]->content[x] == 'A')
			{
				game->enemy[i].x = x + 0.5;
				game->enemy[i].y = y + 0.5;
				game->enemy[i].is_animating = false;
				if (create_enemy_tab(game, prefix, i) == FAILURE)
					return (FAILURE);
				i++;
			}
		}
	}
	return (SUCCESS);
}
