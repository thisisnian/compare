// Florian Killius
// License: Do whatever you want with this code.

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    //check if there are two files for reading given from the user
    if(argc != 3)
    {
        //if not, exit
        cout << "Wrong syntax: compare [file1] [file2] " << endl;
        return -2;
    }
    
    //two streams for the two files
    ifstream file1;
    ifstream file2;
    
    char *filename1 = argv[1];
    char *filename2 = argv[2];
    
    //open files binary for reading
    file1.open(filename1, ios::binary | ios::in);
    file2.open(filename2, ios::binary | ios::in);
    
    //if we couldnt open one of the two files
    //tell the user and exit
    if(!file1.is_open())
    {
        cout << filename1 << " could not be opened!" << endl;
        if(file2.is_open())
        {
            file2.close();
        }
        return -1;
    }
    if(!file2.is_open())
    {
        cout << filename2 << " could not be opened!" << endl;
        file1.close();
        return -1;
    }
    
    
    //find out the size of the two files
    streampos sizefile1 = file1.tellg();
    file1.seekg(0, ios::end);
    sizefile1 = file1.tellg() - sizefile1;
    
    streampos sizefile2 = file2.tellg();
    file2.seekg(0, ios::end);
    sizefile2 = file2.tellg() - sizefile2;    
    
    //if they have different size, they cant be equal
    if(sizefile1 != sizefile2)
    {
        cout << filename1  << " AND " << filename2  << " are not same" << endl;
        file1.close();
        file2.close();
        return 0;
    }
    
    //if they have the same size lets compare them byte per byte
    //jump to the beginning
    file1.seekg(0, ios::beg);
    file2.seekg(0, ios::beg);
    
    char buf1, buf2;
    
    //check each byte
    for(int a=0; a < sizefile1; a++)
    {
        //read from the files
        file1.get(buf1);
        file2.get(buf2);
        
        //and compare
        if(buf1 != buf2)
        {
            //iof they are not equal
            //tell the user und exit
            cout << filename1  << " AND " << filename2  << " are not same" << endl;
            file1.close();
            file2.close();
            return 0;
        }
    }
    
    cout << filename1 << " AND " << filename2 << " are the same" << endl;
    file1.close();
    file2.close();
    return 1;
}