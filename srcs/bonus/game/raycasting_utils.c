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
	*tex = &game->texture->image[NORTH];
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
	int		mid_ray;

	mid_ray = (game->player.angle * CENT_PI) - 30 + FOV * (870 / (double)SCREEN_WIDTH);
	init_ray(game, &ray, SCREEN_WIDTH / 2);
	calculate_steps(game, &ray);
	if (door == true)
	{
		perform_dda(game, &ray, true);
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
