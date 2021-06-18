/* Copyright Statement:
 *
 */

/*****************************************************
  Usage:
   1. function: (a or b)
      a. ATTR_TEXT_IN_TCM int func(int par);
      b. ATTR_TEXT_IN_TCM int func(int par)
        {
        }
   2. RO data:
      a. ATTR_RODATA_IN_TCM const int b = 8;
   3. RW data:
      a. ATTR_RWDATA_IN_TCM int b = 8;
   4. ZI data:
      a. ATTR_ZIDATA_IN_TCM int b;
      
  Note: must put these attributes at HEAD of declaration.
*****************************************************/

#ifndef MEMORY_ATTRIBUTE_H_
#define MEMORY_ATTRIBUTE_H_

#if defined(__GNUC__)  /*GCC VERSION*/
#if (PRODUCT_VERSION == 7686)
#define ATTR_TEXT_IN_TCM              __attribute__ ((__section__(".tcm_code")))
#define ATTR_RODATA_IN_TCM            __attribute__ ((__section__(".tcm_rodata")))
#define ATTR_RWDATA_IN_TCM            __attribute__ ((__section__(".tcm_rwdata")))
#define ATTR_ZIDATA_IN_TCM            __attribute__ ((__section__(".tcm_zidata")))


#define ATTR_TEXT_IN_RAM              __attribute__ ((__section__(".ram_code")))
#define ATTR_RODATA_IN_RAM            __attribute__ ((__section__(".ram_rodata")))
#define ATTR_RWDATA_IN_NONCACHED_RAM  __attribute__ ((__section__(".noncached_ram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_RAM  __attribute__ ((__section__(".noncached_ram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_ram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_ram_zidata"),__aligned__(4)))

#define ATTR_TEXT_IN_SYSRAM              __attribute__ ((__section__(".sysram_code")))
#define ATTR_RODATA_IN_SYSRAM            __attribute__ ((__section__(".sysram_rodata")))

#define ATTR_RWDATA_IN_CACHED_SYSRAM     __attribute__ ((__section__(".cached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_CACHED_SYSRAM     __attribute__ ((__section__(".cached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__(".noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__(".noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_zidata"),__aligned__(4)))

#else

#define ATTR_TEXT_IN_TCM              __attribute__ ((__section__(".tcm_code")))
#define ATTR_RODATA_IN_TCM            __attribute__ ((__section__(".tcm_rodata")))
#define ATTR_RWDATA_IN_TCM            __attribute__ ((__section__(".tcm_rwdata")))
#define ATTR_ZIDATA_IN_TCM            __attribute__ ((__section__(".tcm_zidata")))


#define ATTR_TEXT_IN_RAM              __attribute__ ((__section__(".sysram_code")))
#define ATTR_RODATA_IN_RAM            __attribute__ ((__section__(".sysram_rodata")))
#define ATTR_RWDATA_IN_NONCACHED_RAM  __attribute__ ((__section__(".noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_RAM  __attribute__ ((__section__(".noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_zidata"),__aligned__(4)))

#define ATTR_TEXT_IN_SYSRAM              __attribute__ ((__section__(".sysram_code")))
#define ATTR_RODATA_IN_SYSRAM            __attribute__ ((__section__(".sysram_rodata")))

#define ATTR_RWDATA_IN_CACHED_SYSRAM     
#define ATTR_ZIDATA_IN_CACHED_SYSRAM    

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__(".noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__(".noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__(".noncached_sysram_zidata"),__aligned__(4)))


#endif

#define ATTR_PACKED __attribute__ ((__packed__))
#if (PRODUCT_VERSION == 5932)
#define ATTR_4BYTE_ALIGN __attribute__ ((__section__(".n9fw")__aligned__(4)))
#else
#define ATTR_4BYTE_ALIGN __attribute__ ((__aligned__(4)))
#endif

#elif defined(__CC_ARM)  /*KEIL VERSION*/

#if (PRODUCT_VERSION == 7686)
#define ATTR_TEXT_IN_TCM              __attribute__ ((__section__("tcm_code")))
#define ATTR_RODATA_IN_TCM            __attribute__ ((__section__("tcm_rodata")))
#define ATTR_RWDATA_IN_TCM            __attribute__ ((__section__("tcm_rwdata")))
#define ATTR_ZIDATA_IN_TCM            __attribute__ ((__section__("tcm_zidata")))


#define ATTR_TEXT_IN_RAM              __attribute__ ((__section__("ram_code")))
#define ATTR_RODATA_IN_RAM            __attribute__ ((__section__("ram_rodata")))
#define ATTR_RWDATA_IN_NONCACHED_RAM  __attribute__ ((__section__("noncached_ram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_RAM  __attribute__ ((__section__("noncached_ram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_ram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_ram_zidata"),__aligned__(4)))

#define ATTR_TEXT_IN_SYSRAM              __attribute__ ((__section__("sysram_code")))
#define ATTR_RODATA_IN_SYSRAM            __attribute__ ((__section__("sysram_rodata")))

#define ATTR_RWDATA_IN_CACHED_SYSRAM     __attribute__ ((__section__("cached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_CACHED_SYSRAM     __attribute__ ((__section__("cached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__("noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__("noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_zidata"),__aligned__(4)))

#else

#define ATTR_TEXT_IN_TCM              __attribute__ ((__section__("tcm_code")))
#define ATTR_RODATA_IN_TCM            __attribute__ ((__section__("tcm_rodata")))
#define ATTR_RWDATA_IN_TCM            __attribute__ ((__section__("tcm_rwdata")))
#define ATTR_ZIDATA_IN_TCM            __attribute__ ((__section__("tcm_zidata")))


#define ATTR_TEXT_IN_RAM              __attribute__ ((__section__("sysram_code")))
#define ATTR_RODATA_IN_RAM            __attribute__ ((__section__("sysram_rodata")))
#define ATTR_RWDATA_IN_NONCACHED_RAM  __attribute__ ((__section__("noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_RAM  __attribute__ ((__section__("noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_zidata"),__aligned__(4)))

#define ATTR_TEXT_IN_SYSRAM              __attribute__ ((__section__("sysram_code")))
#define ATTR_RODATA_IN_SYSRAM            __attribute__ ((__section__("sysram_rodata")))

#define ATTR_RWDATA_IN_CACHED_SYSRAM     
#define ATTR_ZIDATA_IN_CACHED_SYSRAM    

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__("noncached_sysram_rwdata")))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  __attribute__ ((__section__("noncached_sysram_zidata")))

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_rwdata"),__aligned__(4)))
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  __attribute__ ((__section__("noncached_sysram_zidata"),__aligned__(4)))


#endif

#define ATTR_PACKED __attribute__ ((__packed__))
#if (PRODUCT_VERSION == 5932)
#define ATTR_4BYTE_ALIGN __attribute__ ((__section__("n9fw")__aligned__(4)))
#else
#define ATTR_4BYTE_ALIGN __attribute__ ((__aligned__(4)))
#endif

#elif defined(__ICCARM__) /*IAR*/
#if (PRODUCT_VERSION == 7686)

#define ATTR_TEXT_IN_TCM              _Pragma("location=\".tcm_code\"")
#define ATTR_RODATA_IN_TCM            _Pragma("location=\".tcm_rodata\"")
#define ATTR_RWDATA_IN_TCM            _Pragma("location=\".tcm_rwdata\"")
#define ATTR_ZIDATA_IN_TCM            _Pragma("location=\".tcm_zidata\"")


#define ATTR_TEXT_IN_RAM              _Pragma("location=\".ram_code\"")
#define ATTR_RODATA_IN_RAM            _Pragma("location=\".ram_rodata\"")
#define ATTR_RWDATA_IN_NONCACHED_RAM  _Pragma("location=\".noncached_ram_rwdata\"")
#define ATTR_ZIDATA_IN_NONCACHED_RAM  _Pragma("location=\".noncached_ram_zidata\"")

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  _Pragma("location=\".noncached_ram_rwdata\"") \
                                                  _Pragma("data_alignment=4")
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  _Pragma("location=\".noncached_ram_zidata\"") \
                                                  _Pragma("data_alignment=4")

#define ATTR_TEXT_IN_SYSRAM              _Pragma("location=\".sysram_code\"")
#define ATTR_RODATA_IN_SYSRAM            _Pragma("location=\".sysram_rodata\"")

#define ATTR_RWDATA_IN_CACHED_SYSRAM      _Pragma("location=\".cached_sysram_rwdata\"")
#define ATTR_ZIDATA_IN_CACHED_SYSRAM     _Pragma("location=\".cached_sysram_zidata\"")

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  _Pragma("location=\".noncached_sysram_rwdata\"")
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  _Pragma("location=\".noncached_sysram_zidata\"")

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_rwdata\"") \
                                                _Pragma("data_alignment=4")
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_zidata\"") \
                                                  _Pragma("data_alignment=4")

#else
#define ATTR_TEXT_IN_TCM              _Pragma("location=\".tcm_code\"")
#define ATTR_RODATA_IN_TCM            _Pragma("location=\".tcm_rodata\"")
#define ATTR_RWDATA_IN_TCM            _Pragma("location=\".tcm_rwdata\"")
#define ATTR_ZIDATA_IN_TCM            _Pragma("location=\".tcm_zidata\"")


#define ATTR_TEXT_IN_RAM              _Pragma("location=\".sysram_code\"")
#define ATTR_RODATA_IN_RAM            _Pragma("location=\".sysram_rodata\"")
#define ATTR_RWDATA_IN_NONCACHED_RAM  _Pragma("location=\".noncached_sysram_rwdata\"")
#define ATTR_ZIDATA_IN_NONCACHED_RAM  _Pragma("location=\".noncached_sysram_zidata\"")

#define ATTR_RWDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_rwdata\"") \
                                                  _Pragma("data_alignment=4")
#define ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_zidata\"") \
                                                  _Pragma("data_alignment=4")

#define ATTR_TEXT_IN_SYSRAM              _Pragma("location=\".sysram_code\"")
#define ATTR_RODATA_IN_SYSRAM            _Pragma("location=\".sysram_rodata\"")

#define ATTR_RWDATA_IN_CACHED_SYSRAM     
#define ATTR_ZIDATA_IN_CACHED_SYSRAM  

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM  _Pragma("location=\".noncached_sysram_rwdata\"")
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM  _Pragma("location=\".noncached_sysram_zidata\"")

#define ATTR_RWDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_rwdata\"") \
                                                _Pragma("data_alignment=4")
#define ATTR_ZIDATA_IN_NONCACHED_SYSRAM_4BYTE_ALIGN  _Pragma("location=\".noncached_sysram_zidata\"") \
                                                 _Pragma("data_alignment=4")
#endif
#define ATTR_PACKED __packed
#if (PRODUCT_VERSION == 5932)
#define ATTR_4BYTE_ALIGN _Pragma("location=\".n9fw\" data_alignment=4")
#else
#define ATTR_4BYTE_ALIGN _Pragma("data_alignment=4")
#endif

#endif

#endif


