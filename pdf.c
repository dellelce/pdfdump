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
pdf_read (char *pdfName)
{
 pdf_context_t pdf = { 0 };

/* 
  unsigned char  ps_token_buffer[TOKEN_BUFFER];
  unsigned short ps_token_used; // actual used part of buffer
*/

 pdf.state.ps_state = STATE_MAIN;

 // Open pdf file
 pdf.fh = fopen(pdfName, "rb");

 if (pdf.fh == NULL)
 {
   return 1;
 }

 while (!feof(pdf.fh))
 {
  pdf.ch = fgetc(pdf.fh);
  pdf.gcnt = pdf.gcnt + 1; // increase total number of chars read

  if (pdf.cnt >= LINESIZE)
  {
   pdf.cnt = 0;
   printf("\n");
  }

  // non printable characters plus some whitespaces
  if (pdf.ch < 32)
  {
   // EOL
   if (pdf.ch == 0x0d)
   {
    pdf.cnt = 0;
    printf("\n");
    continue;
   }

   // EOL: 0x0a after 0x0d
   if (pdf.ch == 0x0a && pdf.cnt == 0)
   {
    continue;
   }

   // After EOL: all other white spaces conditions

   if (pdf.ch == 0x09 || pdf.ch == 0x0A || pdf.ch == 0x0C || pdf.ch == 0x20)
   {
    printf(" ");
    pdf.cnt += 1;
    continue;
   }

   printf(DOT);
   pdf.cnt += 1;
   continue;
  }

  // Unprintable characters go hex or DOT (tbd)
  if (pdf.ch > 126)
  {
   //printf("<%02x>", pdf.ch);
   printf(DOT);
   pdf.cnt += 4;
   continue;
  }

  printf("%c", pdf.ch); 
  pdf.cnt += 1;
 } // while feof

 if (pdf.cnt > 0) { printf("\n"); }  

 return 0;
}

// ** EOF **
