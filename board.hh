#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>


using namespace std;

class piece
{
    public:
        piece(char nord, char ouest, char sud, char est, bool fixed);
        int nord;
        int ouest;
        int sud;
        int est;
        bool fixed;

        void rotate();
};

class board
{
    public:
        board(string input_file);
        ~board() = default;

        void printer();


        vector<vector<piece>> pieces;
        int size;
    private:

};