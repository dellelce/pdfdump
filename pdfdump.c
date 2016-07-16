/* 
   File:    pdfdump.c
   Created: 120814

   pdf dumper
*/

// includes

#include <stdio.h>

#include "pdf.h"

// Types: pstate / processing state, use a standar 2D state machine?

typedef struct __process_state
{
// input state
  unsigned short ps_state;
  unsigned short ps_substate;
  unsigned long  ps_depth;
// pdf state / output state(? - TBD)
// ..
// token

  unsigned char  ps_token_buffer[TOKEN_BUFFER];
} pstate_t;

typedef struct 
{
 // count binary zeros: just one will not print anything, more will print a blank
 // int   zerocnt = 0;
 FILE            *fh;           // pdf file handle
 int              ch;
 int              cnt = 0;      // number of characters we printed
 pstate_t         state;
 unsigned char    ver[10];
 unsigned char    verclose = 0;
 unsigned long    gcnt = 0;     // global counter - count all chars read
 unsigned short   verread = 0;  // version is NOT read = 0 - read = 1
} pdf_context_t;

//
// main
//

int
main (int argc, char **argv)
{
 pdf_context_t pdf;

// Initialize stuff

 pdf.ver[0] = 0;
 
 pdf.fh = fopen(argv[1], "rb");

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
        pdf.verclose = ch;
        printf ("Version: %s\nVersion closing char: %02x\n", &pdf.ver[0], pdf.ch);
      }
      else
      {
        pdf.ver[gcnt]   = pdf.ch;
        pdf.ver[gcnt+1] = 0;
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
   cnt += 4;
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
