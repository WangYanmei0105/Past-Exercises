#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int finished_map(int max, char **map);
int free_cell_for_letter(int row, int col, char letter, char** map, int max);
void trans_sub_square(char **map, char buffer[], int row, int col, int size);
void resolve(int max, char** map);
int exclusion_in_a_region(int row, int col, char **map, int size);

int size, max;
char **map;
char letters[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
//char letters[26]={'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'K', 'L', 'M', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(){
    FILE *fp=fopen("input5.txt", "r");
    /*read map*/
    char read[256];
    fgets(read,255,fp);
    size=atof(&read[0]);//size: n
    max=size*size;//max: number for resolve; n^2
    map=(char **)malloc(max*sizeof(char *));//a pointer of pointers
    for (int i=0; i<=max-1; i++) map[i]=(char *)malloc(size*sizeof(char));//pointer to chars
    for (int i=0; i<=max-1; i++){
        fgets(read,255,fp);
        for (int j=0, n=0; j<=255; j++){
            if (read[j]!=' ' && read[j]!='\\' && read[j]!='n') map[i][n++]=read[j];
        }
    }
    for (int i=0; i<=max-1; i++) printf("%s\n", map[i]);
    fclose(fp);
    resolve(max, map);
    //for (int i=0; i<=max-1; i++) printf("%s\n", map[i]);
    fp=fopen("Output.txt", "w");
    for (int i=0; i<max; i++) {
        for (int j=0; j<max; j++){
            fprintf(fp, "%c ", map[i][j]);
            if ((j%size==size-1) && j<max-1) fprintf(fp, "\t");
        }
        fprintf(fp, "\n");
        if ((i%size==size-1) && i<max-1) fprintf(fp, "\n");
    }
    fclose(fp);
    free(map);
    return 0;
}

///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void resolve(int max, char** map){
    int row, col;
    char buffer_number[5]={""};
    for (row=0; row<max; row++) {
        for (col=0; col<max; col++){
            if (map[row][col]!='-') continue;
            for (int i=0; i<max; i++){
                if (! free_cell_for_letter(row, col, letters[i], map, size)) continue;
                buffer_number[0] = map[row][col];
                map[row][col] = letters[i];
                /*这里放上循环：Method by exclusion in a region， column and row*/
                //for (int i=0; i<=max-1; i++) printf("%s\n", map[i]);
                exclusion_in_a_region(row, col, map, size);
                resolve(max, map);
                
                if (finished_map(max, map)) return;
                map[row][col]=buffer_number[0];
            }
            return;
        }
    }
    return;
}
///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////

int free_cell_for_letter(int row, int col, char letter, char** map, int size){
    int result=TRUE;
    char buffer[40]={""};
    for (int j=0; j<max; j++) if(map[j][col]==letter){
        //printf("Here");
        result=FALSE;
    }
    for (int j=0; j<max; j++) if(map[row][j]==letter) result=FALSE;
    trans_sub_square(map, buffer, row, col, size);
    for (int j=0; j<max; j++) if(buffer[j]==letter) result=FALSE;
    return result;
}

int exclusion_in_a_region(int row, int col, char **map, int size){
    int result=TRUE;
    //first check and mark
    //for (int i=0; i<size; i++) printf("%s\n", map[i]);
    for (int k=0; k<max; k++){
        char **map_t=(char **)malloc(max*sizeof(char *));
        for (int i=0; i<max; i++) map_t[i]=(char *)malloc(max*sizeof(char));
        for (int i=0; i<max; i++) for (int j=0; j<max; j++) map_t[i][j]='-';
        for (int r=0; r<max; r++){
            for (int c=0; c<max; c++){
                if (map[r][c]==letters[k]){//mark the region, the row and the col
                    //1:mark the region
                    int check_row=r/size+1, check_col=c/size+1;
                    for (int i=0; i<=max-1; i++){
                        for (int j=0; j<=max-1; j++) if (i/size+1==check_row && j/size+1==check_col) map_t[i][j]='*';
                    }
                    //for (int i=0; i<=max-1; i++) printf("%s\n", map_t[i]);
                    //2:mark row
                    for (int i=0; i<=max-1; i++) {
                        map_t[r][i]='*';
                    }
                    for (int i=0; i<=3; i++) {
                        map_t[i][c]='*';
                        //printf("map[%d][%d]=%c.\n", i, c, map_t[i][c]);
                        //for (int i=0; i<=max-1; i++) printf("%s\n", map_t[i]);
                    }
                    //printf("map_t[3]=%s\n", map_t[1]);
                    //for (int i=0; i<=max-1; i++) printf("%s\n", map_t[i]);
                    //for (int i=0; i<size; i++) printf("%s\n", map_t[i]);
                }
            }
        }
        //for (int i=0; i<=max-1; i++) printf("%s\n", map_t[i]);
        for (int r=0; r<max; r++){
            for (int c=0; c<max; c++){
                char buffer[40]={""};
                trans_sub_square(map_t, buffer, r, c, size);
                int n=0;
                for (long i=0; i<strlen(buffer); i++){
                    if (buffer[i]=='*') n++;
                }
                if (n==max-1){
                    int check_row=r/size+1, check_col=c/size+1;
                    for (int i=0; i<max; i++){
                        for (int j=0; j<max; j++){
                            if (i/size+1==check_row && j/size+1==check_col && map_t[r][c]!='*'){
                                map[r][c]=letters[k];
                            }
                        }
                    }
                }
            }
        }
        //for (int i=0; i<=max-1; i++) printf("%s\n", map[i]);
        for (int i=0; i<max; i++) free(map_t[i]);
        free(map_t);
    }
    return result;
}

///// ///// ///// ///// ///// ///// ///// ///// ///// ///// /////
void trans_sub_square(char **map, char buffer[], int row, int col, int size){
    /* Transfer the sub-square of size x size into a one-dimensional array. */
    /*1: find which sub_square the letter is in*/
    int check_row=row/size+1, check_col=col/size+1, n=0;
    for (int i=0; i<max; i++){
        for (int j=0; j<max; j++){
            if (i/size+1==check_row && j/size+1==check_col){
                buffer[n++]=map[i][j];
            }
        }
    }
    return;
}

int finished_map(int max, char **map){
    int row, col;
    for (row = max-1; row >= 0; row--) {
        for (col = max-1; col >= 0; col--) {
            if (map[row][col] == '-' ) {
                return FALSE;
                }
            }/* end for col */
        }/* end for row */
    return TRUE;
}
