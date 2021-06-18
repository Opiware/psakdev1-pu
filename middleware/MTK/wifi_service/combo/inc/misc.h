/* Copyright Statement:
 *
 */

#ifndef __MISC_H__
#define __MISC_H__


/* Sanity check the configuration. */
#define ALIGN_4BYTE(size)       (((size+3)/4) * 4)

#ifndef IS_ALIGN_4
#define IS_ALIGN_4(_value)          (((_value) & 0x3) ? FALSE : TRUE)
#define IS_NOT_ALIGN_4(_value)          (((_value) & 0x3) ? TRUE : FALSE)
#endif /* IS_ALIGN_4 */

#ifndef IS_NOT_ALIGN_4
#define IS_NOT_ALIGN_4(_value)          (((_value) & 0x3) ? TRUE : FALSE)
#endif /* IS_NOT_ALIGN_4 */

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   BitArray
    @abstract   Macros for working with bit arrays.
    @discussion

    This treats bit numbers starting from the left so bit 0 is 0x80 in byte 0, bit 1 is 0x40 in bit 0,
    bit 8 is 0x80 in byte 1, etc. For example, the following ASCII art shows how the bits are arranged:

                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2
    Bit      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |    x          |x              |  x           x| = 0x20 0x80 0x41 (bits 2, 8, 17, and 23).
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Byte    0               1               2
*/
#define BIT_ARRAY_MIN_BYTES( ARRAY, N_BYTES )         os_memrlen( (ARRAY), (N_BYTES) )
#define BIT_ARRAY_MAX_BYTES( BITS )                   ( ( (BITS) + 7 ) / 8 )
#define BIT_ARRAY_MAX_BITS( ARRAY_BYTES )             ( (ARRAY_BYTES) * 8 )
#define BIT_ARRAY_CLEAR( ARRAY_PTR, ARRAY_BYTES )    os_memset( (ARRAY_PTR), 0, (ARRAY_BYTES) );
#define BIT_ARRAY_GET_BIT( PTR, LEN, BIT ) \
    ( ( (BIT) < BIT_ARRAY_MAX_BITS( (LEN) ) ) && ( (PTR)[ (BIT) / 8 ] & ( 1 << ( 7 - ( (BIT) & 7 ) ) ) ) )
#define BIT_ARRAY_SET_BIT( ARRAY, BIT )               ( (ARRAY)[ (BIT) / 8 ] |=  ( 1 << ( 7 - ( (BIT) & 7 ) ) ) )
#define BIT_ARRAY_CLEAR_BIT( ARRAY, BIT )             ( (ARRAY)[ (BIT) / 8 ] &= ~( 1 << ( 7 - ( (BIT) & 7 ) ) ) )



extern char *rstrtok(char *s, const char *ct);
extern void convert_string_to_hex_array(char *string, unsigned char *hex);
extern void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen);
extern void hex_dump_limit_len(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen, unsigned int limit_len);
extern char *uint64ToDecStr(uint64_t value);
extern void ignore_spaces_dash(char *pin_src, char *pin_dst);
uint8_t BtoH(char ch);
void AtoH(char *src, char *dest, int destlen);

#endif

