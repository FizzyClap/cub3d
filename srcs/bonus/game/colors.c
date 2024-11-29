#include "../includes/cub3D_bonus.h"

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
