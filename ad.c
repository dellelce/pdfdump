/* 
   File:    bindump.c
   Created: 1449 120814

   mini binary dumper
*/

// includes

#include <stdio.h>

#ifndef LINESIZE
#define LINESIZE 120
#endif // LINESIZE

#ifndef BLANK
#define BLANK " "
#endif // BLANK

// main

int
main (int argc, char **argv)
{
 FILE *fh;
 int   ch;
 int   cnt = 0;     // number of characters we printed
 int   zerocnt = 0; // count binary zeros: just one will not print anything, more will print a blank

 fh = fopen(argv[1], "rb");

 if (fh == NULL)
 {
   return 1;
 }

 while (!feof(fh))
 {
  ch = fgetc(fh);

  if (cnt >= LINESIZE) { cnt = 0; printf("\n"); }
  if (ch == 0) { zerocnt += 1; continue; }

  // we have a non-0 character: print a blank if we had previously more than 1 zero bytes

  if (zerocnt > 0)
  {
   if (zerocnt > 1) { printf(BLANK); cnt += 1; } 
   zerocnt = 0;
  }

  if (ch < 32)
  {
   if (ch == '\n')
   {
    if (cnt != 0) { cnt = 0; printf("\n"); }; continue;
   }
   if (ch == 8)
   {
    cnt += 4; printf("    "); continue;
   }

   printf(BLANK);
   cnt += 1;
   continue;
  }

  if (ch > 126) { printf(BLANK); cnt += 1; continue; }

  printf("%c", ch); 
  cnt += 1;
 } // while

 if (cnt > 0) { printf("\n"); }  

 return 0;
}

// ** EOF **
