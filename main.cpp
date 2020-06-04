//TO COMPILE: g++ -Wall -Werror -std=c++14 -O -o main Game.cpp Player.cpp Wall.cpp FloorLine.cpp PatternLines.cpp CentreFactory.cpp Factory.cpp BoxLid.cpp TileBag.cpp Tile.cpp main.cpp
#include "Game.h"

int getInput();
void printMain();
void printCredits();
bool doesFileExist (string filename);

int main (void) {
    cout << "Welcome to Azul!" << endl;
    cout << "---------------- \n" << endl;
   
    int choice;
    do{
        printMain();

        choice = getInput();

        if(choice == 1){
            Game* aGame = new Game();

            aGame->newGame();
            aGame->~Game();
        } else if(choice == 2){
             //loadGame();
            Game* aGame = new Game();
            cout << "Enter the filename from which to load a game" << endl;
            cout << "> ";
            string filename ="";
            cin >> filename;
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            while(!doesFileExist(filename)){
                cout << "Invalid filename, try again: ";
                cin >> filename;
                cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            }
            aGame -> loadGame(filename);
            aGame->~Game();
        } else if(choice == 3){
            printCredits();
        } else if(choice == 4){
            cout << "Goodbye!" << endl;
            exit(1);
        }
    } while(choice != 4);
    cin >> choice;
   
    return EXIT_SUCCESS;
}

int getInput()
{    
    int choice;
    
    cout << endl << "> ";
    while(!(cin >> choice))
    {
        cout << endl <<"Error: enter a valid number" << endl << endl;

        printMain();

        cout << endl << "> ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cout << endl;

    return choice;
}

void printMain() {
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;
}

void printCredits() {
    cout << "------------------------------------" << endl;
    cout << "Name: Sovatharo Huy" << endl;
    cout << "Student ID: s3783867" << endl;
    cout << "Email: s3783867@student.rmit.edu.au" << endl << endl;

    cout << "Name: Maria Dalvik" << endl;
    cout << "Student ID: s3829197" << endl;
    cout << "Email: s3829197@student.rmit.edu.au" << endl << endl;

    cout << "Name: Matthies Abera" << endl;
    cout << "Student ID: s3779748" << endl;
    cout << "Email: s3779748@student.rmit.edu.au" << endl;
    cout << "------------------------------------" << endl << endl;
}

bool doesFileExist (string filename) {
    bool returnValue = false;
    if (FILE *file = fopen(filename.c_str(), "r")) {
        fclose(file);
        returnValue = true;
    }
    return returnValue;
}