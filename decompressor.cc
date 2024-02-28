#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include<stdlib.h>
#include<vector>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc > 2){
        setlocale(LC_CTYPE, "");
        char car;
        int fdl = open("kanjis.txt",O_RDWR, S_IRWXU); //open the document to read all the characters
        int fdl2 = open(argv[1],O_RDWR, S_IRWXU), ret, c;
        int fdw = open(argv[2],O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);

        vector<int> vectorkanji;

        while ( (ret = read(fdl,&c,3))>0){ //we read 3 bytes (one kanji)
            vectorkanji.push_back(c);
            ret = read(fdl,&c,2); //we read the 2 bytes of the line break
        }

        int count =0, c1=0, c2=0, c3=0, aux;
        while ( (ret = read(fdl2,&car,1))>0){
            c = car;
            if (c<0) c = 256+c; //Not to drag 1s when moving with << or >>.
            count++;
            if (count ==1) c1 = c;
            else if (count == 2) c2 = c;
            else{
                c3 = c;
                aux = (c1<<4) | (c2>>4);
                aux = vectorkanji[aux];
                ret = write(fdw,&aux,3);

                aux = ((c2 & 0xf)<<8) | (c3);
                aux = vectorkanji[aux];
                ret = write(fdw,&aux,3);
                count = 0;
            }
        }
    }
    else{
        cout<<"Usage: ./decompressor <compressed_file> <decompressed_file>"<<endl;
    }
}