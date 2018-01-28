#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef PGM_LIB_H
#define PGM_LIB_H


typedef struct {
    char nbMagique[2];
    size_t width;
    size_t height;
    size_t nbColor;
    char **data;
    long nbLigneData;
} Image_t;

typedef struct Histogramme_t{
    int intensite;
    int nbIntensite;
    struct Histogramme_t* suiv;
}Histogramme_t;


Image_t * read_image(char *imageName);
char** str_split(char* a_str, const char a_delim);
void pause();

bool write_image(Image_t *image, char *imageName);

double min(double x, double y);

double max(double x, double y);

Image_t *adapt_contrast_image(Image_t *image_t, double k);

Histogramme_t *histogram_image(Image_t *image);

Image_t *grey_yo_bw(Image_t *image);

Image_t *erosion(Image_t *image);

Image_t *dilatation(Image_t *image);

Image_t *write_histogram(Histogramme_t *pHistogramme);

#endif //PGM_LIB_H
