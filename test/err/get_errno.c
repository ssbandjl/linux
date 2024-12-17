#include <stdio.h>
#include <string.h>
#include <errno.h>

int main ()
{
   FILE *fp;

   fp = fopen("file.txt","r");
   if( fp == NULL ) 
   {
      printf("Error: %s\n", strerror(errno));  // -> glibc -> https://elixir.bootlin.com/glibc/latest/source/string/strerror.c, 
   }
   
  return(0);
}

