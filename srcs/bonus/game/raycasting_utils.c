#include "../includes/cub3D_bonus.h"

static void	calculate_tex_x_pos(t_game *game, t_ray *ray, t_image **tex);

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
	char	pos;

	pos = game->map->lines[(int)game->player.posY]->content[(int)game->player.posX];
	if (ray->is_door && ray->door_idx == game->door_idx && game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, game->doors_frames);
	else if (ray->is_door && ray->door_idx == game->door_idx && !game->doors[game->door_idx].is_open)
		*tex = doors_animation(game, game->door_idx, 0);
	else if (ray->is_door && (game->doors[ray->door_idx].is_open || pos == 'D'))
		*tex = &game->door[game->doors_frames - 1];
	else if (ray->is_door && !game->doors[ray->door_idx].is_open)
		*tex = &game->door[0];
	else if (ray->pos_door == 'D')
		select_door_texture(game, ray, tex);
	else if (ray->side == 1 && ray->step_y < 0)
		*tex = &game->texture->image[NORTH];
	else if (ray->side == 1 && ray->step_y > 0)
		*tex = &game->texture->image[SOUTH];
	else if (ray->side == 0 && ray->step_x < 0)
		*tex = &game->texture->image[WEST];
	else if (ray->side == 0 && ray->step_x > 0)
		*tex = &game->texture->image[EAST];
	calculate_tex_x_pos(game, ray, tex);
}

static void	calculate_tex_x_pos(t_game *game, t_ray *ray, t_image **tex)
{
	if (ray->side == 0)
		(*tex)->wall_x = game->player.posY + ray->wall_dist * ray->dir_y;
	else
		(*tex)->wall_x = game->player.posX + ray->wall_dist * ray->dir_x;
	(*tex)->wall_x -= floor((*tex)->wall_x);
	(*tex)->x = (int)((*tex)->wall_x * (double)(*tex)->width);
	if (ray->side == 0 && ray->dir_x > 0)
		(*tex)->x = (*tex)->width - (*tex)->x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		(*tex)->x = (*tex)->width - (*tex)->x - 1;
}

void	shoot_ray_to_center(t_game *game, bool door)
{
	t_ray	ray;

	init_ray(game, &ray, SCREEN_WIDTH / 2);
	calculate_steps(game, &ray);
	if (door == true)
	{
		perform_dda(game, &ray, true);
		if (game->map->lines[ray.door_y]->content[ray.door_x] == 'D')
			toggle_door(game, ray.door_y, ray.door_x);
	}
	else
		game->target = hit_enemy(&ray, game);
}
