#include "../../includes/cub3D.h"

void	free_map(t_map *map)
{
	int	y;

	free(map->file);
	free(map->first_line);
	if (map->lines)
	{
		y = -1;
		while (++y < map->y)
		{
			free(map->lines[y]->content);
			free(map->lines[y]);
		}
		free(map->lines);
	}
	free(map);
}
