/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:10:13 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:10:15 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	load_weapons(t_game *game, char **map);

int	init_weapon(t_game *game)
{
	char	**weapon;

	weapon = NULL;
	if (ft_strcmp(game->map_type, "moria") == 0)
	{
		weapon = create_balrog_tab(game);
		if (load_weapons(game, weapon) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		weapon = create_staff_tab(game);
		if (load_weapons(game, weapon) == FAILURE)
			return (FAILURE);
	}
	game->anim_weapons.is_animating = false;
	return (SUCCESS);
}

static int	load_weapons(t_game *game, char **map)
{
	int	i;

	game->weapon = ft_calloc(sizeof(t_image), game->weapons_frames);
	if (!game->weapon)
		return (FAILURE);
	i = -1;
	while (++i < game->weapons_frames)
		if (load_xpm(game, &game->weapon[i], map[i]) == FAILURE)
			return (FAILURE);
	free(map);
	return (SUCCESS);
}
