/* Copyright Statement:
 *
 */

#ifndef	__CGI_API_H__
#define	__CGI_API_H__
//==============================================================================
//                                INCLUDE FILES
//==============================================================================

//==============================================================================
//                               MACROS PORTED FROM APUI
//==============================================================================

typedef unsigned long long		UINT64;
typedef int					INT32;
typedef long long 				INT64;

typedef unsigned char			UCHAR;
typedef unsigned short			USHORT;
typedef unsigned int			UINT;
typedef unsigned long			ULONG;

typedef unsigned char *		PUINT8;
typedef unsigned short *		PUINT16;
typedef unsigned int *			PUINT32;
typedef unsigned long long *	PUINT64;
typedef int *					PINT32;
typedef long long * 			PINT64;
typedef char 					STRING;
typedef signed char			CHAR;

typedef signed short			SHORT;
typedef signed int				INT;
typedef signed long			LONG;
typedef signed long long		LONGLONG;

typedef unsigned long long		ULONGLONG;

typedef unsigned char			BOOLEAN;
typedef void					VOID;

typedef char *				PSTRING;
typedef VOID *				PVOID;
typedef CHAR *				PCHAR;
typedef UCHAR * 				PUCHAR;
typedef USHORT *				PUSHORT;
typedef LONG *				PLONG;
typedef ULONG *				PULONG;
typedef UINT *				PUINT;

//==============================================================================
//                               Definitions PORTED FROM APUI
//==============================================================================


//==============================================================================
//                                    MACROS
//==============================================================================
#define	CGI_MAP(name,id)	CGI_var_map(cn,#name,id)
#define	CGI_CFG_ID(id)		WEB_printf(cn,"%u",id)
#define	CGI_CFG_GET(id)		CGI_get_cfg(cn,id)
#define	CGI_QUERY(var)		CGI_put_var(cn,var)
#define	CGI_DO_CMD()		WEB_printf(cn, "%d", CGI_do_cmd(cn))

#define CGI_AP_SSID()       CGI_get_ap_ssid(cn)
#define CGI_AP_PASSWD()     CGI_get_ap_passwd(cn)

#define CGI_MT7687AP_SSID()       CGI_get_mt7687ap_ssid(cn)
#define CGI_MT7687AP_PASSWD()     CGI_get_mt7687ap_passwd(cn)

//==============================================================================
//                               TYPE DEFINITIONS
//==============================================================================

//==============================================================================
//                               LOCAL VARIABLES
//==============================================================================

//==============================================================================
//                          LOCAL FUNCTION PROTOTYPES
//==============================================================================

//==============================================================================
//                              EXTERNAL FUNCTIONS
//==============================================================================
extern void CGI_var_map(struct connstruct *cn, char *name, int id);
extern void CGI_var_map_array(struct connstruct *cn, char *name, int id, int num);
extern void CGI_get_cfg(struct connstruct *cn, int tag);
extern char * CGI_put_var(struct connstruct *cn, char *var);
extern int CGI_do_cmd(struct connstruct *cn);

extern void CGI_get_ap_ssid(struct connstruct *cn);
extern void CGI_get_ap_passwd(struct connstruct *cn);

extern void CGI_get_mt7687ap_ssid(struct connstruct *cn);
extern void CGI_get_mt7687ap_passwd(struct connstruct *cn);

//==============================================================================
//                              EXTERNAL FUNCTIONS FOR WLAN
//==============================================================================

#endif //__CGI_API_H__

