#include "../includes/cub3D_bonus.h"

static t_ray	*dup_ray(t_game *game, t_ray *ray);

void	draw_doors(t_game *game, t_ray *ray, t_coord loop)
{
	t_image	*tex;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	calculate_wall_distance(ray);
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

	transparency = dup_ray(game, ray);
	if (*isLastDoor == true || *isFirst == true)
		transparency->is_door = true;
	ft_lstadd_front(&ray->doors, ft_lstnew(transparency));
	*isLastDoor = !*isLastDoor;
	if (*isFirst && ray->pos_door != 'D')
		*isLastDoor = false;
}

static t_ray	*dup_ray(t_game *game, t_ray *ray)
{
	t_ray	*dest;
	(void)game;

	dest = ft_calloc(sizeof(t_ray), 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, ray, sizeof(t_ray));
	dest->doors = NULL;
	return (dest);
}
