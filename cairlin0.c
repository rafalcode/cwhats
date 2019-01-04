/* taken from lintx2.c a very old program */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo/cairo.h>

#define VBARNUMS 6
#define NUMHBARS 6
#define STRBUF 128 /* ample but not excessive buffer, woul dneed to be modified later */
#define STRPBUF 128 /* ample but not excessive buffer, woul dneed to be modified later */
#define NAMBUF 32 /*  colour name length */

typedef struct {
    char nam[NAMBUF];
    float rgb[3];
} colstru_f;

void creatch(cairo_t *cr, char *alphabet, int im_w, int im_h)
{
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 14.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;
    char letter[2]; /* this will be where we put our individual characters, with the null char to mark them out */

    cairo_font_extents (cr, &fe);

    int i;

    for (i=0; i < strlen(alphabet); i++) {
        *letter = '\0';
        strncat (letter, alphabet + i, 1);

        cairo_text_extents (cr, letter, &te);
        cairo_move_to (cr, i*15 + im_w/2-90 - te.x_bearing - te.width / 2, im_h/2 - fe.descent + fe.height / 2);
        cairo_show_text (cr, letter);
    }
}

void creatstr(cairo_t *cr, char *alphabet, int cnv_w, int cnv_h)
{
/*  this function is like creatch, except not processed char by char, but by whole string
 *  mne for cnv is canvas */
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 16.0);

    cairo_font_extents_t fe;
    cairo_text_extents_t te;

    cairo_font_extents (cr, &fe);


    cairo_text_extents (cr, alphabet, &te);
    cairo_move_to (cr, cnv_w/2 - te.x_bearing - te.width/2, cnv_h/2 - fe.descent + fe.height / 2);
    cairo_show_text (cr, alphabet);
}

int main (int argc, char *argv[])
{
    colstru_f colsf[18] = { {"foreground", {0.866667, 0.866667, 0.866667} }, {"background", {0.066667, 0.066667, 0.066667} }, {"color0", {0.098039, 0.098039, 0.098039} }, {"color8", {0.627451, 0.321569, 0.176471} }, {"color1", {0.501961, 0.196078, 0.196078} }, {"color9", {0.596078, 0.168627, 0.168627} }, {"color2", {0.356863, 0.462745, 0.184314} }, {"color10", {0.537255, 0.721569, 0.247059} }, {"color3", {0.666667, 0.600000, 0.262745} }, {"color11", {0.937255, 0.937255, 0.376471} }, {"color4", {0.196078, 0.298039, 0.501961} }, {"color12", {0.168627, 0.309804, 0.596078} }, {"color5", {0.439216, 0.423529, 0.603922} }, {"color13", {0.509804, 0.415686, 0.694118} }, {"color6", {0.572549, 0.694118, 0.619608} }, {"color14", {0.631373, 0.803922, 0.803922} }, {"color7", {1.000000, 1.000000, 1.000000} }, {"color15", {0.866667, 0.866667, 0.866667} } };

    int i, im_w=640, im_h=480;
    int lmarp=(int)im_w*.05; // left margin ... but the position, mind.
    int rmarp=im_w - lmarp; //right margin ... but the position, mind.
    char ch;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, im_w, im_h);
    cairo_t *cr = cairo_create (surface);

    /*  first we're going to set the background */
    cairo_rectangle (cr, 0, 0, im_w, im_h); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* argument accounting: we're going to pull our text from a file */
//    FILE *ftin;
    int j=0, k=0;
    char **txt;
//     txt=malloc(sizeof(char *)*STRPBUF);
//     for(i=0; i<STRPBUF; ++i) 
//         txt[i]=malloc(sizeof(char)*STRBUF);
    /* without prev file knowledge apply string buffers */
//    if(argc!=2) {
//        printf("Error. Pls supply appropriate arguments (filename with text in it).\n");
//        exit(EXIT_FAILURE);
//    }
//    ftin=fopen(argv[1],"r");
//    while((ch=fgetc(ftin)) != EOF) {
//        if(ch == '\n') {
//            txt[j++][k] ='\0';
//            k = 0;
//        } else 
//            txt[j][k++] =ch;
//    }

    /* vertical divider how ar ewe going to section off the screen vertically */
    int hbarh=im_h/NUMHBARS; // hbar height.
    int vposl[NUMHBARS]={0}; // vertical position of the lines
    /* arrange array of vert line positions */
    vposl[0]=3*hbarh/4;
    for(i=1;i<NUMHBARS;i++)
        vposl[i] = vposl[i-1] + hbarh;

/* dot placement */
    cairo_set_source_rgb(cr, 0.85, 0.1, 0.2);
    cairo_set_source_rgb(cr, 1., 1. , 1.);
    for(i=0;i<NUMHBARS;i++) {
        cairo_arc(cr, lmarp+i*im_w/NUMHBARS, vposl[i], 3, 0, 2 * M_PI);
        cairo_fill(cr);
    }

    /* Drawing code goes here */
    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 1.0);
    cairo_set_line_width (cr, 3); /* thinnest really possible */
    for(i=0;i<NUMHBARS;i++) {
        cairo_move_to(cr, lmarp, vposl[i]);
        cairo_line_to(cr, rmarp, vposl[i]);
        cairo_stroke (cr);
    }
    /*  we want some text now. We have a function, but actually to set color
     *  we need to set color for the whole "cr"  */
    cairo_set_source_rgba (cr, 0.7, 0.6, 0.75, 0.8);
    for(i=0; i<j; ++i) 
        creatstr(cr, "NUMHBARS", im_w, im_h*(i+1)/4);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "cairlin0.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    //for(i=0; i<STRPBUF; ++i) 
    //    free(txt[i]);
    //free(txt);

    return 0;
}
