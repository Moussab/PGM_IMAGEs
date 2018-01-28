#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib.h"






int main() {


    char *imageName = NULL;
    double k;
    Image_t *image_t = NULL,
            *image_adaptation = NULL,
            *image_histo = NULL,
            *image_g_to_bw = NULL,
            *image_erosion = NULL,
            *image_dilatation = NULL;
    Histogramme_t * histogramme_t = NULL;
    bool stop = false,existe = false;
    int choix = -1;


    while (!stop){

        system("clear");
        printf("\n\n");
        printf("\t===========================================\n");
        printf("\t===\t\t**MENU**1\t\t===\n");
        printf("\t===========================================\n");
        printf("\t===\t1) Lire Une Image PGM\t\t\t\t===\n");
        printf("\t===\t2) Ecrire Une Image PGM\t\t\t\t===\n");
        printf("\t===\t3) Adaptation du contraste\t\t\t===\n");
        printf("\t===\t4) Histogramme\t\t\t\t\t\t===\n");
        printf("\t===\t5) Créer un Histogramme en PGM\t\t===\n");
        printf("\t===\t6) Image grey to black & white\t\t===\n");
        printf("\t===\t7) Erosion\t\t\t\t\t\t\t===\n");
        printf("\t===\t8) Dilatation\t\t\t\t\t\t===\n");
        printf("\t===\t9) Quitter\t\t\t\t\t\t\t===\n");
        printf("\t===========================================\n");
        printf("\t\t\tChoix :\t");
        scanf("%d",&choix);
        getchar();


        switch (choix){

            case 1:
                imageName = malloc (sizeof(char)*50);
                printf("Veillez indiquer le nom de l'image :\t");
                scanf("%s",imageName);
                getchar();
                image_t = read_image(imageName);
                if (!image_t){
                    printf("\n\n\t\tOuverture Impossible, Fichier introuvable\n");
                    pause();
                } else{
                    existe = true;
                    printf("\n\n\t\tOuverture réussite, Fichier chargé\n\n");
                    pause();
                }
                free(imageName);
                choix = -1;
                break;

            case 2:

                if(existe){
                    imageName = malloc (sizeof(char)*50);
                    printf("Veillez indiquer le nom de l'image :\t");
                    scanf("%s",imageName);
                    getchar();
                    if (write_image(image_t,imageName)){
                        printf("\n\n\t\tImage enregistrer avec succès.\n\n");
                        pause();
                    } else{
                        printf("\n\n\t\tImage non enregistrée.\n\n");
                        pause();
                    }
                    free(imageName);
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }

                choix = -1;
                break;

            case 3:
                if(existe){
                    printf("Veillez indiquer le facteur d'adaptation du contrastre :\t");
                    scanf("%lf",&k);
                    getchar();
                    image_adaptation = adapt_contrast_image(image_t, k);
                    if (!image_adaptation){
                        printf("\n\n\t\tImpossible, Fichier interrompu\n");
                        pause();
                    } else{
                        image_t = image_adaptation;
                        printf("\n\n\t\tAdaptation réussite\n\n");
                        pause();
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 4:
                if(existe){
                    histogramme_t = histogram_image(image_t);
                    if (!histogramme_t){
                        printf("\n\n\t\tImpossible, Fichier interrompu\n");
                        pause();
                    } else{
                        printf("\n\n\t\tHistogramme réussit : \n\n");
                        Histogramme_t * hist;
                        hist = histogramme_t;
                        while (hist){
                            printf("Pixel N = %d apparut %d fois dans l'image.\n",hist->intensite,hist->nbIntensite);
                            hist = hist->suiv;
                        }
                        pause();
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 5:
                if(existe){
                    if (!histogramme_t){
                        printf("\n\n\t\tImpossible, Veuillez créer l'histogramme avant.\n");
                        pause();
                    } else{
                        image_histo = write_histogram(histogramme_t);
                        if (!image_histo){
                            printf("\n\n\t\tImpossible, Fichier interrompu\n");
                            pause();
                        } else{
                            imageName = malloc (sizeof(char)*50);
                            printf("Veillez indiquer le nom de l'image :\t");
                            scanf("%s",imageName);
                            getchar();
                            if (write_image(image_histo,imageName)){
                                printf("\n\n\t\tImage de l'histogramme enregistrée avec succès.\n\n");
                                pause();
                            } else{
                                printf("\n\n\t\tImage non enregistrer.\n\n");
                                pause();
                            }
                            free(imageName);
                            pause();
                        }
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 6:
                if(existe){
                    image_g_to_bw = grey_yo_bw(image_t);
                    if (!image_g_to_bw){
                        printf("\n\n\t\tImpossible, Fichier interrompu\n");
                        pause();
                    } else{
                        image_t = image_g_to_bw;
                        printf("\n\n\t\tTransformation réussite\n\n");
                        pause();
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 7:
                if(existe){
                    if (!image_g_to_bw){
                        printf("\n\n\t\tImpossible, Veuillez créer une image Noir et Blanc.\n");
                        pause();
                    } else{
                        image_erosion = erosion(image_t);
                        if (!image_erosion){
                            printf("\n\n\t\tImpossible, Fichier interrompu\n");
                            pause();
                        } else{
                            image_t = image_erosion;
                            printf("\n\n\t\tErosion réussite\n\n");
                            pause();
                        }
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 8:
                if(existe){
                    if (!image_g_to_bw){
                        printf("\n\n\t\tImpossible, Veuillez créer une image Noir et Blanc.\n");
                        pause();
                    } else{
                        image_dilatation = dilatation(image_t);
                        if (!image_dilatation){
                            printf("\n\n\t\tImpossible, Fichier interrompu\n");
                            pause();
                        } else{
                            image_t = image_dilatation;
                            printf("\n\n\t\tDilatation réussite\n\n");
                            pause();
                        }
                    }
                } else{
                    printf("\n\n\t\tVeuillez charger l'image PGM avant.\n\n");
                    pause();
                }
                choix = -1;
                break;

            case 9:
                pause();
                stop = !stop;
                break;
        }


    }






/*



     //  image_t = erosion(image_t);

    //image_t = dilatation(image_t);

*/
    return 0;
}
