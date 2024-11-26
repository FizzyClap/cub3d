#include "../includes/cub3D.h"

void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (540) + game->player.z)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&game->raycast, x, y, ceiling_color);
	}
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(&game->raycast, x, y, floor_color);
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
	int	i;

	i = -1;
	if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && \
	pos.x < game->map->lines[pos.y]->x)
	{
		if (game->map->lines[pos.y]->content[pos.x] == '1')
			return (*game->texture->image[NORTH].color);
		else if (game->map->lines[pos.y]->content[pos.x] == 'D')
		{
			while (++i < game->nb_doors)
				if (game->doors[i].y == pos.y && game->doors[i].x == pos.x && \
				game->doors[i].is_open == false)
					return (*game->texture->image[NORTH].color);
			return (game->floor.a);
		}
		else
			return (game->floor.a);
	}
	else
		return (game->ceiling.a);
}

t_color get_alpha_blended_color(t_color prev, t_color new)
{
	t_color blend;

	blend.a = new.a + (255 - new.a) * prev.a / 255;
	blend.r = (new.a * new.r + (255 - new.a) * prev.a * prev.r / 255) / blend.a;
	blend.g = (new.a * new.g + (255 - new.a) * prev.a * prev.g / 255) / blend.a;
	blend.b = (new.a * new.b + (255 - new.a) * prev.a * prev.b / 255) / blend.a;
	return (blend);
}
