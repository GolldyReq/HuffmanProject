#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#include "decompress.h"


int main(int nbarg,char **argv)
{

    char file[456]="test.txt";
    compress_file(file);
    decompress_file("test.txt.hf");
    return 0;


}
