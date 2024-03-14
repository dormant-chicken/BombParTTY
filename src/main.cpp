/*
 ____                  _     ____           _____ _______   __
| __ )  ___  _ __ ___ | |__ |  _ \ __ _ _ _|_   _|_   _\ \ / /
|  _ \ / _ \| '_ ` _ \| '_ \| |_) / _` | '__|| |   | |  \ V / 
| |_) | (_) | | | | | | |_) |  __/ (_| | |   | |   | |   | |  
|____/ \___/|_| |_| |_|_.__/|_|   \__,_|_|   |_|   |_|   |_|  
*/

#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <cstring>
#include <time.h>

using std::cout, std::cin, std::string, std::ifstream;

int find_length(string path) {
    // opens file
    ifstream file;
    file.open(path);

    // variables
    int length = 0;
    string line;

    // finds length of file
    while(getline(file, line)) {
        length++;
    }

    file.close();

    return length;
}

void draw_boxes(int term_max_y, int term_max_x, int start_x, int start_y) {
    WINDOW *back = newwin(term_max_y, term_max_x, 0, 0);
    WINDOW *input_win = newwin(3, term_max_x - 7, start_y, start_x);
    refresh();

    box(back, 0, 0);
    box(input_win, 0, 0);
    wrefresh(back);
    wrefresh(input_win);
}

void redraw_screen(int term_max_y, int term_max_x, int start_x, int start_y, string message, int message_y, int message_x) {
    clear();

    draw_boxes(term_max_y, term_max_x, start_x, start_y);

    // writes message and returns to proper position
    move(message_y, message_x);
    addstr(message.c_str());

    move(start_y + 1, start_x + 1);
}

int argument_warning(int argc, char* argv[], string argument, string warning, bool condition) {
    int temp = 0;
    
    // loops through arguments to check if specified argument is used
    for(int i = 0; i < argc; i++) {
        if(argv[i] == argument) {
            temp = 1;
        }
    }

    // if specified condition is not met and specified argument is not passed, give error
    if(condition && temp != 1) {
        mvaddstr(0, 0, warning.c_str());
        // mvprintw is used rather than mvaddstr because a variable (converted to char string) is printed alongside a string
        mvprintw(1, 0, "You can bypass this warning with the '%s' flag", argument.c_str());
        
        mvaddstr(2, 0, "This may cause unwanted problems, so be warned when doing so");
        mvaddstr(4, 0, "Press any key to exit");
        
        getch();

        return -1;
    }

    return 0;
}


int main(int argc, char* argv[])
{
    // copies words from dictionary file to array
    int length = find_length("/usr/local/bin/bomb-partty-bin/dictionary.txt");

    string line;

    // declare dictionary array with length variable found in find_length function
    string dictionary[length];

    // opens file
    ifstream file;
    file.open("/usr/local/bin/bomb-partty-bin/dictionary.txt");

    // goes through file again and fills array using file
    for(int i = 0; getline(file, line); i++) {
        dictionary[i] = line;
    }

    file.close();

    // curses initialization
    initscr();
    noecho();
    cbreak();
    timeout(-1);

    // main variable initialization
    bool quit = false;
    int c, term_max_y, term_max_x, start_x, start_y, check, points, error;

    getmaxyx(stdscr, term_max_y, term_max_x);

    start_y = term_max_y - 4;
    start_x = 3;
    check = 0;
    points = 0;
    string input;

    // checks terminal height
    error = argument_warning(argc, argv, "--bypass-term-height", "Terminal height is too small!", term_max_y < 20);
    if(error == -1) {
        endwin();
        return -1;
    }

    // checks terminal width
    error = argument_warning(argc, argv, "--bypass-term-width", "Terminal width is too small!", term_max_x < 55);
    if(error == -1) {
        endwin();
        return -1;
    }

    // draw the screen with help message before any player input
    redraw_screen(term_max_y, term_max_x, start_x, start_y, "Instructions: \n \n ENTER to enter in your input \n BACKSPACE to clear input \n SHIFT + s to skip to next set of words \n shift + q to quit \n \n Press any key to start", 1, 1);
    getch();

    // create random seed
    srand(time(0));

    // find length of file
    int set_length = find_length("/usr/local/bin/bomb-partty-bin/set.txt");

    // declare set array using find_length
    string letter_set[set_length];

    // opens file
    file.open("/usr/local/bin/bomb-partty-bin/set.txt");

    // goes through file again and fills array using file
    for(int i = 0; getline(file, line); i++) {
        letter_set[i] = line;
    }

    file.close();

    // determines the random set of letters using rand() function
    string message = letter_set[rand() % set_length];

    // displays set of letters before first key press
    redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));
    mvprintw(1, 1, "points: %d", points);
    move(start_y + 1, start_x + 1);

    // main loop
    while(!quit) {
        c = getch();
        redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));

        // check specific input
        switch(c) {
            // SHIFT + q to quit
            case 81:
                quit = true;

                break;
            
            // BACKSPACE key to clear input
            case 127:
                input = "";
                redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));

                break;
            
            // ENTER key
            case 10:
                // checks if input contains specified set of letters
                if(input.find(message) != std::string::npos) {
                    check++;
                }
                else {
                    check = 0;
                    input = "";
                    redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));
                    
                    break;
                }

                // loops through dictionary to check if input is real word
                for(int i = 0; i < length; i++) {
                    if(dictionary[i] == input) {
                        check++;

                        break;
                    }
                }

                // increase points and make new set of letters
                if(check == 2) {
                    message = letter_set[rand() % set_length];
                    points++;
                }
                
                check = 0;
                input = "";
                redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));

                break;
            
            // SHIFT + s to skip
            case 83:
                message = letter_set[rand() % set_length];
                input = "";
                redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));

                break;
            
            default:
                input += c;

                break;
            }
        
        // failsafe to clear input and redraw screen if input is too large
        if(std::size(input) > term_max_x - 10) {
            input = "";
            redraw_screen(term_max_y, term_max_x, start_x, start_y, message, term_max_y / 2, term_max_x / 2 - (std::size(message) / 2));
        }

        // draws points
        mvprintw(1, 1, "points: %d", points);

        // writes all input on screen
        mvaddstr(start_y + 1, start_x + 1, input.c_str());

    }

    // end ncurses
    endwin();

    cout << "points: " << points << "\n";

    return 0;
}
