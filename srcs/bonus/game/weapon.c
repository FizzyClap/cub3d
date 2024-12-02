#include "../includes/cub3D_bonus.h"

static int	load_weapons(t_game *game, char **map);
static char	**create_balrog_tab(t_game *game);
static char	**create_staff_tab(t_game *game);

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

static char	**create_balrog_tab(t_game *game)
{
	game->weapon_map = malloc(sizeof(char *) * 8);
	if (!game->weapon_map)
		return (NULL);
	game->weapon_map[0] = "textures/balrog/balrog.xpm";
	game->weapon_map[1] = "textures/balrog/balrog(1).xpm";
	game->weapon_map[2] = "textures/balrog/balrog(2).xpm";
	game->weapon_map[3] = "textures/balrog/balrog(3).xpm";
	game->weapon_map[4] = "textures/balrog/balrog(4).xpm";
	game->weapon_map[5] = "textures/balrog/balrog(5).xpm";
	game->weapon_map[6] = "textures/balrog/balrog(6).xpm";
	game->weapon_map[7] = NULL;
	game->weapons_frames = 7;
	return (game->weapon_map);
}

static char	**create_staff_tab(t_game *game)
{
	game->weapon_map = malloc(sizeof(char *) * 12);
	if (!game->weapon_map)
		return (NULL);
	game->weapon_map[0] = "textures/staff/staff.xpm";
	game->weapon_map[1] = "textures/staff/staff(1).xpm";
	game->weapon_map[2] = "textures/staff/staff(2).xpm";
	game->weapon_map[3] = "textures/staff/staff(3).xpm";
	game->weapon_map[4] = "textures/staff/staff(4).xpm";
	game->weapon_map[5] = "textures/staff/staff(5).xpm";
	game->weapon_map[6] = "textures/staff/staff(6).xpm";
	game->weapon_map[7] = "textures/staff/staff(7).xpm";
	game->weapon_map[8] = "textures/staff/staff(8).xpm";
	game->weapon_map[9] = "textures/staff/staff(9).xpm";
	game->weapon_map[10] = "textures/staff/staff(10).xpm";
	game->weapon_map[11] = NULL;
	game->weapons_frames = 11;
	return (game->weapon_map);
}
