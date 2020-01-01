/* where we hard code a 0-5 number sequence to progress row-wise
 * pretty easy as that is the default for printf */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	if(argc!=3) {
        printf("Needs 2 args: 1) nrows & 2) ncols grid layout (math-style nrows=M, ncols=N for MxN).\n"); 
		exit(EXIT_FAILURE);
	}
    int i, j;
    const int nrows=atoi(argv[1]);
    const int ncols=atoi(argv[2]);
    const int nclines=nrows*ncols;

    int *arr1=malloc(nclines*sizeof(int));
    int *arr2=malloc(nclines*sizeof(int));
    int *arr3=malloc(nclines*sizeof(int));
    /* OK, we're going to create an array made up indices ... quite articifial actually
     * because if it were really that way, it we could use use the naked indices of the forloop */
    for(j=0;j<nclines;++j) {
        arr1[j] = j;
    }

    /* original order is */
    printf("So here's a little story: we layout a series of samples which we label with consecutive numbers:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr1[i]); 
    printf("\n"); 
    printf("They are put into a %ix%i grid in \"row-wise\", meaning each row is completed, before moving to next:\n", nrows, ncols); 
    for(i=0;i<nrows;++i) {
        for(j=0;j<ncols;++j)
            printf("%i ", arr1[j+i*ncols]); 
        printf("\n"); 
    }
    printf("%ix%i column-wise grid layout:\n", nrows, ncols); 
    printf("However the samples are mistakenly analysed in columnwise fashion. Note the gird retains %ix%i dimensions:\n", nrows, ncols); 
    for(i=0;i<nrows;++i) {
        for(j=0;j<ncols;++j)
            printf("%i ", arr1[j*nrows+i]); 
        printf("\n"); 
    }

    /* convert */
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            arr2[i*ncols+j] = arr1[j*nrows+i]; 
    printf("After conversion, print straight out:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i ", arr2[j+i*ncols]); 
    printf("\n"); 

    printf("So what's happened? This mapping has occured:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i->%i ", arr1[j+i*ncols] , arr2[j+i*ncols]);
    printf("\n"); 
    printf("SO we need to reverse this\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i->%i ", arr2[j+i*ncols] , arr1[j+i*ncols]);
    printf("\n"); 

    /* reverse convert */
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            arr3[arr2[i*ncols+j]] = arr1[i*ncols+j];
    printf("New arr3:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i ", arr3[j+i*ncols]); 
    printf("\n"); 
    // k=0;
    // printf("Convert to row-wise:\n");
    // for(j=0;j<ncols;++j)
    //     for(i=0;i<nrows;++i)
    //         arr2[j*nrows+i] = arr1[j+i*ncols]; 
    // for(i=0;i<nclines;++i) 
    //     printf("%i ", arr2[i]); 
    // printf("\n"); 

    // printf("%ix%i grid layout:\n", nrows, ncols); 
    // for(i=0;i<nrows;++i) {
    //     for(j=0;j<ncols;++j)
    //         printf("%i ", arr2[j+i*ncols]); 
    //     printf("\n"); 
    // }

    free(arr1);
    free(arr2);
    free(arr3);

    return 0;
}
