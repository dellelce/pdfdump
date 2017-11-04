/* 
   File:    pdfdump.c
   Created: 120814

   pdf dumper
*/

// includes

#include <stdio.h>

#include "pdf.h"

//
// main
//

int
main (int argc, char **argv)
{
 pdf_context_t ctx = { 0 };

 return pdf_read(&ctx, argv[1]);
}

// ** EOF **
