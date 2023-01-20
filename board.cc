#include "board.hh"

#include <vector>


Board::Board(string input_file)
{
    int pos = 0;
    while(input_file[pos] != 's')
        pos++;
    char s = input_file[pos + 1];
    this->size = stoi(string(1, s));



    string line;

    ifstream myfile (input_file);
    //Check if file exists

    if (!myfile.is_open()) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    this->pieces = vector<vector<Piece>>();
    for (size_t i = 0; i < size; i++)
    {
        vector<Piece> linep;

        for (size_t j = 0; j < size; j++)
        {
            getline(myfile,line);
            int k = 0;
            while (k < line.size() && line[k] != '@')
                k++;
            Piece p(line[0], line[1], line[2], line[3], k < line.size());
            linep.push_back(p);
        }
        this->pieces.push_back(linep);
        
        
    }

    myfile.close();
}


void Board::printer()
{
    string sol("+-----");
    for (size_t i = 0; i < this->size; i++)
    {
        for (size_t j = 0; j < this->size; j++)
            cout << sol;
        cout << "+" << endl;

        for (size_t j = 0; j < this->size; j++)
            cout << "|  " << this->pieces[i][j].nord << "  ";
        cout << "|" << endl;

        for (size_t j = 0; j < this->size; j++)
        {
            cout << "| " << this->pieces[i][j].ouest;
            if (this->pieces[i][j].fixed)
                cout << "@";
            else
                cout << " ";
            cout << this->pieces[i][j].est << " ";
        }
        cout << "|" << endl;

        for (size_t j = 0; j < this->size; j++)
            cout << "|  " << this->pieces[i][j].sud << "  ";
        cout << "|" << endl;
        
    }
    for (size_t j = 0; j < this->size; j++)
        cout << sol;
    cout << "+" << endl;
    
}

void Board::write(char *string) {
	ofstream myfile;
	myfile.open(string);
	for (size_t i = 0; i < this->size; i++)
	{
		for (size_t j = 0; j < this->size; j++)
		{
			myfile << this->pieces[i][j].nord << this->pieces[i][j].ouest << this->pieces[i][j].est << this->pieces[i][j].sud;
			myfile << endl;
		}
	}
	myfile.close();
}

int ctoi(char c)
{
    return c - '0';
}

Piece::Piece(char nord, char ouest, char est, char sud, bool fixed)
{
    this->nord = ctoi(nord);
    this->ouest = ctoi(ouest);
    this->sud = ctoi(sud);
    this->est = ctoi(est);
    this->fixed = fixed;
}