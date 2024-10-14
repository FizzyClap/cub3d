#include "../includes/cub3D.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	minimap(t_game *game)
{
	int	x;
	int	y;

	x = get_x_max(game->map);
	y = get_y_max(game->map);
	
}