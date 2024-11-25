#include "../includes/cub3D.h"

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop);

void	raycasting(t_ray *ray, t_game *game)
{
	t_coord	loop;
	double	ray_angle;

	floor_raycast(game);
	ceil_raycast(game);
	ray = malloc(sizeof(t_ray));
	loop.x = 0;
	while (loop.x < SCREEN_WIDTH)
	{
		ray_angle = ((game->player.angle) * 180 / PI) - FOV / 2 + \
		FOV * (loop.x / (double)SCREEN_WIDTH);
		init_ray(ray, game, ray_angle);
		calculate_steps(ray);
		perform_dda(ray, game);
		calculate_wall_distance(ray);
		camera_angle_distortion(game, ray);
		draw_wall(game, ray, loop);
		loop.x++;
	}
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

void	perform_dda(t_ray *ray, t_game *game)
{
	int		hit;
	char	pos;

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
		pos = game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x];
		if (pos == '1' || pos == 'D' || pos == 'A')
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

static void	draw_wall(t_game *game, t_ray *ray, t_coord loop)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		height_correct;
	t_image	*tex;

	height_correct = game->player.h / ray->projected_dist;
	line_height = (int)(SCREEN_HEIGHT / ray->projected_dist);
	draw_start = (SCREEN_HEIGHT - line_height + height_correct) / 2;
	draw_end = (SCREEN_HEIGHT + line_height + height_correct) / 2;
	select_wall_texture(game, ray, &tex);
	tex->step = (double)tex->height / line_height;
	tex->pos = (draw_start - 540 + (line_height - height_correct) / 2) * tex->step;
	loop.y = draw_start - 1;
	game->z_buffer[loop.x] = ray->wall_dist;;
	while (++loop.y < draw_end)
	{
		tex->y = (int)tex->pos % (tex->height - 1);
		tex->pos += tex->step;
		if (tex->x >= 0 && tex->x < tex->width && tex->y >= 0 && tex->y < tex->height)
			color = tex->color[tex->width * tex->y + tex->x];
		my_mlx_pixel_put(game->raycast, loop.x, loop.y + game->player.z, color);
	}
	ray->end = draw_end;
}
