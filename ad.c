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

#ifndef DOT
#define DOT "."
#endif // BLANK

#ifndef TOKEN_BUFFER
#define TOKEN_BUFFER  256
#endif // TOKEN_BUFFER


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


// functions

unsigned int
pushchar(pstate_t *s, unsigned char ch)
{
  // work in progress

  return 0;
}

// main

int
main (int argc, char **argv)
{
 FILE    *fh;
 int      ch;
 int      cnt = 0;     // number of characters we printed
// int   zerocnt = 0; // count binary zeros: just one will not print anything, more will print a blank
 pstate_t       s;
 unsigned char  ver[10];
 unsigned char  verclose = 0;
 unsigned long  gcnt = 0;    // global counter - count all chars read
 unsigned short verread = 0; // version is NOT read = 0 - read = 1

// Initialize stuff

 ver[0] = 0;
 
 fh = fopen(argv[1], "rb");

 if (fh == NULL)
 {
   return 1;
 }

 while (!feof(fh))
 {
  ch = fgetc(fh);

  // read PDF version
  if (gcnt < (sizeof(ver)-1)) // slightly buggy condition as it is 
  {
    if (verread == 0)
    {
      if (ch == 0xa || ch == 0xd)
      {
        verread = 1;
        verclose = ch;
        printf ("Version: %s\n", &ver[0]);
        printf ("Version closing char: %02x\n", ch);
      }
      else
      {
        ver[gcnt] = ch;
        ver[gcnt+1] = 0;
      }
    }
  }
  
  gcnt = gcnt + 1;

  if (cnt >= LINESIZE)
  {
   cnt = 0; printf("\n");
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

  if (ch < 32)
  {
/*
   if (ch == '\n')
   {
    if (cnt != 0) { cnt = 0; printf("\n"); }; continue;
   }
*/
   if (ch == 8)
   {
    cnt += 4; printf("    "); continue;
   }

   // CR

   if (ch == verclose)
   {
    cnt = 0;
    printf(" <EOL>\n");
    continue;
   }

   //printf(DOT);
   printf("<%02x>", ch);
   cnt += 4;
   continue;
  }

  if (ch > 126)
  {
   printf("<%02x>", ch);
   cnt += 4;
   continue;
  }

  printf("%c", ch); 
  cnt += 1;
 } // while

 if (cnt > 0) { printf("\n"); }  

 return 0;
}

// ** EOF **
