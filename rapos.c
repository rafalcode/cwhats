/* hopefully less hilarious than hilarious exercise reading from a binary ped (bed0 file */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<sys/stat.h>

#define SEED 122
#define CHUNKS16 200
#define MINX -5
#define MINY -5
#define MAXX 5
#define MAXY 5
/* you however need the sample number ... */

typedef struct
{
    int x, y;
} pos_t;

int rfill16(pos_t *p, int *ind, int minx, int miny, int maxx, int maxy)
{
    unsigned x;
    int j, jj; 
    int i=*ind;
    int rn=rand();
    unsigned char firsttime=(i==0)?1:0;
    int startj=(firsttime)?1:0;
    for(j=startj;j<16;j++) {
        jj=j*2;
        x=(rn>>jj)&0x03;
        switch(x) {
            case 0x00:
                p[i+j].x = p[i+j-1].x+1; p[i+j].y = p[i+j-1].y; break; // horizontal right move only, vert same as previous
            case 0x01:
                p[i+j].y = p[i+j-1].y-1; p[i+j].x = p[i+j-1].x; break; // vertical down move only
            case 0x02:
                p[i+j].x = p[i+j-1].x-1; p[i+j].y = p[i+j-1].y; break; // horizon left move
            case 0x03:
                p[i+j].y = p[i+j-1].y+1; p[i+j].x = p[i+j-1].x; break; // vert up move
        }
        printf("step%i:(%i,%i)\n", i+j, p[i+j].x, p[i+j].y);
        if((p[i+j].x == minx) | (p[i+j].y == miny) | (p[i+j].x == maxx) | (p[i+j].y == maxy)) {
            *ind += j+1;
            return 1;
        }
    }
    *ind+=15; // next index
    return 0;
}

int main(int argc, char *argv[])
{
    srand(SEED);
    pos_t *pos=calloc(1, sizeof(pos_t));
    int i, ind=0;

    int minx=MINX, miny=MINY, maxx=MAXX, maxy=MAXY, ret;
    ret=0;
    i=0;
    while((!ret) & (i<CHUNKS16)) {
        // printf("ind=%i\n", ind); 
        pos=realloc(pos, (ind+16)*sizeof(pos_t));
        ret=rfill16(pos, &ind, minx, miny, maxx, maxy);
        printf("ret=%i\n", ret);
        i++;
    }
    // for(i=0;i<CHUNKS16*16;++i) 
    //     printf("(%i,%i) ", pos[i].x, pos[i].y);
    // printf("\n"); 
    printf("round=%i;ind=%i:(%i,%i)\n", i, ind-1, pos[ind-1].x, pos[ind-1].y);

    free(pos);
    return 0;
}
