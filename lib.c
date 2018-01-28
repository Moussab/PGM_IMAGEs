//
// Created by amrine on 24/01/18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "lib.h"

Image_t *write_histogram(Histogramme_t *pHistogramme) {

    Image_t* image;
    Histogramme_t* histogramme;
    int m = INT_MIN, cpt = 0, i = 0, j = 0;
    char ** matrix = (char **) malloc(999999*sizeof(char *));
    char *str;
    int bits[200][256];

    for (i = 0; i < 200 ; i++) {
        for (j = 0; j < 256 ; j++) {
            bits[i][j] = 0;
        }
    }




    histogramme = pHistogramme;


    image = malloc(sizeof(Image_t));

    strcpy(image->nbMagique,"P2");
    image->nbColor = 255;
    image->height = 200;
    image->width = 256;




    while (histogramme){
        m = (int) max(m,histogramme->nbIntensite);
        histogramme = histogramme->suiv;
    }

    double scale = (double)(((double)image->height)/((double)m));

    for (i = 0; i < image->width; ++i) {
        bool stop = false;
        histogramme = pHistogramme;
        while (!stop && histogramme){
            if (histogramme->intensite == i)
                stop = !stop;
            else
                histogramme = histogramme->suiv;
        }

        if (stop){
            int mark = (int) (image->height - (int)(scale * histogramme->nbIntensite));

            for (j = 0; j < mark; j++)
                bits[j][i] = 0;
            for ( ; j < image->height ; ++j)
                bits[j][i] = 255;
        }
    }



    for (i = 0; i < image->height; i++) {
        str = (char*)malloc((image->width)* sizeof(char*));

        for (j = 0; j < image->width; j++) {
            sprintf(str,"%s%d%c",str,bits[i][j],' ');
        }

        matrix[i] = str;
    }

    image->nbLigneData = image->height;
    image->data = matrix;

    return image;
}

Image_t *dilatation(Image_t *image) {
    int tab[26000][80];
    int i, j, cpt_x = 0, cpt_y = 0;
    char *line;
    char ** matrix = (char **) malloc(999999*sizeof(char *));

    for (i = 0; i < 26000; i++) {
        for (j = 0; j < 80; j++) {
            tab[i][j] = -1;
        }
    }

    for (i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);

        cpt_y = 0;
        char* pch = strtok (line," ");
        while (pch != NULL && *pch != '\r')
        {
            size_t pixel = (size_t ) strtol(pch,NULL,10);
            tab[cpt_x][cpt_y] = (int) pixel;
            cpt_y++;
            pch = strtok (NULL, " ");
        }
        cpt_x++;
    }

    cpt_y = 0;
    while (tab[0][cpt_y] != -1) {
        cpt_y++;
    }

    for (i = 0; i < cpt_x; i++) {
        for (j = 0; j < cpt_y ; j++) {
            int result = INT_MIN;
            if(tab[i][j] != -1){
                int val1 = INT_MIN,val2 = INT_MIN,val3 = INT_MIN;
                int min1 = INT_MIN, min2 = INT_MIN;

                if((i-1)>=0){
                    if((j-1)>=0){
                        min1 = tab[i - 1][j - 1];
                    }
                    min2 = tab[i-1][j];
                    min2 = (int) max(min1, min2);
                    min1 = INT_MIN;
                    if((j+1)<=(cpt_y)){
                        min1 = tab[i - 1][j + 1];
                    }
                    val1 = (int) max(min1,min2);
                }

                min1 = INT_MIN, min2 = INT_MIN;
                if((j-1)>=0){
                    min1 = tab[i][j - 1];
                    if(min1 == -1)
                        min1 = INT_MIN;
                }
                min2 = tab[i][j];
                min2 = (int) max(min1, min2);
                min1 = INT_MIN;
                if((j+1)<(cpt_y)){
                    min1 = tab[i][j + 1];
                    if(min1 == -1)
                        min1 = INT_MIN;
                }
                val2 = (int) max(min1,min2);

                if((i+1)<=(cpt_x)){
                    if((j-1)>=0){
                        min1 = tab[i + 1][j - 1];
                        if(min1 == -1)
                            min1 = INT_MIN;
                    }
                    min2 = tab[i+1][j];
                    if(min2 == -1)
                        min2 = INT_MIN;
                    min2 = (int) max(min1, min2);
                    min1 = INT_MIN;
                    if((j+1)<=(cpt_y)){
                        min1 = tab[i + 1][j + 1];
                        if(min1 == -1)
                            min1 = INT_MIN;
                    }
                    val3 = (int) max(min1,min2);
                }

                result = (int) max((int)max(val1,val2),val3);

            } else{
                result = -1;
            }

            tab[i][j] = result;

        }
    }


    for (i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);
        char* buf = (char*) malloc(sizeof(char*)*strlen(line));

        for (j = 0; j < cpt_y; j++) {
            if(tab[i][j] != -1){
                char str[12] = {""};
                sprintf(str,"%d%c",tab[i][j],' ');
                sprintf(buf, "%s%s",buf,str);
            }
        }
        sprintf(buf, "%s%s",buf,"\r\n");
        matrix[i] = buf;
    }

    image->data = matrix;
    return image;

}


Image_t *erosion(Image_t* image) {

    int tab[26000][80];
    int i, j, cpt_x = 0, cpt_y = 0;
    char *line;
    char ** matrix = (char **) malloc(999999*sizeof(char *));


    for (i = 0; i < 26000; i++) {
        for (j = 0; j < 80; j++) {
            tab[i][j] = -1;
        }
    }

    for (i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);

        cpt_y = 0;
        char* pch = strtok (line," ");
        while (pch != NULL && *pch != '\r')
        {
            size_t pixel = (size_t ) strtol(pch,NULL,10);
            tab[cpt_x][cpt_y] = (int) pixel;
            cpt_y++;
            pch = strtok (NULL, " ");
        }
        cpt_x++;
    }

    cpt_y = 0;
    while (tab[0][cpt_y] != -1) {
        cpt_y++;
    }



    for (i = 0; i < (cpt_x); i++) {
        for (j = 0; j < (cpt_y); j++) {
            int result = INT_MAX;
            if(tab[i][j] != -1){
                int val1 = INT_MAX,val2 = INT_MAX,val3 = INT_MAX;
                int min1 = INT_MAX, min2 = INT_MAX;

                if((i-1)>=0){
                    if((j-1)>=0){
                        min1 = tab[i - 1][j - 1];
                    }
                    min2 = tab[i-1][j];
                    min2 = (int) min(min1, min2);
                    min1 = INT_MAX;
                    if((j+1)<=(cpt_y)){
                        min1 = tab[i - 1][j + 1];
                    }
                    val1 = (int) min(min1,min2);
                }

                min1 = INT_MAX, min2 = INT_MAX;
                if((j-1)>=0){
                    min1 = tab[i][j - 1];
                    if(min1 == -1)
                        min1 = INT_MAX;
                }
                min2 = tab[i][j];
                min2 = (int) min(min1, min2);
                min1 = INT_MAX;
                if((j+1)<=(cpt_y)){
                    min1 = tab[i][j + 1];
                    if(min1 == -1)
                        min1 = INT_MAX;
                }
                val2 = (int) min(min1,min2);

                if((i+1)<(cpt_x)){
                    if((j-1)>=0){
                        min1 = tab[i + 1][j - 1];
                        if(min1 == -1)
                            min1 = INT_MAX;
                    }
                    min2 = tab[i+1][j];
                    if(min2 == -1)
                        min2 = INT_MAX;
                    min2 = (int) min(min1, min2);
                    min1 = INT_MAX;
                    if((j)<=(cpt_y)){
                        min1 = tab[i + 1][j + 1];
                        if(min1 == -1)
                            min1 = INT_MAX;
                    }
                    val3 = (int) min(min1,min2);
                }

                result = (int) min((int)min(val1,val2),val3);

            } else{
                result = -1;
            }

            tab[i][j] = result;

        }
    }

    for (i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);
        char* buf = (char*) malloc(sizeof(char*)*strlen(line));

        for (j = 0; j < cpt_y; j++) {
            if(tab[i][j] != -1){
                char str[12] = {""};
                sprintf(str,"%d%c",tab[i][j],' ');
                sprintf(buf, "%s%s",buf,str);
            }
        }
        sprintf(buf, "%s%s",buf,"\r\n");
        matrix[i] = buf;
    }

    image->data = matrix;
    return image;
}

Image_t *grey_yo_bw(Image_t *image) {

    char ** matrix = (char **) malloc(999999*sizeof(char *));
    char *line;
    int k = 0;

    size_t v_max = image->nbColor;

    printf("Veillez indiquer une valeur entre 0 et %zu :\t",v_max);
    scanf("%d",&k);



    for (int i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);
        char* buf = (char*) malloc(sizeof(char*)*strlen(line));

        char* pch = strtok (line," ");
        while (pch != NULL && *pch != '\r')
        {
            size_t pixel = (size_t ) strtol(pch,NULL,10);
            int pixel_t = (((int )pixel)>k)?((int)v_max):0;
            char str[12] = {""};
            sprintf(str,"%d%c",pixel_t,' ');
            sprintf(buf, "%s%s",buf,str);
            pch = strtok (NULL, " ");
        }
        sprintf(buf, "%s%s",buf,"\r\n");
        matrix[i] = buf;
    }

    image->data = matrix;


    return image;

}


Histogramme_t *histogram_image(Image_t *image) {

    Histogramme_t *root = NULL, *item, *ptr, *queue = NULL;
    char *line;

    for (int i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);

        char* pch = strtok (line," ");
        while (pch != NULL && *pch != '\r')
        {
            long pixel = strtol(pch,NULL,10);
            item = ((Histogramme_t *) malloc( sizeof(Histogramme_t)));
            bool stop = true;

            if (!root){
                item->intensite = (int) pixel;
                item->nbIntensite = 1;
                item->suiv = NULL;
                root = item;
                queue = item;
            } else{
                ptr = root;

                while (ptr){
                    if(ptr->intensite == ((int )pixel)){
                        stop = false;
                        (ptr->nbIntensite)++;
                        break;
                    }
                    ptr = ptr->suiv;
                }

                if(stop){
                    item->intensite = (int) pixel;
                    item->nbIntensite = 1;
                    item->suiv = NULL;
                    queue->suiv = item;
                    queue = item;
                }

            }
            pch = strtok (NULL, " ");
        }
    }

    return root;
}

Image_t *adapt_contrast_image(Image_t *image_t, double k) {

    Image_t *image;
    char ** matrix = (char **) malloc(999999*sizeof(char *));
    char *line;

    image = image_t;

    size_t v_max = image->nbColor;

    for (int i = 0; i < image->nbLigneData; i++) {
        line = (char *) malloc(strlen(image->data[i])*sizeof(char *));
        strcpy(line,image->data[i]);
        char* buf = (char*) malloc(sizeof(char*)*strlen(line));

        char* pch = strtok (line," ");
        while (pch != NULL && *pch != '\r')
        {
            size_t pixel = (size_t ) strtol(pch,NULL,10);
            int pixel_t = (int) max(min(k*pixel,v_max),0);
            char str[12] = {""};
            sprintf(str,"%d%c",pixel_t,' ');
            sprintf(buf, "%s%s",buf,str);
            pch = strtok (NULL, " ");
        }
        sprintf(buf, "%s%s",buf,"\r\n");
        matrix[i] = buf;
    }

    image->data = matrix;


    return image;
}

double max(double x, double y) {
    return (x>=y)?x:y;
}

double min(double x,double y) {
    return (x<=y)?x:y;
}

bool write_image(Image_t *image,char *imageName) {
    FILE *fd;
    char line[100];

    fd = fopen(imageName,"w");
    if(fd == NULL){
        printf("erreur lors de l'ouverture");
        return false;
    }

    fprintf(fd,"%s\n",image->nbMagique);
    fprintf(fd,"%zu %zu\n",image->width,image->height);
    fprintf(fd,"%zu\n",image->nbColor);
    for (int i = 0; i < image->nbLigneData;i++) {
        fprintf(fd,"%s",image->data[i]);
    }

    return true;
}

Image_t * read_image(char *imageName) {
    FILE *fd;
    char ok[200],
            wrong[200];
    char line[100];


    strcpy(ok,"../tests/ok/");
    strcpy(wrong,"../tests/wrong/");




    fd = fopen(imageName,"r");
    if(fd == NULL){
        strcat(ok,imageName);
        fd = fopen(ok,"r");
        if (fd == NULL){
            strcat(wrong,imageName);
            fd = fopen(wrong,"r");
            if (fd == NULL){
                printf("erreur lors de l'ouverture");
                return NULL;
            }
        }
    }



    bool doIt = true, nbColor = true;
    Image_t* image_t;
    image_t = malloc(sizeof(image_t));
    long cpt = 0;

    fgets(line,sizeof(line),fd);

    if(line == "P2"){
        return NULL;
    } else{
        strcpy(image_t->nbMagique,"P2");
    }
    char ** matrix = (char **) malloc(999999*sizeof(char *));


    while(fgets(line,sizeof(line),fd)){
        if(line[0]!='#' && strlen(line)>0){
            if (doIt){
                char** tokens;
                tokens = str_split(line, ' ');
                if (tokens)
                {
                    image_t->width = (size_t ) strtol(*(tokens),NULL,10);
                    image_t->height = (size_t ) strtol(*(tokens+1),NULL,10);
                    free(*(tokens));
                    free(*(tokens+1));
                    free(tokens);
                }
                doIt = !doIt;
            } else{
                if(nbColor){
                    image_t->nbColor = (size_t) strtol(line,NULL,10);
                    nbColor = !nbColor;
                } else{
                    char* line_t = (char*) malloc(strlen(line)*sizeof(char*));
                    strcpy(line_t,line);
                    matrix[cpt] = line_t;
                    cpt++;
                }
            }
        }
    }

    image_t->data = matrix;
    image_t->nbLigneData = cpt;

    return image_t;
}

void pause(){
    printf("Appuyer sur Entree pour continuer ");
    getchar();
    system("clear");
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    long count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);


    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char **) malloc(sizeof(char*) * count);

    if (result)
    {
        long idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}