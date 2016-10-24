/* 
   File:    pdf.c
   Created: 241016

   pdf dumper
*/

// includes

#include <stdio.h>

#include "pdf.h"

//
// pdf
//

int
pdf (char *pdfName)
{
 pdf_context_t pdf;

// Initialize stuff

 pdf.ver[0] = 0;
 pdf.gcnt   = 0;
 pdf.cnt    = 0;
 
 pdf.fh = fopen(pdfName, "rb");

 if (pdf.fh == NULL)
 {
   return 1;
 }

 while (!feof(pdf.fh))
 {
  pdf.ch = fgetc(pdf.fh);

  // read PDF version
  if (pdf.gcnt < (sizeof(pdf.ver)-1)) // slightly buggy condition as it is 
  {
    if (pdf.verread == 0)
    {
      if (pdf.ch == 0xa || pdf.ch == 0xd)
      {
        pdf.verread  = 1;
        pdf.verclose = pdf.ch;
        printf ("Version: %s\nVersion closing char: %02x\n", &pdf.ver[0], pdf.ch);
      }
      else
      {
        pdf.ver[pdf.gcnt]   = pdf.ch;
        pdf.ver[pdf.gcnt+1] = 0;
      }
    }
  }
  
  pdf.gcnt = pdf.gcnt + 1;

  if (pdf.cnt >= LINESIZE)
  {
   pdf.cnt = 0;
   printf("\n");
  }

/*
  if (ch == 0) { zerocnt += 1; continue; }

  // we have a non-0 character: print a blank if we had previously more than 1 zero bytes

  if (zerocnt > 0)
  {
   if (zerocnt > 1) { printf(BLANK); cnt += 1; } 
   zerocnt = 0;
  }
*/

  if (pdf.ch < 32)
  {
/*
   if (ch == '\n')
   {
    if (cnt != 0) { cnt = 0; printf("\n"); }; continue;
   }
*/
   if (pdf.ch == 8)
   {
    pdf.cnt += 4; printf("    "); continue;
   }

   // CR
   if (pdf.ch == pdf.verclose)
   {
    pdf.cnt = 0;
    printf(" <EOL>\n");
    continue;
   }

   //printf(DOT);
   printf("<%02x>", pdf.ch);
   pdf.cnt += 4;
   continue;
  }

  // Unprintable characters go hex
  if (pdf.ch > 126)
  {
   printf("<%02x>", pdf.ch);
   pdf.cnt += 4;
   continue;
  }

  printf("%c", pdf.ch); 
  pdf.cnt += 1;
 } // while

 if (pdf.cnt > 0) { printf("\n"); }  

 return 0;
}

// ** EOF **
