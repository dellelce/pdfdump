/**
 
  @file    pdf.h
  @author  Antonio Dell'elce
  @created 100215
  @brief   
 
*/

#ifndef __PDF_H
/** @cond NoDoc */
#define __PDF_H 1
/** @endcond */

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
#define TOKEN_BUFFER  1024
#endif // TOKEN_BUFFER

//
// Types: pstate_t
//  processing state, use a standar 2D state machine?

typedef struct __process_state
{
 unsigned short ps_state;
 unsigned short ps_substate;
 unsigned long  ps_depth;
} pstate_t;

// states

#define STATE_MAIN    1
#define STATE_COMMENT 2

/*
   pdf_token
*/

typedef struct __pdf_token
{
 unsigned char  ps_token_buffer[TOKEN_BUFFER];
 unsigned short ps_token_used; // actual used part of buffer
 // token type missing
} pdf_token_t;

/*
   pdf_context_t

*/

typedef struct
{
 // count binary zeros: just one will not print anything, more will print a blank
 // int   zerocnt = 0;
 FILE            *fh;        // pdf file handle
 int              ch;
 int              cnt;       // number of characters we printed (when dumping to screen)
 pstate_t         state;
 unsigned long    gcnt;     // global counter - count all chars read
 // version block
 unsigned char    ver[10];
 unsigned char    verclose;
 unsigned short   verread;  // version is NOT read = 0 - read = 1
} pdf_context_t;

// States

#define STATE_READING_NULL         0
#define STATE_READING_VERSION      1
#define STATE_NEW_LINE             2 // we are at the beginning of a line


// Substates


/*
   Prototypes
*/

int pdf_read(char *pdfName);


#endif /* __PDF_H */

/* EOF */
