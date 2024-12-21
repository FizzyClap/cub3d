/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:46 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:09:57 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

char	**create_moria_tab(t_game *game)
{
	char	**tab_moria;

	tab_moria = malloc(sizeof(char *) * 12);
	if (!tab_moria)
		return (NULL);
	tab_moria[0] = "textures/doors/moria.xpm";
	tab_moria[1] = "textures/doors/moria(1).xpm";
	tab_moria[2] = "textures/doors/moria(2).xpm";
	tab_moria[3] = "textures/doors/moria(3).xpm";
	tab_moria[4] = "textures/doors/moria(4).xpm";
	tab_moria[5] = "textures/doors/moria(5).xpm";
	tab_moria[6] = "textures/doors/moria(6).xpm";
	tab_moria[7] = "textures/doors/moria(7).xpm";
	tab_moria[8] = "textures/doors/moria(8).xpm";
	tab_moria[9] = "textures/doors/moria(9).xpm";
	tab_moria[10] = "textures/doors/moria_open.xpm";
	tab_moria[11] = NULL;
	game->doors_frames = 11;
	return (tab_moria);
}

char	**create_morgul_tab(t_game *game)
{
	game->morgul = malloc(sizeof(char *) * 18);
	if (!game->morgul)
		return (NULL);
	game->morgul[0] = "textures/doors/morgul.xpm";
	game->morgul[1] = "textures/doors/morgul(1).xpm";
	game->morgul[2] = "textures/doors/morgul(2).xpm";
	game->morgul[3] = "textures/doors/morgul(3).xpm";
	game->morgul[4] = "textures/doors/morgul(4).xpm";
	game->morgul[5] = "textures/doors/morgul(5).xpm";
	game->morgul[6] = "textures/doors/morgul(6).xpm";
	game->morgul[7] = "textures/doors/morgul(7).xpm";
	game->morgul[8] = "textures/doors/morgul(8).xpm";
	game->morgul[9] = "textures/doors/morgul(9).xpm";
	game->morgul[10] = "textures/doors/morgul(10).xpm";
	game->morgul[11] = "textures/doors/morgul(11).xpm";
	game->morgul[12] = "textures/doors/morgul(12).xpm";
	game->morgul[13] = "textures/doors/morgul(13).xpm";
	game->morgul[14] = "textures/doors/morgul(14).xpm";
	game->morgul[15] = "textures/doors/morgul(15).xpm";
	game->morgul[16] = "textures/doors/morgul_open.xpm";
	game->morgul[17] = NULL;
	game->doors_frames = 17;
	return (game->morgul);
}

char	**create_balrog_tab(t_game *game)
{
	char	**weapon_balrog;

	weapon_balrog = malloc(sizeof(char *) * 8);
	if (!weapon_balrog)
		return (NULL);
	weapon_balrog[0] = "textures/balrog/balrog.xpm";
	weapon_balrog[1] = "textures/balrog/balrog(1).xpm";
	weapon_balrog[2] = "textures/balrog/balrog(2).xpm";
	weapon_balrog[3] = "textures/balrog/balrog(3).xpm";
	weapon_balrog[4] = "textures/balrog/balrog(4).xpm";
	weapon_balrog[5] = "textures/balrog/balrog(5).xpm";
	weapon_balrog[6] = "textures/balrog/balrog(6).xpm";
	weapon_balrog[7] = NULL;
	game->weapons_frames = 7;
	return (weapon_balrog);
}

char	**create_staff_tab(t_game *game)
{
	char	**weapon_gandalf;

	weapon_gandalf = malloc(sizeof(char *) * 12);
	if (!weapon_gandalf)
		return (NULL);
	weapon_gandalf[0] = "textures/staff/staff.xpm";
	weapon_gandalf[1] = "textures/staff/staff(1).xpm";
	weapon_gandalf[2] = "textures/staff/staff(2).xpm";
	weapon_gandalf[3] = "textures/staff/staff(3).xpm";
	weapon_gandalf[4] = "textures/staff/staff(4).xpm";
	weapon_gandalf[5] = "textures/staff/staff(5).xpm";
	weapon_gandalf[6] = "textures/staff/staff(6).xpm";
	weapon_gandalf[7] = "textures/staff/staff(7).xpm";
	weapon_gandalf[8] = "textures/staff/staff(8).xpm";
	weapon_gandalf[9] = "textures/staff/staff(9).xpm";
	weapon_gandalf[10] = "textures/staff/staff(10).xpm";
	weapon_gandalf[11] = NULL;
	game->weapons_frames = 11;
	return (weapon_gandalf);
}

int	create_launcher_images(t_game *game, char *prefix)
{
	char	**tab_launcher;
	int		i;

	tab_launcher = malloc(sizeof(char *) * 9);
	if (!tab_launcher)
		return (FAILURE);
	tab_launcher[0] = ft_strjoin(prefix, ".xpm");
	tab_launcher[1] = ft_strjoin(prefix, "(1).xpm");
	tab_launcher[2] = ft_strjoin(prefix, "(2).xpm");
	tab_launcher[3] = ft_strjoin(prefix, "(3).xpm");
	tab_launcher[4] = ft_strjoin(prefix, "(4).xpm");
	tab_launcher[5] = ft_strjoin(prefix, "(3).xpm");
	tab_launcher[6] = ft_strjoin(prefix, "(2).xpm");
	tab_launcher[7] = ft_strjoin(prefix, "(1).xpm");
	tab_launcher[8] = NULL;
	game->launcher_frames = 8;
	game->launcher = ft_calloc(sizeof(t_image), (game->launcher_frames + 1));
	if (!game->launcher)
		return (ft_free_tab(tab_launcher), FAILURE);
	i = -1;
	while (++i < game->launcher_frames)
		if (load_xpm(game, &game->launcher[i], tab_launcher[i]) == FAILURE)
			return (ft_free_tab(tab_launcher), FAILURE);
	return (ft_free_tab(tab_launcher), SUCCESS);
}
