#include "../includes/cub3D.h"

void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game->raycast, x, y, ceiling_color);
	}
	y = SCREEN_HEIGHT / 2 - 1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game->raycast, x, y, floor_color);
	}
}

void	get_color(t_color *type, char *path)
{
	char	**rgb;

	rgb = ft_split(path, ',');
	type->r = ft_atoi(rgb[0]);
	type->g = ft_atoi(rgb[1]);
	type->b = ft_atoi(rgb[2]);
	ft_free_tab(rgb);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	minimap_color(t_game *game, t_coord pos)
{
	if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && \
	pos.x < game->map->lines[pos.y]->x)
	{
		if (game->map->lines[pos.y]->content[pos.x] == '1')
			return (*game->texture->image[NORTH].color);
		else
			return (game->floor.color);
	}
	else
		return (game->ceiling.color);
}
