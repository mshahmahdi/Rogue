#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>

#define WIDTH 200
#define HEIGHT 50



typedef struct{
    char name[50];
    char pas[50];
    char email[60];
    int score;

} hinfo;


void print_margin();
void inter_menu();


int main(){

    initscr();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    FILE * names; FILE * passwords;
    FILE * emails; FILE * scores;
    //print_margin();
    getch();
    inter_menu();
    refresh();
    getch();
    getch();
    getch();
    endwin();


    return 0;
}



void print_margin(){
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    for (int i = 0; i < 200; i++) {
        mvprintw(0, i, "#");           
        mvprintw(50 - 1, i, "#");   
    }
    for (int i = 0; i < 50; i++) {
        mvprintw(i, 0, "#");            
        mvprintw(i, 200 - 1, "#");    
    }
    refresh();
    attroff(COLOR_PAIR(1));
}

void inter_menu(){
    start_color();
    clear();
    print_margin();

    char * choices[] = {"Creat new account, sign in"};

    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvprintw(3, 98 , "ROGUE");
    refresh();
    attroff(COLOR_PAIR(2));



}