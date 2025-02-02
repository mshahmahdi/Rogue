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
    char password[50];
    char email[60];
    int score;

} hinfo;


void print_margin();
void inter_menu(int * s_i_m, int * s_m, hinfo * hero, FILE * names, FILE * passwords, FILE * emails);
void print_option(int num_op, char * choices[]);
int sim_name(FILE * names, char name[]);
int is_valid_email(char email[]);
int is_valid_password(const char *str);
void creat_new_account(hinfo * hero, FILE * names, FILE * passwords, FILE * emails);
int find_name_in_file(FILE * file, char name[]);
int check_name_in_line(FILE * file, int n, char password[]);
void log_in(hinfo * hero, FILE * names, FILE * passwords);


int main(){

    initscr();
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    FILE * names; FILE * passwords;
    FILE * emails; FILE * scores;
    hinfo * hero = (hinfo *) malloc (sizeof(hinfo));

    int s_i_m = 1; int s_m = 0;
    //print_margin();
    getch();
    while(1){
        if(s_i_m == 1){
            inter_menu(&s_i_m, &s_m, hero, names, passwords, emails);
        }


    }

    //inter_menu();
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
void print_option(int num_op, char * choices[]){

    if(num_op%3 == 0){
        attron(A_REVERSE);
        mvprintw(8, 98, "%s", choices[0]);
        attroff(A_REVERSE);
        mvprintw(9, 98, "%s", choices[1]);
        mvprintw(10, 98, "%s", choices[2]);
        attron(COLOR_PAIR(3)); mvprintw(14, 75, "%s", choices[3]); attroff(COLOR_PAIR(3)); refresh();
    }
    else if(num_op%3 == 1){
        mvprintw(8, 98, "%s", choices[0]);
        attron(A_REVERSE);
        mvprintw(9, 98, "%s", choices[1]);
        attroff(A_REVERSE);
        mvprintw(10, 98, "%s", choices[2]);
        attron(COLOR_PAIR(3)); mvprintw(14, 75, "%s", choices[3]); attroff(COLOR_PAIR(3)); refresh();
    }
    else if(num_op%3 == 2){
        mvprintw(8, 98, "%s", choices[0]);
        mvprintw(9, 98, "%s", choices[1]);
        attron(A_REVERSE);
        mvprintw(10, 98, "%s", choices[2]);
        attroff(A_REVERSE);
        attron(COLOR_PAIR(3)); mvprintw(14, 75, "%s", choices[3]); attroff(COLOR_PAIR(3)); refresh();

    }
}
void inter_menu(int * s_i_m, int * s_m, hinfo * hero, FILE * names, FILE * passwords, FILE * emails){


    curs_set(FALSE);
    noecho();
    int num_op = 0;
    int key;
    char * choices[] = {"<<Creat new account>>", "<<Log in>>", "<<guest login>>", "Note: If you log in as a guest, your score will not be recorded."};

    while(1){

        clear();
        print_margin();
        attron(COLOR_PAIR(2));
        mvprintw(3, 98 , "ROGUE");
        print_option(num_op, choices);
        refresh();


        key = getch();
        
        if(key == KEY_UP){
            num_op -= 1;
            if(num_op < 0){
                num_op = 2;
            }
        }
        else if(key == KEY_DOWN){
            num_op += 1;
            if(num_op > 2){
                num_op = 0;
            }
        }
        else if(key == 10){
            break;
        }

    }

    attroff(COLOR_PAIR(2));

    if(num_op == 0){
        creat_new_account(hero, names, passwords, emails);
        *s_i_m = 0; *s_m = 1;
    }
    else if(num_op == 1){
        log_in(hero, names, passwords);
        *s_i_m = 0; *s_m = 1;
    }
    else if(num_op == 2){
        strcpy(hero->name, "guest");
        *s_i_m = 0; *s_m = 1;

    }

    
    noecho();
    
}
int sim_name(FILE * names, char name[]){
    names = fopen("names.txt", "a+");
    char line [100];
    while (fgets(line, sizeof(line), names)) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, name) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_valid_email(char email[]) {

    char *at = strchr(email, '@'); 
    char *dot = strrchr(email, '.');

    if (!at || !dot) return 0; 
    if (at == email || dot == email) return 0; 
    if (at > dot) return 0; 
    if (*(at + 1) == '.' || *(dot + 1) == '\0') return 0; 

    if (strchr(at + 1, '@')) return 0; 

    return 1; 
}
int is_valid_password(const char *str) {
    int has_upper = 0, has_lower = 0, has_digit = 0;

    while (*str) { 
        if (isupper(*str)) has_upper = 1;  
        if (islower(*str)) has_lower = 1;  
        if (isdigit(*str)) has_digit = 1;  
        str++; 

        if (has_upper && has_lower && has_digit)
            return 1;
    }
    return 0; 
}
void creat_new_account(hinfo * hero, FILE * names, FILE * passwords, FILE * emails){

    clear();
    start_color();
    curs_set(FALSE); noecho();
    char * name = (char *) malloc (50 * sizeof(char)) ; char  * password = (char *) malloc (50 * sizeof(char)); char  * email = (char *) malloc (60 * sizeof(char)); int score = 0;
    int sn = 0; int sp = 0; int se = 0;

    print_margin();
    attron(COLOR_PAIR(4));
    mvprintw(15, 60, "Enter your name :");
    mvprintw(19, 60, "Enter your password :");
    mvprintw(23, 60, "Enter your email :");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    mvprintw(17, 60, "(The name should not contain spaces or enter characters !)");
    mvprintw(21, 60, "(The password must be at least 7 characters long and include uppercase and lowercase English letters and numbers !)");
    mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
    attroff(COLOR_PAIR(3));
    refresh();
    
    curs_set(TRUE); echo();
    mvscanw(15, 90, "%s", name);
    if(strcmp(name, "") != 0){ sn = 1; } if(sim_name(names, name) == 0){ sn += 2; }
    curs_set(FALSE);

    
    while(1){
        
        if(sn == 1){
            sn = 0;
            clear();
            print_margin();
            attron(COLOR_PAIR(4));
            mvprintw(15, 60, "Enter your name :");
            mvprintw(19, 60, "Enter your password :");
            mvprintw(23, 60, "Enter your email :");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(17, 60, "(This name exists !)");
            mvprintw(21, 60, "(The password must be at least 7 characters long and include uppercase and lowercase English letters and numbers !)");
            mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
            attroff(COLOR_PAIR(3));
            refresh();

            curs_set(TRUE); echo();
            strcpy(name, ""); mvscanw(15, 90, "%s", name);
            if(strcmp(name, "") != 0){ sn = 1; } if(sim_name(names, name) == 0){ sn += 2; }
            curs_set(FALSE);  

        }

        else if(sn == 2){
            sn = 0;
            clear();
            print_margin();
            attron(COLOR_PAIR(4));
            mvprintw(15, 60, "Enter your name :");
            mvprintw(19, 60, "Enter your password :");
            mvprintw(23, 60, "Enter your email :");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(17, 60, "(The name should not contain spaces or enter characters !)");
            mvprintw(21, 60, "(The password must be at least 7 characters long and include uppercase and lowercase English letters and numbers !)");
            mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
            attroff(COLOR_PAIR(3));
            refresh();    

            curs_set(TRUE); echo();
            strcpy(name, ""); mvscanw(15, 90, "%s", name);
            if(strcmp(name, "") != 0){ sn = 1; } if(sim_name(names, name) == 0){ sn += 2; }
            curs_set(FALSE);   
        }

        else if(sn == 3){
            strcpy(hero->name, name);
            names = fopen("names.txt", "a+");
            fprintf(names, "\n%s", name);
            fclose(names);
            break;
        }

    }

    
    clear();
    print_margin();
    attron(COLOR_PAIR(4));
    mvprintw(15, 60, "Enter your name :"); mvprintw(15, 90, "%s", hero->name);
    mvprintw(19, 60, "Enter your password :");
    mvprintw(23, 60, "Enter your email :");
    mvprintw(17, 60, "(Correct name)");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    mvprintw(21, 60, "(The password must be at least 7 characters long and include uppercase and lowercase English letters and numbers !)");
    mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
    attroff(COLOR_PAIR(3));
    refresh();

    curs_set(TRUE); echo();
    mvscanw(19, 90, "%s", password);
    if(is_valid_password(password) == 1){ sp = 1; }
    curs_set(FALSE); 
    
    while(1){

        if(sp == 0){

            clear();
            print_margin();
            attron(COLOR_PAIR(4));
            mvprintw(15, 60, "Enter your name :"); mvprintw(15, 90, "%s", hero->name);
            mvprintw(19, 60, "Enter your password :");
            mvprintw(23, 60, "Enter your email :");
            mvprintw(17, 60, "(Correct name)");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(21, 60, "(The password is invalid !)");
            mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
            attroff(COLOR_PAIR(3));
            refresh();

            curs_set(TRUE); echo();
            strcpy(password, ""); mvscanw(19, 90, "%s", password);
            if(is_valid_password(password) == 1){ sp = 1; }
            curs_set(FALSE); 
        }

        else if(sp == 1){
            strcpy(hero->password, password);
            passwords = fopen("passwords.txt", "a+");
            fprintf(passwords, "\n%s", password);
            break;
        }

    }

    clear();
    print_margin();
    attron(COLOR_PAIR(4));
    mvprintw(15, 60, "Enter your name :"); mvprintw(15, 90, "%s", hero->name);
    mvprintw(19, 60, "Enter your password :"); mvprintw(19, 90, "%s", hero->password);
    mvprintw(23, 60, "Enter your email :");
    mvprintw(17, 60, "(Correct name)");
    mvprintw(21, 60, "(Correct password)");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    mvprintw(25, 60, "(The email must be in the format ""xxx@y.zzz"" !)");
    attroff(COLOR_PAIR(3));
    refresh();

    curs_set(TRUE); echo();
    mvscanw(23, 90, "%s", email);
    if(is_valid_email(email) == 1){ se = 1; }
    curs_set(FALSE); 

    while(1){
        if(se == 0){
        clear();
            print_margin();
            attron(COLOR_PAIR(4));
            mvprintw(15, 60, "Enter your name :"); mvprintw(15, 90, "%s", hero->name);
            mvprintw(19, 60, "Enter your password :"); mvprintw(19, 90, "%s", hero->password);
            mvprintw(23, 60, "Enter your email :");
            mvprintw(17, 60, "(Correct name)");
            mvprintw(21, 60, "(Correct password)");
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(3));
            mvprintw(25, 60, "(The email is not formatted correctly !)");
            attroff(COLOR_PAIR(3));
            refresh();

            curs_set(TRUE); echo();
            mvscanw(23, 90, "%s", email);
            if(is_valid_email(email) == 1){ se = 1; }
            curs_set(FALSE); 
        }
        else if(se == 1){
            strcpy(hero->email, email);
            passwords = fopen("emails.txt", "a+");
            fprintf(emails, "\n%s", email);

            clear();
            print_margin();
            attron(COLOR_PAIR(4));
            mvprintw(15, 60, "Enter your name :"); mvprintw(15, 90, "%s", hero->name);
            mvprintw(19, 60, "Enter your password :"); mvprintw(19, 90, "%s", hero->password);
            mvprintw(23, 60, "Enter your email :"); mvprintw(23, 90, "%s", hero->email);
            mvprintw(17, 60, "(Correct name)");
            mvprintw(21, 60, "(Correct password)");
            mvprintw(25, 60, "(Correct email)");
            getch();
            attroff(COLOR_PAIR(4));
            refresh();

            break;
        }

    }
}
int find_name_in_file(FILE * file, char name[]) {
    file = fopen("names.txt", "r");

    char line[256]; 
    int line_number = 0; 

    while (fgets(line, sizeof(line), file)) {
        line_number++; 

        line[strcspn(line, "\n")] = '\0';
        
        if (strcmp(line, name) == 0) {
            fclose(file); 
            return line_number; 
        }
    }

    fclose(file); 
    return -1; 
}
int check_name_in_line(FILE * file, int n, char password[]) {
    file = fopen("passwords.txt", "r");

    char line[256]; 
    int current_line = 1; 

    while (fgets(line, sizeof(line), file)) {
        
        if (current_line == n) {
            line[strcspn(line, "\n")] = '\0'; 
            if (strcmp(line, password) == 0) {
                fclose(file);
                return 1; 
            } else {
                fclose(file);
                return 0; 
            }
        }
        current_line++; 
    }

    fclose(file); 
    return 0; 
}
void log_in(hinfo * hero, FILE * names, FILE * passwords){

    char name[50]; char password[50];
    int sn = 0; int sp = 0;

    clear();
    print_margin();
    attron(COLOR_PAIR(2));
    mvprintw(20, 70, "Enter your name : ");
    mvprintw(24, 70, "Enter your password :");
    attroff(COLOR_PAIR(2));
    refresh();
    
    
    curs_set(TRUE); echo();
    mvscanw(20, 100, "%s", name); int line = find_name_in_file(names, name);
    if(line != -1){ sn = 1; }
    curs_set(FALSE); 

    while(1){
        if(sn == 0){

            clear();
            print_margin();
            attron(COLOR_PAIR(2));
            mvprintw(20, 70, "Enter your name : ");
            mvprintw(24, 70, "Enter your password :");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(3));
            mvprintw(22, 70, "(The name entered does not exist !)");
            attroff(COLOR_PAIR(3));
            refresh();
            
            
            curs_set(TRUE); echo();
            mvscanw(20, 100, "%s", name); line = find_name_in_file(names, name);
            if(line != -1){ sn = 1; }
            curs_set(FALSE);  
        }

        else if(sn == 1){
            break;

        }
    }

    clear();
    print_margin();
    attron(COLOR_PAIR(2));
    mvprintw(20, 70, "Enter your name : "); mvprintw(20, 90, "%s", name);
    mvprintw(24, 70, "Enter your password :");
    attroff(COLOR_PAIR(2));
    refresh();
    
    curs_set(TRUE); echo();
    mvscanw(24, 100, "%s", password); sp = check_name_in_line(passwords, line, password);
    curs_set(FALSE); 

    while(1){
        if(sp == 0){
            
            clear();
            print_margin();
            attron(COLOR_PAIR(2));
            mvprintw(20, 70, "Enter your name : "); mvprintw(20, 90, "%s", name);
            mvprintw(24, 70, "Enter your password :");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(3));
            mvprintw(26, 70, "The password entered is incorrect !");
            attroff(COLOR_PAIR(3));
            refresh();
            
            curs_set(TRUE); echo();
            mvscanw(24, 100, "%s", password); sp = check_name_in_line(passwords, line, password);
            curs_set(FALSE); 
        }

        else if(sp == 1){
            clear();
            print_margin();
            attron(COLOR_PAIR(2));
            mvprintw(20, 70, "Enter your name : "); mvprintw(20, 90, "%s", name);
            mvprintw(24, 70, "Enter your password :"); mvprintw(24, 90, "%s", password);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(4));
            mvprintw(26, 70, "You have successfully logged in !");
            attroff(COLOR_PAIR(4));
            refresh();
        
            break;
        }
    }
    
}