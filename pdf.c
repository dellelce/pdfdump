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
pdf_read (pdf_context_t *pdf, char *pdfName)
{
 int ch;

 pdf->state.ps_state = STATE_MAIN;

 // Open pdf file
 pdf->fh = fopen(pdfName, "rb");
 if (pdf->fh == NULL) return 1;

 while (!feof(pdf->fh))
 {
  ch = fgetc(pdf->fh);
  pdf->gcnt = pdf->gcnt + 1; // increase total number of chars read

  if (pdf->cnt >= LINESIZE)
  {
   pdf->cnt = 0;
   printf(NL);
  }

  // non printable characters plus some whitespaces
  if (ch < 32)
  {
   // EOL
   if (ch == 0x0d)
   {
    pdf->cnt = 0;
    printf(NL);
    continue;
   }

   // EOL: 0x0a after 0x0d
   if (ch == 0x0a && pdf->cnt == 0) continue;

   // After EOL: all other white spaces conditions

   if (ch == 0x09 || ch == 0x0A || ch == 0x0C || ch == 0x20)
   {
    printf(" ");
    pdf->cnt += 1;
    continue;
   }

   printf(DOT);
   pdf->cnt += 1;
   continue;
  }

  // Unprintable characters go hex or DOT (tbd)
  if (ch > 126)
  {
   //printf("<%02x>", pdf.ch);
   printf(DOT);
   pdf->cnt += 4;
   continue;
  }

  printf("%c", ch);
  pdf->cnt += 1;
 } // while feof

 if (pdf->cnt > 0) { printf(NL); }

 return 0;
}

// ** EOF **
