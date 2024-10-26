#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc==1) {
		printf("Error. Pls lst of filenames, i.e. *.\n");
		exit(EXIT_FAILURE);
	}
    int i,j;

    size_t ln;
    wchar_t *nn=calloc(1024, sizeof(wchar_t));
    unsigned cc;
    char n2[1024];
    bool ych=false; // yes change

    for(j=1;j<argc;++j) {
        ln=strlen(argv[j]);
        for(i=0;i<ln;++i) {
            cc=(unsigned)argv[j][i];
            switch(cc){
                case 0xFFFFFFAC:
                    // ecirconflex
                    nn[i]=L'ê'; ych=true; break;
                case 0xFFFFFF82: case 0xFFFFFFE9:
                // case 0xFFFFFFC3: dangerous ... will convert and cut off a name if there's an egrave!
                    // eacute
                    nn[i]=L'é'; ych=true; break;
                case 0xFFFFFF8a: case 0xFFFFFFBF: case 0xFFFFFFEB: case 0xFFFFFFE8:
                    // egrave the EB could be cpaital egrave, not sure.
                    nn[i]=L'è'; ych=true; break;
                case 0xFFFFFF85: case 0xFFFFFFE0:
                    // agrave
                    nn[i]=L'à'; ych=true; break;
                case 0xFFFFFFE1:
                    // ß thought it was agrave!
                    nn[i]=L'ß'; ych=true; break;
                case 0xFFFFFF84: case 0xFFFFFFE4:
                    // aumlaut
                    nn[i]=L'ä'; ych=true; break;
                case 0xFFFFFFF6: case 0xFFFFFFF7: case 0xFFFFFF94:
                    // oumlaut
                    nn[i]=L'ö'; ych=true; break;
                case 0xFFFFFF81:
                    // uumlaut
                    nn[i]=L'ü'; ych=true; break;
                case 0xFFFFFFA2:
                    // &#242; or ograve, as in "che farò senza Euridice" that's Italian for you.
                    nn[i]=L'ò'; ych=true; break;
                case 0xFFFFFFF9:
                    // ugrave, as in "più"
                    nn[i]=L'ù'; ych=true; break;
                default:
                    nn[i]=argv[j][i];
            }
            // printf("%c:%x ", argv[1][i], argv[1][i]);
        }
        if(ych) {
            wcstombs(n2, nn, sizeof(n2));
            printf("WOULDREN: %s --> %s\n", argv[j], n2);
            ych=false;
        } 

        memset(nn, 0, 1024*sizeof(wchar_t));
    }

    // printf("Res_1: %s\n", argv[1]);

    free(nn);
    return 0;
}
