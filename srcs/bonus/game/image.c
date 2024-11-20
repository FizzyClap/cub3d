#include "../includes/cub3D.h"

static int	load_walls(t_game *game);
static int	load_doors(t_game *game, char **map);
static char	**create_moria_tab(t_game *game);
static char	**create_morgul_tab(t_game *game);

int	load_textures(t_game *game)
{
	char	**map;

	if (load_walls(game) == FAILURE)
		return (FAILURE);
	if (ft_strcmp(game->file, "maps/moria.cub") == 0)
		map = create_moria_tab(game);
	else
		map = create_morgul_tab(game);
	if (load_doors(game, map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	load_walls(t_game *game)
{
	int		width;
	int		height;
	int		i;
	char	*file[4];
	int		t;

	file[NORTH] = game->texture->north_path;
	file[SOUTH] = game->texture->south_path;
	file[WEST] = game->texture->west_path;
	file[EAST] = game->texture->east_path;
	i = -1;
	while (++i < 4)
	{
		game->texture->image[i].img = mlx_xpm_file_to_image(game->mlx, file[i],
				&width, &height);
		if (!game->texture->image[i].img)
			return (FAILURE);
		game->texture->image[i].color = \
			(int *)mlx_get_data_addr(game->texture->image[i].img, &t, &t, &t);
		game->texture->image[i].width = width;
		game->texture->image[i].height = height;
	}
	//game->ring.img = mlx_xpm_file_to_image(game->mlx, "textures/ring.xpm",
	//	&width, &height);
	//if (!game->ring.img)
	//	return (FAILURE);
	//game->ring.color = \
	//	(int *)mlx_get_data_addr(game->ring.img, &t, &t, &t);
	//game->ring.width = width;
	//game->ring.height = height;
	return (SUCCESS);
}

static int	load_doors(t_game *game, char **map)
{
	int	width;
	int	height;
	int	t;
	int	i;

	i = -1;
	while (++i < game->total_frames + 2)
		game->door[i].img = NULL;
	i = -1;
	while (++i < game->total_frames + 2)
	{
		game->door[i].img = mlx_xpm_file_to_image(game->mlx, map[i], &width, &height);
		if (!game->door[i].img)
			return (FAILURE);
		game->door[i].addr = mlx_get_data_addr(game->door[i].img, &t, &t, &t);
		game->door[i].color = (int *)game->door[i].addr;
		game->door[i].width = width;
		game->door[i].height = height;
	}
	free(map);
	return (SUCCESS);
}

static char **create_moria_tab(t_game *game)
{
	game->moria = malloc(sizeof(char *) * 14);
	if (!game->moria)
		return (NULL);
	game->moria[0] = "textures/doors/moria.xpm";
	game->moria[1] = "textures/doors/moria(1).xpm";
	game->moria[2] = "textures/doors/moria(2).xpm";
	game->moria[3] = "textures/doors/moria(3).xpm";
	game->moria[4] = "textures/doors/moria(4).xpm";
	game->moria[5] = "textures/doors/moria(5).xpm";
	game->moria[6] = "textures/doors/moria(6).xpm";
	game->moria[7] = "textures/doors/moria(7).xpm";
	game->moria[8] = "textures/doors/moria(8).xpm";
	game->moria[9] = "textures/doors/moria(9).xpm";
	game->moria[10] = "textures/doors/door_open_test.xpm";
	game->moria[11] = "textures/moria_ceil.xpm";
	game->moria[12] = "textures/moria_floor.xpm";
	game->moria[13] = NULL;
	game->total_frames = 11;
	return (game->moria);
}

static char **create_morgul_tab(t_game *game)
{
	game->morgul = malloc(sizeof(char *) * 20);
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
	game->morgul[17] = "textures/morgul_ceil.xpm";
	game->morgul[18] = "textures/morgul_floor.xpm";
	game->morgul[19] = NULL;
	game->total_frames = 17;
	return (game->morgul);
}
