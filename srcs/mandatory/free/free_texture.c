#include "../includes/cub3D.h"

void	free_texture(t_texture *texture)
{
	if (texture->id)
		free(texture->id);
	if (texture->north_path)
		free(texture->north_path);
	if (texture->south_path)
		free(texture->south_path);
	if (texture->west_path)
		free(texture->west_path);
	if (texture->east_path)
		free(texture->east_path);
	if (texture->floor_color)
		free(texture->floor_color);
	if (texture->ceiling_color)
		free(texture->ceiling_color);
	free(texture);
}
