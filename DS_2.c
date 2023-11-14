#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char game[20][20];

void display(char arr[20][20]){         // the basic map aside from character and snake
    system("clear");
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int getRandom() {
    int randomNumber = rand() % 18 + 1;

    return randomNumber;
}


int main(){

    printf("Press any key to start\n");

    srand(time(0)); // Seed for random number generation

    // Read map from file
    FILE *file = fopen("/Users/adityagupta/Desktop/work/c++/mymap.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }
    int map_row, map_col;
    if (fscanf(file, "%d %d", &map_row, &map_col) != 2) {
        perror("Error reading metadata from file");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            game[i][j] = ' ';
        }
    }

    // Read object coordinates from file
    int object_row, object_col;
    char object_code;

    while (fscanf(file, "%d %d %c", &object_row, &object_col, &object_code) == 3) {
        game[object_row][object_col] = object_code;
    }

    fclose(file);

    int pX = 15;
    int pY = 15;

    game[pX][pY] = '^';

    int gX = getRandom();
    int gY = getRandom();

    game[gX][gY] = 'O';

    int sX = getRandom();
    int sY = getRandom();

    game[sX][sY] = '~';


    while(1){
        char ch;
        scanf(" %c", &ch);

        if (game[gX][gY] == game[pX][pY]) {
            printf("YOU WIN\n");
            break;
        }

        if (game[pX][pY] == game[sY][sX]) {
            printf("YOU LOSE\n");
            break;
        }

        if(ch == 'w'){
            if(pX > 1){
                game[pX][pY] = ' ';
                pX--;
                game[pX][pY] = '^';
            }
        }
        if (ch == 's') {
            if (pX < 18) {
                game[pX][pY] = ' ';
                pX++;
                game[pX][pY] = 'v';
            }
        }
        if (ch == 'd') {
            if (pY < 18) {
                game[pX][pY] = ' ';
                pY++;
                game[pX][pY] = '>';
            }
        }
        if (ch == 'a') {
            if (pY > 1) {
                game[pX][pY] = ' ';
                pY--;
                game[pX][pY] = '<';
            }
        }

        int diffX = pY - sY;
        int diffY = pX - sX;

        if (abs(diffX) > abs(diffY)) {
            if (diffX > 0 && sY < 18) {
                game[sX][sY] = ' ';
                sY++;
                game[sX][sY] = '~';
            } else if (diffX < 0 && sY > 1) {
                game[sX][sY] = ' ';
                sY--;
                game[sX][sY] = '~';
            }
        } else {
            if (diffY > 0 && sX < 18) {
                game[sX][sY] = ' ';
                sX++;
                game[sX][sY] = '~';
            } else if (diffY < 0 && sX > 1) {
                game[sX][sY] = ' ';
                sX--;
                game[sX][sY] = '~';
            }
        }

        display(game);
    }

    return 0;

}
