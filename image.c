// image.c
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

imageRGB *creerImageRGB(int longueur, int hauteur, int resolution) {
    imageRGB *image = malloc(sizeof(imageRGB));
    image->longueur = longueur;
    image->hauteur = hauteur;
    image->resolution = resolution;

    image->img = malloc(3 * sizeof(unsigned char **));
    for (int i = 0; i < 3; i++) {
        image->img[i] = malloc(hauteur * sizeof(unsigned char *));
        for (int j = 0; j < hauteur; j++) {
            image->img[i][j] = malloc(longueur * sizeof(unsigned char));
        }
    }

    return image;
}

void initialiserImageAleatoire(imageRGB *image) {
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < image->hauteur; y++) {
            for (int x = 0; x < image->longueur; x++) {
                image->img[i][y][x] = (rand() % 256);
            }
        }
    }
}

void libererImageRGB(imageRGB *image) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < image->hauteur; j++) {
            free(image->img[i][j]);
        }
        free(image->img[i]);
    }
    free(image->img);
    free(image);
}

void afficherImage(imageRGB *image) {
    for (int y = 0; y < image->hauteur; y++) {
        for (int x = 0; x < image->longueur; x++) {
            printf("(%3d, %3d, %3d) ", image->img[0][y][x], image->img[1][y][x], image->img[2][y][x]);
        }
        printf("\n");
    }
}

void creerFichierDonnees(imageRGB *image, int colorIndex) {
    FILE *file = fopen("image_data.txt", "w");
    FILE *gnuplotScript = fopen("plot_script.gp", "w");

    if (file && gnuplotScript) {
        fprintf(gnuplotScript, "set terminal wxt size 800,600\n");
        fprintf(gnuplotScript, "set title 'RGB Image Visualization'\n");
        fprintf(gnuplotScript, "set xlabel 'X'\n");
        fprintf(gnuplotScript, "set ylabel 'Y'\n");
        fprintf(gnuplotScript, "set xrange [0:*]\n");
        fprintf(gnuplotScript, "set yrange [0:*]\n");

        fprintf(gnuplotScript, "plot 'image_data.txt' using 1:2:(column(%d + 3)):(column(%d + 3)):(column(%d + 3)) with points pt 7 lc rgb variable title 'RGB Image'\n", colorIndex, colorIndex, colorIndex);
        fprintf(gnuplotScript, "pause -1 'Press any key to exit'\n");

        for (int y = 0; y < image->hauteur; y++) {
            for (int x = 0; x < image->longueur; x++) {
                fprintf(file, "%d %d %d %d %d\n", x, y, image->img[0][y][x], image->img[1][y][x], image->img[2][y][x]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
        fclose(gnuplotScript);

        system("gnuplot plot_script.gp");
    } else {
        fprintf(stderr, "Error: Couldn't create files\n");
    }
}

// Function to capture image data from the keyboard
void saisirImage(imageRGB *image) {
    for (int i = 0; i < 3; i++) {
        printf("Enter data for color component %c:\n", 'R' + i);
        for (int y = 0; y < image->hauteur; y++) {
            for (int x = 0; x < image->longueur; x++) {
                printf("Enter value at position (%d, %d): ", x, y);
                scanf("%hhu", &image->img[i][y][x]);
            }
        }
    }
}

// Function to capture image data from a file
void chargerImage(imageRGB *image, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: Couldn't open file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < image->hauteur; y++) {
            for (int x = 0; x < image->longueur; x++) {
                if (fscanf(file, "%hhu", &image->img[i][y][x]) != 1) {
                    fprintf(stderr, "Error: Invalid file format\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    fclose(file);
}
