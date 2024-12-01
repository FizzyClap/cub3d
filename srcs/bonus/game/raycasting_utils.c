#include "../includes/cub3D_bonus.h"

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

void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex)
{
	if (ray->is_door && ray->door_idx == game->door_idx && game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, game->doors_frames);
	else if (ray->is_door && ray->door_idx == game->door_idx && !game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, 0);
	else if (ray->is_door && (game->doors[ray->door_idx].is_open || game->map->lines[(int)game->player.y]->content[(int)game->player.x] == 'D')) // to fix
		*tex = &game->door[game->doors_frames - 1];
	else if (ray->is_door && !game->doors[ray->door_idx].is_open) // to fix
		*tex = &game->door[0];
	else if (game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x] == 'D')
		select_door_texture(game, ray, tex);
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

void	shoot_ray_to_center(t_game *game, bool door)
{
	t_ray	ray;
	int		mid_ray;

	mid_ray = (game->player.angle * CENT_PI) - 30 + FOV * (870 / (double)SCREEN_WIDTH);
	init_ray(&ray, game, mid_ray);
	calculate_steps(&ray);
	if (door == true)
	{
		perform_dda(&ray, game, true);
		if (game->map->lines[(int)ray.pos_y]->content[(int)ray.pos_x] == 'D')
			toggle_door(game, (int)ray.pos_y, (int)ray.pos_x);
	}
	else
		game->target = hit_enemy(&ray, game);
}

void	move_ray(t_ray *ray)
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
}
