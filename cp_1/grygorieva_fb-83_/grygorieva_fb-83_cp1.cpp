#include <iostream>
#include <fstream>
#include <istream>
#include<cstdlib>

using namespace std;

class Letter
{
public:
    int ascii_code;
    float times_in_text;
    char symbol;
    float frequency_with_space;
    float frequency_without_space;
};

class Bigramm
{
public:
    float times_in_text;
    string symbols;
    float frequency_with_space;
    float frequency_without_space;
};

char* buffer;
int length;
Letter* frequency_for_each_letter;
Bigramm* frequency_for_each_bigramm;
void find_bigramms();
void entropy_for_letters_with_space();
void entropy_for_letters_without_space();

void show_frequency()
{
    cout << "----ASCII--------SYMBOL--------TIMES--------FREQUENCY_1--------FREQUENCY_2----" << endl;
    for (int i = 0; i < 33; i++)
    {
        cout << frequency_for_each_letter[i].ascii_code << "             " << frequency_for_each_letter[i].symbol <<"             "<< frequency_for_each_letter[i].times_in_text << "             " << frequency_for_each_letter[i].frequency_with_space << "              " << frequency_for_each_letter[i].frequency_without_space <<endl;
    }
}


int main()
{
    setlocale(LC_ALL, "");
   
    float** letters_array;

    letters_array = new float* [33];
    for (int i = 0; i < 33; i++) 
    {
        letters_array[i] = new float[2];
    }

    int n = -32;
    for (int i = 0; i < 33; i++)
    {
        letters_array[i][0] = n;
        letters_array[i][1] = 0;
        n++;
    }

    letters_array[32][0] = 32;

    std::ifstream file;
    file.open("C:\\crypto\\master-i-margarita.txt");
    float sum = 0;
    if (file)
    {
        file.seekg(0, file.end);

        length = file.tellg();
        file.seekg(0, file.beg);
        buffer = new char[length];

        cout << "LENGTH IS " << length << endl;
        file.read(buffer, length);

        int temp = 0;

        for (int i = 0; i < length; i++)
        {
            temp = (int)buffer[i];
            if (temp == 32) letters_array[32][1]++;

            for (int j = -32; j < 0; j++)
            {
                if (temp == j)
                {
                    letters_array[j + 32][1]++;
                }
            }
        }
        
        cout << endl;

        for (int i = 0; i < 33; i++) 
        {
            sum = sum + letters_array[i][1];
        }
    }

    else cout << "ERROR_1" << endl;
   
    cout << "SUM: " << (int)sum << endl;

    frequency_for_each_letter = new Letter[33];

    for (int i = 0; i < 33; i++)
    {
        frequency_for_each_letter[i].ascii_code = letters_array[i][0];
        frequency_for_each_letter[i].times_in_text = letters_array[i][1];
        frequency_for_each_letter[i].symbol = letters_array[i][0];
        frequency_for_each_letter[i].frequency_with_space = frequency_for_each_letter[i].times_in_text / sum;
        frequency_for_each_letter[i].frequency_without_space = frequency_for_each_letter[i].times_in_text / (sum - letters_array[32][1]);
    }

    /*
    float var = 0;
    for (int i = 0; i < 32; i++)
    {
        var = var + frequency_for_each_letter[i].frequency_without_space * 100;
    }
    cout << endl << var << endl;
    */

    show_frequency();
    
    entropy_for_letters_with_space();
    entropy_for_letters_without_space();

    frequency_for_each_bigramm = new Bigramm[1089];
    find_bigramms();

    file.close();
    for (int i = 0; i < 33; i++) 
    {
        delete[] letters_array[i];
    }
    delete[] letters_array;
    return 0;
}

void entropy_for_letters_with_space()
{
    float h1_with_space = 0;
    for (int i = 0; i < 33; i++)
    {
        h1_with_space = h1_with_space + frequency_for_each_letter[i].frequency_with_space * log2(frequency_for_each_letter[i].frequency_with_space);
    }
    h1_with_space = -h1_with_space;
    cout << "ENTROPY FOR LETTERS WITH SPACES H1 = " << h1_with_space << endl;
}

void entropy_for_letters_without_space()
{
    float h1_without_space = 0;
    for (int i = 0; i < 32; i++)
    {
        h1_without_space = h1_without_space + frequency_for_each_letter[i].frequency_without_space * log2(frequency_for_each_letter[i].frequency_without_space);
    }
    h1_without_space = -h1_without_space;
    cout << "ENTROPY FOR LETTERS WITHout SPACES H1 = " << h1_without_space << endl;
}

void find_bigramms()
{
    for (int i = 0; i < 1089; i++)
    {
        frequency_for_each_bigramm[i].symbols  = "";
        frequency_for_each_bigramm[i].times_in_text = 0;
    }

    string temp_str = "";
    int j = 0;
    for (int i = 0; i < length; i = i+2)
    {
        //cout << buffer[i] << buffer[i + 1] << endl;
        temp_str = buffer[i];
        temp_str = temp_str + buffer[i + 1];
        /*
            frequency_for_each_bigramm[j].symbols = temp_str;
            frequency_for_each_bigramm[j].times_in_text++;
            if (j<1089) j++;*/
    }
}