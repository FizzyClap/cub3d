#include "../includes/cub3D.h"

int get_texture_color(t_image *texture, int tx, int ty)
{
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return (0);  // Retourne une couleur par défaut (noir)
	int index = ty * texture->width + tx;
	return texture->color[index];
}

static double	rectify_angle(double angle)
{
	if (angle > 2 * PI)
		return (angle - 2 * PI);
	else if (angle < 0)
		return (angle + 2 * PI);
	else
		return (angle);
}

void floor_raycast(t_game *game)
{
	t_image *floorTexture = &game->texture->image[NORTH];  // Texture du sol

	// Calcul des directions initiales des rayons
	double rayDirX0 = -cos(game->player.angle) + sin(game->player.angle);
	double rayDirY0 = sin(game->player.angle) + cos(game->player.angle);
	double rayDirX1 = -cos(game->player.angle) - sin(game->player.angle);
	double rayDirY1 = sin(game->player.angle) - cos(game->player.angle);

	// Variables pour l'incrémentation des coordonnées du sol
	double floorX, floorY;
	double floorStepX, floorStepY;

	for (int y = SCREEN_HEIGHT / 2 + game->player.z; y < SCREEN_HEIGHT; y++)
	{
		// Calcul des distances pour le sol
		double dy = y - SCREEN_HEIGHT / 2.0 - game->player.z;
		double rowDistance = rectify_angle((SCREEN_HEIGHT / (2.0 * dy)));  // Distance en fonction de y
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

		// Position de départ des coordonnées du sol/plafond
		floorX = rectify_angle(game->player.x + rowDistance * rayDirX0);
		floorY = rectify_angle(game->player.y + rowDistance * rayDirY0);

		// Calcul du centre de la texture
		double cx = floorTexture->width / 2.0;
		double cy = floorTexture->height / 2.0;

		// Application des textures pour chaque colonne de l'écran
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			// Coordonnées de la texture pour le sol avant rotation
			int tx = (int)(floorX * floorTexture->width) % floorTexture->width;
			int ty = (int)(floorY * floorTexture->height) % floorTexture->height;

			// Appliquer la rotation des coordonnées de la texture
			double angle = game->player.angle;  // L'angle du joueur
			double cosA = -cos(angle * 2);
			double sinA = -sin(angle * 2);

			// Rotation de la texture autour de son centre
			double newTx = cosA * (tx - cx) - sinA * (ty - cy) + cx;
			double newTy = sinA * (tx - cx) + cosA * (ty - cy) + cy;

			// Calcul du pixel à afficher pour le sol
			int floorColor = get_texture_color(floorTexture, (int)newTx % floorTexture->width, (int)newTy % floorTexture->height);

			// Affichage du pixel du sol
			my_mlx_pixel_put(game->raycast, x, y, floorColor);

			// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
			floorX += floorStepX;
			floorY += floorStepY;
		}
	}
	ceil_raycast(game);
}


void ceil_raycast(t_game *game)
{
	t_image *ceilTexture = &game->door;  // Texture du plafond

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
			my_mlx_pixel_put(game->raycast, x, y, ceilColor); // Sol

			// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
			// Le mouvement latéral est pris en compte ici, mais l'orientation de la texture est fixe
			ceilX += ceilStepX;
			ceilY += ceilStepY;
		}

		// Mise à jour des coordonnées du sol/plafond pour la prochaine itération
		// A ce niveau, on ne fait plus de rotation des textures, seulement des déplacements latéraux
	}
}