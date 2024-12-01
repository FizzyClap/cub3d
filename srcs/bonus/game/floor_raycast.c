#include "../includes/cub3D_bonus.h"

int	get_texture_color(t_image *texture, int tx, int ty)
{
	int	index;

	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return (0);  // Retourne une couleur par défaut (noir)
	index = ty * texture->width + tx;
	return (texture->color[index]);
}

void	floor_raycast(t_game *game)
{
	t_image *floorTexture = &game->door[game->doors_frames + 1];  // Texture du plafond

	for (int y = SCREEN_HEIGHT / 2 + game->player.z; y < SCREEN_HEIGHT; y++)
	{
		// Calcul des distances pour le sol et le plafond
		double dy = y - SCREEN_HEIGHT / 2.0 - game->player.z;  // Différence entre la position actuelle et le centre de l'écran
		double rayDirX0 = -cos(game->player.angle) + sin(game->player.angle);
		double rayDirY0 = sin(game->player.angle) + cos(game->player.angle);
		double rayDirX1 = -cos(game->player.angle) - sin(game->player.angle);
		double rayDirY1 = sin(game->player.angle) - cos(game->player.angle);

		// Calcul de la distance du rayon pour le sol/plafond
		double rowDistance = (SCREEN_HEIGHT / (2.0 * dy));  // Distance en fonction de y
		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

		// Position de départ des coordonnées du sol/plafond
		double floorX = game->player.x + rowDistance * rayDirX0;
		double floorY = game->player.y + rowDistance * rayDirY0;

		// Application des textures
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			// Coordonnées de la texture pour le sol
			int tx = (int)(floorX * floorTexture->width) % floorTexture->width;
			int ty = (int)(floorY * floorTexture->height) % floorTexture->height;

			// Calcul du pixel à afficher pour le plafond
			int floorColor = get_texture_color(floorTexture, tx, ty);

			// Affichage du pixel du plafond
			my_mlx_pixel_put(&game->raycast, x, y, floorColor); // Sol

			// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
			// Le mouvement latéral est pris en compte ici, mais l'orientation de la texture est fixe
			floorX += floorStepX;
			floorY += floorStepY;
		}

		// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
		// A ce niveau, on ne fait plus de rotation des textures, seulement des déplacements latéraux
	}
}

void	ceil_raycast(t_game *game)
{
	t_image *ceilTexture = &game->door[game->doors_frames];// Texture du plafond

	for (int y = 0; y < (SCREEN_HEIGHT / 2 + game->player.z); y++)
	{
		// Calcul des distances pour le sol et le plafond
		double dy = y - SCREEN_HEIGHT / 2.0 - game->player.z;  // Différence entre la position actuelle et le centre de l'écran
		double rayDirX0 = cos(game->player.angle) - sin(game->player.angle);
		double rayDirY0 = -sin(game->player.angle) - cos(game->player.angle);
		double rayDirX1 = cos(game->player.angle) + sin(game->player.angle);
		double rayDirY1 = -sin(game->player.angle) + cos(game->player.angle);

		// Calcul de la distance du rayon pour le sol/plafond
		double rowDistance = SCREEN_HEIGHT / (2.0 * dy);  // Distance en fonction de y
		double ceilStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		double ceilStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

		// Position de départ des coordonnées du sol/plafond
		double ceilX = game->player.x + rowDistance * rayDirX0;
		double ceilY = game->player.y + rowDistance * rayDirY0;

		// Application des textures
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			// Coordonnées de la texture pour le plafond
			int tx = (int)(ceilX * ceilTexture->width) % ceilTexture->width;
			int ty = (int)(ceilY * ceilTexture->height) % ceilTexture->height;

			// Calcul du pixel à afficher pour le plafond
			int ceilColor = get_texture_color(ceilTexture, tx, ty);

			// Affichage du pixel du plafond
			my_mlx_pixel_put(&game->raycast, x, y, ceilColor); // Sol
			// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
			// Le mouvement latéral est pris en compte ici, mais l'orientation de la texture est fixe
			ceilX += ceilStepX;
			ceilY += ceilStepY;
		}
		// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
		// A ce niveau, on ne fait plus de rotation des textures, seulement des déplacements latéraux
	}
}
