#include "../includes/cub3D.h"

//1st triangle: -wall distance
//				-row_y (up-mid vision wall)
//				- ??
//2nd triangle: -x (ray until it hit the floor)
//				-cam_z (floor to eyes)
//				-

void	floor_raycasting(t_game *game)
{
	int		y;
	double	raydirx0;
	double	raydirx1;
	double	raydiry0;
	double	raydiry1;
	int		p;

	y = -1;
	while (++y < game->map->y)
	{
		p = y - SCREEN_HEIGHT / 2;
	}
}
