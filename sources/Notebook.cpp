#include <iostream>
#include <string>
#include <map>
#include "Direction.hpp"
#include "Notebook.hpp"

using namespace std;
using namespace ariel;
const int MAX_COL = 100;


void Notebook::write( int page, int row,  int column, Direction direction, string message) {

    // check exceptions
    int size = message.length();

    if ( page < 0 || row < 0 || column <  0 || column > MAX_COL){
        throw invalid_argument("Failed, parameters must be positive numbers ");
    }

    if (size < 0) {
        throw invalid_argument("Failed, you cannot write a negative message ");
    }
    
    if (column + size > MAX_COL && direction == Direction::Horizontal) {
        throw invalid_argument("Failed, the length of the message is out of range ");
    }
    
    // if the message is legal
    for( int i = 0; i < size; i++) {

        // Check if this is not an erase point
        if (message[(unsigned int)i] == '~') {
            throw invalid_argument("Error, you cannot write at this point");
        }

        // Check if this a printable character
        if(isprint(message[(unsigned int)i])==0){
            throw invalid_argument(" Error,this is an invalid character");
        }

    }

    // FIll the row by '_'
    string underscore = "____________________________________________________________________________________________________";

    // Write in horizontal direction
    if ( direction == Direction::Horizontal) {

        // Check if the row is empty or not
        if (myNotebook[page].count(row) == 0) {
            myNotebook[page][row] = underscore;
        }

        for( int i = 0; i < size; i++) {

            // Cannot write on a already written place
            if ( myNotebook[page][row][(unsigned int)(column+i)] != '_'){
                throw invalid_argument(" Error, you cannot write on a written place");
            }
            myNotebook[page][row][(unsigned int)(column+i)] = message[(unsigned int)(i)];
           
        }

    }
    // If the direction is vertical
    else {

        for( int i = 0; i < size; i++) {

            if ( myNotebook[page].count(row+i) == 0) {
                myNotebook[page][row+i] = underscore;
            }
        }

        for( int i = 0; i < size; i++) {

            //Cannot write on a already written place
            if ( myNotebook[page][row+i][(unsigned int)column] != '_'){
                throw invalid_argument(" Error, you cannot write on a written place");
            }
            // Pass over the message and fill the notebook
            myNotebook[page][row+i][(unsigned int)column] = message[(unsigned int)i];
        }
    } 
}



string Notebook::read(int page, int row,  int column, Direction direction, int length) {

    if (length < 0) {
        throw invalid_argument("Failed, you cannot write a negative message ");
    }

    if (column + length > MAX_COL && direction == Direction::Horizontal) {
        throw invalid_argument("Failed, the length of the message is out of range ");
    }

    if (column >= MAX_COL || column <0 || row<0 ||page<0) {
        throw invalid_argument("Failed, enter positive num ");
    }
    string word;
    word.append((unsigned int)length, '_');
    if (myNotebook.find(page) == myNotebook.end()) {
        return word;
    }
    if (direction == Direction::Horizontal) {

        if (myNotebook[page].find(row) == myNotebook[page].end()) {
            return word;
        }
        for (int i = 0; i < length; i++) {
               
                word[(unsigned int)i] = myNotebook[page][row][(unsigned int)(column + i)];
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (myNotebook[page].find(row+i) != myNotebook[page].end()) {
                word[(unsigned int)i] = myNotebook[page][row+i][(unsigned int)column];
            } 
            else {
                word[(unsigned int)i] = '_';
            }
        }
    }
    return word;

}

void Notebook::erase(int page, int row,  int column, Direction direction, int length) {

    if (length < 0) {
        throw invalid_argument("Failed, you cannot erase a negative message ");
    }

    if ( page < 0 || row < 0 || column <  0 || column >= MAX_COL){
        throw invalid_argument("Failed, parameters must be positive numbers ");
    }
    if (column + length > MAX_COL && direction == Direction::Horizontal) {
        throw invalid_argument("Failed, the length of the message is out of range ");
    }


    
    // Replace the message by '~' in the two directions
    for (size_t i = 0; i < length; i++) {

        if ( direction == Direction::Vertical ) {
            // page not exist
            if (myNotebook.find(page) == myNotebook.end()) {
                map<int,string> newPage;
                string newRow(MAX_COL,'_');
                newPage.insert({(size_t)row,newRow});
                myNotebook.insert({page, newPage});
            }
            // row not exist
            if(myNotebook.at(page).find((size_t)row+i) ==  myNotebook.at(page).end())
            {
                string newRow(MAX_COL,'_');
                myNotebook.at(page).insert({(size_t)row+i, newRow});
            }
            myNotebook.at(page).at((size_t)row + i).at((size_t)column) = '~';
        }
        else  {
            // page not exist
            if (myNotebook.find(page) == myNotebook.end()) {
                map<int,string> newPage;
                string newRow(MAX_COL,'_');
                newPage.insert({row,newRow});
                myNotebook.insert({page, newPage});
            }
            // row not exist
            if(myNotebook.at(page).find(row) ==  myNotebook.at(page).end())
            {
                string newRow(MAX_COL,'_');
                myNotebook.at(page).insert({row, newRow});
            }
            myNotebook.at(page).at(row).at((size_t)column + i) = '~';
        }
    }
    
}


void Notebook::show(int page){

    if (page < 0) {
        throw invalid_argument("Failed, you cannot write a negative page ");
    }

    int x = 3;
    x++;

    // while(true) {
    //     string message;
    //     if (myNotebook.count(row) != 0 && myNotebook[row].count(column) != 0) {
    //         message += myNotebook[page][row][(unsigned int)column];
    //         cout << row << ':' << message << endl;
    //         message = "";
    //     } 
    //     else {
    //         cout << "_" << endl;
    //         break;
    //     }
    //
    // }

}
