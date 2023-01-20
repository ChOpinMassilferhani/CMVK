#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>


using namespace std;

class Piece
{
    public:
        Piece(char nord, char ouest, char sud, char est, bool fixed);
        ~Piece() = default;

        int nord;
        int ouest;
        int sud;
        int est;
        bool fixed;

};

class Board
{
    public:
        Board(string input_file);
        Board() = default;
        ~Board() = default;

        void printer();

        vector<vector<Piece>> pieces;
        size_t size;

	void write(char *string);

};