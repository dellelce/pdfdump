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
 return pdf_read(argv[1]);
}

// ** EOF **
