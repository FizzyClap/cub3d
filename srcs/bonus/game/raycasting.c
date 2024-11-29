#include "../includes/cub3D_bonus.h"

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop);

void	raycasting(t_ray *ray, t_game *game)
{
	t_coord	loop;
	double	ray_angle;
	t_list *tmp;

	floor_raycast(game);
	ceil_raycast(game);
	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return ;
	loop.x = -1;
	while (++loop.x < SCREEN_WIDTH)
	{
		ray_angle = ((game->player.angle) * 180 / PI) - FOV / 2 + \
		FOV * (loop.x / (double)SCREEN_WIDTH);
		init_ray(ray, game, ray_angle);
		calculate_steps(ray);
		perform_dda(ray, game, false);
		calculate_wall_distance(ray);
		camera_angle_distortion(game, ray);
		draw_wall(game, ray, loop);
		doors_transparency(game, &tmp, ray, loop);
	}
	sort_enemies(game);
	render_enemies(game);
	free(ray);
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

void	perform_dda(t_ray *ray, t_game *game, bool hitDoor)
{
	bool	hit;
	bool	isLastDoor;
	bool	isFirst;
	char	pos;

	hit = false;
	isLastDoor = false;
	isFirst = true;
	while (hit == false)
	{
		move_ray(ray);
		pos = game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x];
		if (pos == '1' || (pos == 'D' && hitDoor == true))
			hit = true;
		else if (pos == 'D' || isLastDoor || (isFirst && game->map->lines\
		[(int)game->player.y]->content[(int)game->player.x] == 'D'))
			add_doors(game, ray, &isLastDoor, &isFirst);
		isFirst = false;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_y;
}

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop)
{
	t_draw	d;
	t_image	*tex;

	d.h_correct = game->player.h / ray->projected_dist;
	d.h_line = (int)(SCREEN_HEIGHT / ray->projected_dist);
	d.draw_start = (SCREEN_HEIGHT - d.h_line + d.h_correct) / 2;
	d.draw_end = (SCREEN_HEIGHT + d.h_line + d.h_correct) / 2;
	select_wall_texture(game, ray, &tex);
	tex->step = (double)tex->height / d.h_line;
	tex->pos = (d.draw_start - 540 + (d.h_line - d.h_correct) / 2) * tex->step;
	loop.y = d.draw_start - 1;
	game->z_buffer[loop.x] = ray->wall_dist;
	d.color = 0;
	while (++loop.y < d.draw_end)
	{
		tex->y = (int)tex->pos % (tex->height - 1);
		tex->pos += tex->step;

		if (tex->x >= 0 && tex->x < tex->width && \
			tex->y >= 0 && tex->y < tex->height)
			d.color = tex->color[tex->width * tex->y + tex->x];
		my_mlx_pixel_put(&game->raycast, loop.x, loop.y + game->player.z, d.color);
	}
}
