#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <map>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc > 2){
        setlocale(LC_CTYPE, "");
        int fdl = open("kanjis.txt",O_RDWR, S_IRWXU); //open the document to read all the characters
        int fdl2 = open(argv[1],O_RDWR, S_IRWXU); //open the document to read the text to be compressed
        int fdw = open(argv[2],O_RDWR|O_CREAT|O_TRUNC, S_IRWXU), ret,c, count=0;

        map<int,int> mapakanji;

        while ( (ret = read(fdl,&c,3))>0){ //we read 3 bytes (one kanji)
            mapakanji[c] = count; //for each kanji we store a number, indicating its position
            ret = read(fdl,&c,2); //we read the 2 bytes of the line break
            count++;
        }
        char c1,c2,c3;
        int prim=0, segon, aux;
        count = 0;
        bool b=false;
        while ( (ret = read(fdl2,&c,3))>0){ //we read 3 bytes (one kanji)
            auto itr = mapakanji.find(c); //we look for the kanji on the map
            if(itr != mapakanji.end()){ //every two kanji read (3 * 2 = 6 bytes), we write (3 bytes) encoding its position
                if (not b){
                    prim = itr->second;
                    aux = prim>>4;
                    c1 = aux;
                    ret = write(fdw,&c1,sizeof(c1));
                    b=true;
                }
                else{
                    segon = itr->second;
                    aux = ((prim & 0x00f)<<4) | (segon>>8);
                    c2 = aux;
                    ret = write(fdw,&c2,sizeof(c2));
                    aux = segon & 0xff;
                    c3 = aux;
                    ret = write(fdw,&c3,sizeof(c3));
                    b=false;
                }
            }
        }

        if (b){ //we write what is left of the first one to be written in case we have not entered the second one.
            aux = ((prim & 0x00f)<<4);
            c2 = aux;
            ret = write(fdw,&c2,sizeof(c2));
        }
    }
    else{
        cout<<"Usage: ./compressor <input_file> <compressed_file>"<<endl;
    }
    
    
    
}