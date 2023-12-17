// image.h
#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int longueur;
    int hauteur;
    int resolution;
    unsigned char ***img;  // img[3] to store RGB pixel data
} imageRGB;

imageRGB *creerImageRGB(int longueur, int hauteur, int resolution);
void initialiserImageAleatoire(imageRGB *image);
void libererImageRGB(imageRGB *image);
void afficherImage(imageRGB *image);
void creerFichierDonnees(imageRGB *image, int colorIndex);
void saisirImage(imageRGB *image);
void chargerImage(imageRGB *image, const char *fileName);

#endif
