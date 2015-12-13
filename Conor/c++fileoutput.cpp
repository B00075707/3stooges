/* Lab_7.cpp */
/*-------------------------------------------------------------------------
Programmer: Conor O'Mathuna
ID: B00075707
Date: 18 March 2015
Purpose: Reads in a name of a file, and then adds the contents of that file
to 'output.txt'. It will prompt the user to continue adding files until they
are finished, and will also notify the user when a file couldn't be opened.
-------------------------------------------------------------------------*/
#include <std_lib_facilities.h>

using namespace std;

void file_copy_line(const string &, ofstream &);
void file_copy_buff(const string &, ofstream &);//Alternative function to perform
                                                //the same operation a different way.

class bad_file{};

int main()
{
    string filename;
    ofstream out("output.txt");

    cout << "Please enter name of file to add: \n";
	while(cin >> filename && filename != "end")
    {
        try
        {
            file_copy_line(filename, out);
            //file_copy_buff(filename, out); Alternative function call
        }
        catch(bad_file)
        {
            cerr << "ERROR: That file couldn't be opened.\n\n\n";
        }

        cout << "Enter another file to add (enter 'end' to save and exit)\n";
    }

    out.close();

    return 0;
}

/*-------------------------------------------------------------------------
Name:   file_copy_line
Arg1:   Reference to name of input file to open.
Arg2:   Reference to already opened output stream.
Reads in a line from the input file into 'in_buff', and then prints that string
to the output file. Continues until it reaches end of file. Throws 'bad_file'
exception if the input file couldn't be opened.
-------------------------------------------------------------------------*/
void file_copy_line(const string &name, ofstream &output)
{
    string in_buff;
    ifstream input(name.c_str());

    if(input.is_open())
    {
        while(getline(input, in_buff))
        {
            output << in_buff << endl;
        }

        input.close();
        cout << name << " added to output successfully.\n\n\n";
    }
    else
    {
        throw bad_file();
    }
}

/*-------------------------------------------------------------------------
Name:   file_copy_buff
Arg1:   Reference to name of input file to open.
Arg2:   Reference to already opened output stream.
Uses rdbuf(), which returns a pointer to input's stream buffer, and prints
out the contents of the input file to the output file. This method does not
need any temporary strings or chars to hold the contents before printing to
the output file.
-------------------------------------------------------------------------*/
void file_copy_buff(const string &name, ofstream &output)
{
    ifstream input(name.c_str());

    if(input.is_open())
    {
        output << input.rdbuf();
        input.close();
        cout << name << " added to output successfully.\n\n\n";
    }
    else
    {
        throw bad_file();
    }
}
