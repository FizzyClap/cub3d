#include "../includes/cub3D.h"

void	init_map(t_map *map, char *file)
{
	map->file = ft_strdup(file);
	map->lines = NULL;
	map->first_line = NULL;
	map->start_read = false;
	map->end_read = false;
	map->y = 0;
	map->x_max = 0;
	map->start_x = 0;
	map->start_y = 0;
	map->count_start_pos = 0;
}

void	init_texture(t_texture *texture)
{
	texture->id = NULL;
	texture->north_path = NULL;
	texture->south_path = NULL;
	texture->west_path = NULL;
	texture->east_path = NULL;
	texture->floor_color = NULL;
	texture->ceiling_color = NULL;
}

void	init_game(t_game **game, t_texture *texture, t_map *map)
{
	*game = malloc(sizeof(t_game));
	(*game)->texture = texture;
	(*game)->map = map;
}
