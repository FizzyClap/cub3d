#include "../includes/cub3D_bonus.h"

void	floor_raycast(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, t_coord loop);

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->pos_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player.dirX + game->player.planeX * ray->pos_x;
	ray->dir_y = game->player.dirY + game->player.planeY * ray->pos_x;
	if (ray->dir_x == 0)
		ray->delta_x = INT_MAX;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INT_MAX;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

void	raycasting(t_game *game)
{
	t_coord	loop;
	t_ray	*ray;
	t_list	*tmp;

	floor_raycast(game);
	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return ;
	loop.x = -1;
	while (++loop.x < SCREEN_WIDTH)
	{
		init_ray(game, ray, loop.x);
		calculate_steps(game, ray);
		perform_dda(game, ray, true);
		calculate_wall_distance(ray);
		draw_wall(game, ray, loop);
		doors_transparency(game, &tmp, ray, loop);
	}
}

void	calculate_steps(t_game *game, t_ray *ray)
{
	t_coord	pos;

	pos.x = (int)game->player.posX;
	pos.y = (int)game->player.posY;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.posX - pos.x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (pos.x + 1.0 - game->player.posX) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.posY - pos.y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (pos.y + 1.0 - game->player.posY) * ray->delta_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray, bool hitDoor)
{
	int	hit;
	int	map_x;
	int	map_y;
	bool	isLastDoor;
	bool	isFirst;
	char	pos;

	hit = 0;
	map_x = (int)game->player.posX;
	map_y = (int)game->player.posY;
	isLastDoor = false;
	isFirst = true;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			map_y += ray->step_y;
			ray->side = 1;
		}
		pos = game->map->lines[map_y]->content[map_x];
		if (pos == '1' || (pos == 'D' && hitDoor == true))
		{
			ray->pos_door = pos;
			ray->door_x = map_x;
			ray->door_y = map_y;
			hit = 1;
		}
		else if (pos == 'D' || isLastDoor || (isFirst && game->map->lines[(int)game->player.posY]->content[(int)game->player.posX] == 'D'))
		{
			ray->pos_door = pos;
			add_doors(game, ray, &isLastDoor, &isFirst);
		}
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_y);
}

void	floor_raycast(t_game *game)
{
	t_image *floorTexture = &game->door[game->doors_frames + 1];
	t_image *ceilTexture = &game->door[game->doors_frames];
	int	y;
	double rayDirX0;
	double rayDirY0;
	double rayDirX1;
	double rayDirY1;
	int	p;
	double	pos_z;
	double	row_distance;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
	int	x;
	int	cell_x;
	int	cell_y;
	int	t_x;
	int	t_y;
	int	color;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		rayDirX0 = game->player.dirX - game->player.planeX;
		rayDirY0 = game->player.dirY - game->player.planeY;
		rayDirX1 = game->player.dirX + game->player.planeX;
		rayDirY1 = game->player.dirY + game->player.planeY;
		p = y - SCREEN_HEIGHT / 2;
		pos_z = 0.5 * SCREEN_HEIGHT;
		row_distance = pos_z / p;
		floor_step_x = row_distance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floor_step_y = row_distance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
		floor_step_x = row_distance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floor_x = game->player.posX + row_distance * rayDirX0;
		floor_y = game->player.posY + row_distance * rayDirY0;
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			t_x = (int)(floorTexture->width * (floor_x - cell_x)) % (floorTexture->width - 1);
			t_y = (int)(floorTexture->height * (floor_y - cell_y)) % (floorTexture->height - 1);
			floor_x += floor_step_x;
			floor_y += floor_step_y;
			color = floorTexture->color[floorTexture->width * t_y + t_x];
			my_mlx_pixel_put(&game->raycast, x, y, color);
			color = ceilTexture->color[ceilTexture->width * t_y + t_x];
			my_mlx_pixel_put(&game->raycast, x, SCREEN_HEIGHT - y - 1, color);
		}
	}
}

void	draw_wall(t_game *game, t_ray *ray, t_coord loop)
{
	t_image	*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	select_wall_texture(game, ray, &tex);
	tex->step = 1.0 * tex->height / line_height;
	tex->pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * tex->step;
	loop.y = draw_start - 1;
	while (++loop.y < draw_end)
	{
		tex->y = (int)tex->pos % (tex->height - 1);
		tex->pos += tex->step;
		color = tex->color[tex->height * tex->y + tex->x];
		my_mlx_pixel_put(&game->raycast, loop.x, loop.y, color);
	}
}

//void raycast(t_game *game)
//{
//		//color = (color >> 1) & 8355711; // make a bit darker
//		//color = (color >> 1) & 8355711; // make a bit darker
//		//if(side == 1) color = (color >> 1) & 8355711;
//}
