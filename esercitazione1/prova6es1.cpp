#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, const char *argv[]) {
    if (argc < 2)
    {
        cerr << "Non hai inserito il nome del file da leggere\n"; 
        return 1;
    }
    ifstream ifs(argv[1]);
    if ( ifs.is_open() ) {
        while( !ifs.eof() ) {
            string location;
            double temp1;
            double temp2;
            double temp3;
            double temp4;
            ifs>>location>>temp1>>temp2>>temp3>>temp4;
            double media;
            media=(temp1+temp2+temp3+temp4)/4;
            cout << "Average temperature at " << location << " is " << media << "\n";        
        }
    }
    else
    {
        cerr << "Il file inserito non si apre\n"; 
        return 1;
    }  
    return 0;
}