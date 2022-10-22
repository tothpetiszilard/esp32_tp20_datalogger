#include "file_operations.h"
#include "oled.h"

FILE * setup_fs(){
 return NULL;
};

int f_puts(const char* strToWrite, FILE* filePtr)
{
    Oled_Print((char *) strToWrite);
    printf(strToWrite);
    return(sizeof(strToWrite));
}; //When the string was written successfuly, it returns number of character encoding units written to the file. When the function failed due to disk full or any error, an EOF (-1) will be returned.
