#include "../includes/cub3D.h"

double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180);
}

void	init_ray(t_ray *ray, t_game *game, double angle)
{
	ray->pos_x = game->player.x / game->map->tile_x;
	ray->pos_y = game->player.y / game->map->tile_y;
	ray->dir_x = cos(deg_to_rad(angle));
	ray->dir_y = sin(deg_to_rad(angle));
	ray->plane_x = -ray->dir_y * FOV;
	ray->plane_y = ray->dir_x * FOV;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->angle = angle;
}


void	calculate_steps(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - floor(ray->pos_x)) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (floor(ray->pos_x + 1) - ray->pos_x) * ray->delta_x;
	}

	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - floor(ray->pos_y)) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;

		ray->side_dist_y = (floor(ray->pos_y + 1) - ray->pos_y) * ray->delta_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->pos_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->pos_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x] == '1')
			hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_y;
}

void draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	y = start - 1;
	while (++y <= end)
		my_mlx_pixel_put(game->raycast, x, y, color);
}

void	draw_wall(int x, t_ray *ray, t_game *game)
{
	int line_height;
	int draw_start;
	int draw_end;
	int color;

	line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		color = 0xFF0000;
	else
		color = 0x00FF00;
	draw_vertical_line(game, x, draw_start, draw_end, color);
}

void	raycasting(t_ray *ray, t_game *game)
{
	int		x;
	double	ca;
	double	ray_angle;

	x = -1;
	ray = malloc(sizeof(t_ray));
	while (++x < SCREEN_WIDTH)
	{
		ray_angle = (game->player.angle * 180 / PI) - FOV / 2 + FOV * (x / (double)SCREEN_WIDTH);
		printf("ray angle = %f\n", (double)(ray_angle * PI / 180));
		printf("player angle = %f\n", (double)(game->player.angle));
		init_ray(ray, game, ray_angle);
		calculate_steps(ray);
		perform_dda(ray, game);
		calculate_wall_distance(ray);
		ca = game->player.angle - (ray->angle * PI / 180);
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray->wall_dist = ray->wall_dist * cos(ca);
		draw_wall(x, ray, game);
	}
	free(ray);
}
