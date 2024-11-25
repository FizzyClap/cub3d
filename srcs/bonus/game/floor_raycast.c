#include "../includes/cub3D.h"

int get_texture_color(t_image *texture, int tx, int ty)
{
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
		return (0);  // Retourne une couleur par défaut (noir)
	int index = ty * texture->width + tx;
	return texture->color[index];
}

// static double	rectify_angle(double angle)
// {
// 	if (angle > 2 * PI)
// 		return (angle - 2 * PI);
// 	else if (angle < 0)
// 		return (angle + 2 * PI);
// 	else
// 		return (angle);
// }

void floor_raycast(t_game *game)
{
    t_image *floorTexture = &game->door[game->total_frames + 1];  // Texture du sol

    // Calcul des directions initiales des rayons
    double rayDirX0 = -cos(game->player.angle) + sin(game->player.angle);
    double rayDirY0 = sin(game->player.angle) + cos(game->player.angle);
    double rayDirX1 = -cos(game->player.angle) - sin(game->player.angle);
    double rayDirY1 = sin(game->player.angle) - cos(game->player.angle);

    // Variables pour l'incrémentation des coordonnées du sol
    double floorX, floorY;
    double floorStepX, floorStepY;

    // Position du joueur (sans prendre en compte le mouvement sur l'axe X pour le sol)
    double centerX = game->player.x;  // Position du joueur en X
    double centerY = game->player.y;  // Position du joueur en Y

    // Calcul du décalage en X de la texture (proportionnel à la position du joueur en X)
    // double offsetX = centerX - (int)centerX; // Ajuster ce facteur selon l'effet désiré

    // Boucle pour dessiner chaque ligne du sol, à partir du bas de l'écran
    for (int y = SCREEN_HEIGHT / 2 + game->player.z; y < SCREEN_HEIGHT; y++)
    {
        double dy = y - SCREEN_HEIGHT / 2.0 - game->player.z;  // Distance verticale du rayon
        double rowDistance = SCREEN_HEIGHT / (2.0 * dy);  // Calcul de la distance pour chaque ligne

        // Calcul des coordonnées du sol initiales
        floorX = centerX + rowDistance * rayDirX0;
        floorY = centerY + rowDistance * rayDirY0;

        // Appliquer le décalage en X en fonction de la position du joueur (décalage selon `offsetX`)
        // floorX += centerX;  // Décalage des coordonnées de la texture en fonction de la position X du joueur

        // Calcul des incréments pour chaque colonne
        floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

        // Parcours des colonnes de l'écran (affichage du sol)
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            // Coordonnées de la texture avant rotation
            int tx = (int)(floorX * floorTexture->width) % floorTexture->width;
            int ty = (int)(floorY * floorTexture->height) % floorTexture->height;

            // Appliquer la rotation de la texture, mais en la maintenant fixe par rapport à sa position
            double angle = game->player.angle;  // Utilisation de l'angle du joueur pour la rotation
            double cosA = cos(angle);  // Cosinus de l'angle
            double sinA = sin(angle);  // Sinus de l'angle

            // Centre de la texture du sol
            double cx = floorTexture->width / 2.0;
            double cy = floorTexture->height / 2.0;

            // Calcul des coordonnées relatives de la texture
            double relTx = tx - cx;  // Coordonnée locale x du carré
            double relTy = ty - cy;  // Coordonnée locale y du carré

            // Appliquer la rotation locale sur chaque pixel de la texture
            double newTx = cosA * relTx - sinA * relTy + cx;
            double newTy = sinA * relTx + cosA * relTy + cy;

            // Assurer que les coordonnées restent dans les limites de la texture
            if (newTx < 0) newTx = -newTx;  // Si coordonnée X < 0, prendre le symétrique
            if (newTx >= floorTexture->width) newTx = 2 * floorTexture->width - newTx - 1;  // Si coordonnée X > width, faire l'inverse
            if (newTy < 0) newTy = -newTy;  // Si coordonnée Y < 0, prendre le symétrique
            if (newTy >= floorTexture->height) newTy = 2 * floorTexture->height - newTy - 1;  // Si coordonnée Y > height, faire l'inverse

            // Calcul du pixel à afficher pour le sol avec les coordonnées de texture ajustées
            int floorColor = get_texture_color(floorTexture, (int)newTx % floorTexture->width, (int)newTy % floorTexture->height);

            // Affichage du pixel du sol
            my_mlx_pixel_put(game->raycast, x, y, floorColor);

            // Mise à jour des coordonnées du sol pour la prochaine itération
            floorX += floorStepX;
            floorY += floorStepY;
        }
    }

    // Dessin du plafond (si nécessaire, peut être similaire à floor_raycast)
    ceil_raycast(game);
}


void ceil_raycast(t_game *game)
{
	t_image *ceilTexture = &game->door[game->total_frames];  // Texture du plafond

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

