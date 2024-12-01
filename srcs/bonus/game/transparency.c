#include "../includes/cub3D_bonus.h"

static t_ray	*dup_ray(t_game *game, t_ray *ray);

void	draw_doors(t_game *game, t_ray *ray, t_coord loop)
{
	t_draw	d;
	t_image	*tex;

	calculate_wall_distance(ray);
	camera_angle_distortion(game, ray);
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

void	doors_transparency(t_game *game, t_list **tmp, t_ray *ray, t_coord loop)
{
	*tmp = ray->doors;
	while (*tmp)
	{
		draw_doors(game, (*tmp)->content, loop);
		*tmp = (*tmp)->next;
	}
	ft_lstclear(&ray->doors, free);
	ray->doors = NULL;
}

void	add_doors(t_game *game, t_ray *ray, bool *isLastDoor, bool *isFirst)
{
	t_ray	*transparency;
	char	pos;

	pos = game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x];
	transparency = dup_ray(game, ray);
	if (*isLastDoor == true || *isFirst == true)
		transparency->is_door = true;
	ft_lstadd_front(&ray->doors, ft_lstnew(transparency));
	*isLastDoor = !*isLastDoor;
	if (*isFirst && pos != 'D')
		*isLastDoor = false;
}

static t_ray	*dup_ray(t_game *game, t_ray *ray)
{
	t_ray	*dest;
	int		i;
	dest = ft_calloc(sizeof(t_ray), 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < game->nb_doors)
		if (game->doors[i].x == (int)floor(ray->pos_x) && \
			game->doors[i].y == (int)floor(ray->pos_y))
			ray->door_idx = i;
	ft_memcpy(dest, ray, sizeof(t_ray));
	dest->doors = NULL;
	return (dest);
}
