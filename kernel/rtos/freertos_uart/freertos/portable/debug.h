#ifndef DEBUG_H
#define DEBUG_H

#define DBG(a) *(unsigned char*)0xffffff00 = a;

#define PRINTC(ch) {}

/*
#define PRINTC(ch)                      \
 { DBG(ch)                                \
   DBG(0)                                 \
 }
*/

#define PRINT(s)                         \
 { for(char* ptr = s; ptr && *ptr; ++ptr) DBG(*ptr)                           \
   DBG(0)                              \
 }

#define PRINTL(dw) {}
/*
#define PRINTL(dw)                         \
 { for(char i=0; i<8; i++)             \
    { char ch = (dw>>((7-i)*4))&0x0F;         \
      ch = ch > 9 ? ch-10+'A' : ch + '0';    \
      DBG(ch)                           \
    } DBG(0)                              \
 }
*/


#endif