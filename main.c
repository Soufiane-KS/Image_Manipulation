// main.c
#include <stdio.h>
#include <stdlib.h>
#include "image.c"

int main() {
    int longueur = 100;
    int hauteur = 100;
    int resolution = 100 * 100;

    imageRGB *image = creerImageRGB(longueur, hauteur, resolution);

    int choice;

    printf("Choose an option:\n");
    printf("1. Initialize the image with random values\n");
    printf("2. Capture image data from the keyboard\n");
    printf("3. Capture image data from a file\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            initialiserImageAleatoire(image);
            break;
        case 2:
            saisirImage(image);
            break;
        case 3:
            chargerImage(image, "input_image.txt"); // Make sure to provide the correct file name
            break;
        default:
            fprintf(stderr, "Error: Invalid choice\n");
            libererImageRGB(image);
            exit(EXIT_FAILURE);
    }

    printf("Choose a color component to display:\n");
    printf("1. Red\n");
    printf("2. Green\n");
    printf("3. Blue\n");

    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        fprintf(stderr, "Error: Invalid choice\n");
        libererImageRGB(image);
        exit(EXIT_FAILURE);
    }

    afficherImage(image);

    creerFichierDonnees(image, choice - 1);

    libererImageRGB(image);

    return 0;
}
