#include "../includes/cub3D.h"

void	camera_angle_distortion(t_game *game, t_ray *ray)
{
	double	camera_angle;

	camera_angle = game->player.angle - (ray->angle * PI / 180);
	if (camera_angle < 0)
		camera_angle += 2 * PI;
	if (camera_angle > 2 * PI)
		camera_angle -= 2 * PI;
	ray->projected_dist = ray->wall_dist * cos(camera_angle);
}

void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex, double time)
{
	if (game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x] == 'D')
		select_door_texture(game, ray, tex, time);
	else if (ray->side == 1 && ray->step_y < 0)
		*tex = &game->texture->image[NORTH];
	else if (ray->side == 1 && ray->step_y > 0)
		*tex = &game->texture->image[SOUTH];
	else if (ray->side == 0 && ray->step_x < 0)
		*tex = &game->texture->image[WEST];
	else if (ray->side == 0 && ray->step_x > 0)
		*tex = &game->texture->image[EAST];
	if (ray->side == 0)
		(*tex)->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		(*tex)->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	(*tex)->wall_x -= floor((*tex)->wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		(*tex)->wall_x = 1.0 - (*tex)->wall_x;
	(*tex)->x = (int)((*tex)->wall_x * (*tex)->width);
}

void	shoot_ray_to_door(t_game *game)
{
	t_ray	ray;
	int		mid_ray;

	mid_ray = (game->player.angle * CENT_PI) - 30 + FOV * (870 / (double)SCREEN_WIDTH);
	init_ray(&ray, game, mid_ray);
	calculate_steps(&ray);
	perform_dda(&ray, game);
	if (game->map->lines[(int)ray.pos_y]->content[(int)ray.pos_x] == 'D')
		toggle_door(game, (int)ray.pos_y, (int)ray.pos_x);
}
