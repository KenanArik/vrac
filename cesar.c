#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
//https://stackoverflow.com/questions/31322109/write-a-file-and-make-it-read-only

/*
Congratulations, you succeeded in decrypting this message                                                                                                                                                                            
The real subject is to write a program to encrypt a file or                                                                                                                                                                                     
string and write the result in a file named ’crypt’.                                                                                                                                                                                            
To encrypt a file we will use the ’-f’ parameter, for a string we will use ’-s’.                                                                                                                                                                
Since it is a crypted file, nobody should be able to modify its contents,                                                                                                                                                                       
that’s why your program should set the read-only rights to the ’crypt’ file.                                                                                                                                                                    
Usage: ./cesar -f filename key OR ./cesar -s "string" key    
*/
void caesarEnc(const char * message, short key, char * ciphertext);
void caesarDec(const char * ciphertext, short key, char * plaintext);

void caesarEnc(const char * message, short key, char * ciphertext){
    unsigned int i = 0;
    short rang;
    while( message[i] != '\0'){
        if( ( message[i] >= 'a') && (message[i] <= 'z') ){
            rang = (message[i] - 'a' + key) % 26;
            if( rang < 0) rang += 26;
            ciphertext[i] = 'a' + rang;
        }
        else if(( message[i] >= 'A') && (message[i] <= 'Z')){
            rang = (message[i] - 'A' + key) % 26;
            if( rang < 0) rang += 26;
            ciphertext[i] = 'A' + rang;
        }
        else {
            ciphertext[i] = message[i];
        }
        i++;
    }
    ciphertext[i] = '\0';
}

void caesarDec(const char * ciphertext, short key, char * plaintext){
    caesarEnc(ciphertext, -key, plaintext);
    printf("decode[%d]=%s\n",key,plaintext);
}

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}
int checker(int ac,char **av){
    if(ac !=4){
        return 84;
    }
    printf("av[1]=%s,av[2]=%s,av[3]=%s\n",av[1],av[2],av[3]);
    if (strcmp(av[1],"-s") != 0 && strcmp(av[1],"-f") != 0){
        return 84;
    }
    char* p = av[3];
    while (*p != '\0')
    {
        if (*p<'0' || *p>'9')
        {
            //printf("%s is not a number", av[3]);
            return 84;
        }
        p++;
    }
    return 0;
    
}

int get_data(int* key,char **content,char **av){
    *key = atoi(av[3]);
    printf("key=%d,%s is a number", *key,av[3]);
    if (strcmp(av[1],"-s")==0){
        *content = av[2];
        printf("content=%s\n",*content);
    }
    else{
        //from the file
        //printf("read file\n");
        *content = ReadFile(av[2]);
        if(*content==NULL){
            return 84;
        }
    }
    return 0;
}

int create_crypt_file(const char *path,char *content_crypted ){
    FILE *fptr;
    fptr = fopen(path,"w");
    if(fptr == NULL)
    {
      //printf("Error!");   
      return 84;             
    }
    
    fprintf(fptr,"%s",content_crypted);
    fclose(fptr);
    chmod(path, S_IRUSR|S_IRGRP|S_IROTH);
    return 0;
   
}

int main(int ac,char **av){
    
    char *content;
    const char *path = "crypt";
    int key;
    
    if(checker(ac,av)!=0){
        return 84;
    }
        
    
    if(get_data(&key,&content,av)!=0){
        return 84;
    }
    printf("\nkey=%d,av[2]=%s,content=%s\n", key,av[2],content);
    
    
    
    
    char *content_crypted = malloc(sizeof(char)*strlen(content));
    caesarEnc(content,key,content_crypted);
    printf("content_crypted=%s\n",content_crypted); 
    
    if(create_crypt_file(path,content_crypted ) !=0){
        return 84;
    }
    
    printf("content_crypted=%s\n",content_crypted);
    free(content_crypted);

	//caesarDec(ddt,10,ppt);
	

    return 0;
    
}
