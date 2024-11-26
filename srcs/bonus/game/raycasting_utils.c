#include "../includes/cub3D.h"

static int	hit_enemy(t_ray *ray, t_game *game);
static void	move_ray(t_ray *ray);

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
	if (game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x] == 'D')
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
	int		enemy_index = -1;

	mid_ray = (game->player.angle * CENT_PI) - 30 + FOV * (870 / (double)SCREEN_WIDTH);
	init_ray(&ray, game, mid_ray);
	calculate_steps(&ray);
	if (door == true)
		perform_dda(&ray, game);
	else
		enemy_index = hit_enemy(&ray, game);
	if (game->map->lines[(int)ray.pos_y]->content[(int)ray.pos_x] == 'D')
		toggle_door(game, (int)ray.pos_y, (int)ray.pos_x);
	else if (enemy_index != -1)
		game->target = enemy_index;
}

static int	hit_enemy(t_ray *ray, t_game *game)
{
	int		hit;
	t_coord	ray_pos;
	int		i;

	hit = 0;
	while (!hit)
	{
		move_ray(ray);
		ray_pos.y = (int)floor(ray->pos_y);
		ray_pos.x = (int)floor(ray->pos_x);
		if (ray_pos.y < 0 || ray_pos.y >= game->map->y - 1 ||
		ray_pos.x < 0 || ray_pos.x >= game->map->lines[ray_pos.y]->x)
			return (-1);
		if (game->map->lines[ray_pos.y]->content[ray_pos.x] == 'A')
			hit = 1;
		i = -1;
		while (++i < game->nb_enemy)
			if ((int)game->enemy[i].x == ray_pos.x && \
				(int)game->enemy[i].y == ray_pos.y)
				return (i);
	}
	return (-1);
}

static void	move_ray(t_ray *ray)
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
