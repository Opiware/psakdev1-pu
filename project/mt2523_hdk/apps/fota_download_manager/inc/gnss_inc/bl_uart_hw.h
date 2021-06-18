/* Copyright Statement:
 *
 */

#ifndef __BL_UART_HW_H__
#define __BL_UART_HW_H__

#ifdef __cplusplus
extern "C" {
#endif

#define   BL_UART0_BASE    0xa00d0000
#define   BL_UART0_RBR     (BL_UART0_BASE+0x0)    /* Read only */
#define   BL_UART0_THR     (BL_UART0_BASE+0x0)    /* Write only */
#define   BL_UART0_DLL     (BL_UART0_BASE+0x0)
#define   BL_UART0_IER     (BL_UART0_BASE+0x4)
#define   BL_UART0_DLH     (BL_UART0_BASE+0x4)
#define   BL_UART0_IIR     (BL_UART0_BASE+0x8)    /* Read only */
#define   BL_UART0_FCR     (BL_UART0_BASE+0x8)    /* Write only */
#define   BL_UART0_EFR     (BL_UART0_BASE+0x8)    /* Only when LCR = 0xbf */
#define   BL_UART0_LCR     (BL_UART0_BASE+0xc)
#define   BL_UART0_MCR     (BL_UART0_BASE+0x10)
#define   BL_UART0_LSR     (BL_UART0_BASE+0x14)
#define   BL_UART0_SCR     (BL_UART0_BASE+0x1c)
#define   BL_UART0_SPEED   (BL_UART0_BASE+0x24)


/* IER */
#define   BL_UART_IER_ERBFI            0x0001
#define   BL_UART_IER_ETBEI            0x0002
#define   BL_UART_IER_ELSI             0x0004
#define   BL_UART_IER_EDSSI            0x0008
#define   BL_UART_IER_XOFFI            0x0020
#define   BL_UART_IER_RTSI             0x0040
#define   BL_UART_IER_CTSI             0x0080
#define   BL_IER_HW_NORMALINTS         0x000d
#define   BL_IER_HW_ALLINTS            0x000f
#define   BL_IER_SW_NORMALINTS         0x002d
#define   BL_IER_SW_ALLINTS            0x002f
#define   BL_UART_IER_ALLOFF           0x0000


/* FCR */
#define   BL_UART_FCR_FIFOEN            0x0001
#define   BL_UART_FCR_CLRR              0x0002
#define   BL_UART_FCR_CLRT              0x0004
#define   BL_UART_FCR_FIFOINI           0x0007
#define   BL_UART_FCR_RX_1BYTE_LEVEL    0x0000
#define   BL_UART_FCR_RX_6BYTE_LEVEL    0x0040
#define   BL_UART_FCR_RX_12BYTE_LEVEL   0x0080
#define   BL_UART_FCR_TX_1BYTE_LEVEL    0x0000
#define   BL_UART_FCR_TX_4BYTE_LEVEL    0x0010
#define   BL_UART_FCR_TX_8BYTE_LEVEL    0x0020
#define   BL_UART_FCR_TX_14BYTE_LEVEL   0x0030
#define   BL_UART_FCR_NORMAL           (BL_UART_FCR_TX_4BYTE_LEVEL|BL_UART_FCR_RX_12BYTE_LEVEL|BL_UART_FCR_FIFOINI)

/* LCR */
#define   BL_UART_WLS_8                0x0003
#define   BL_UART_WLS_7                0x0002
#define   BL_UART_WLS_6                0x0001
#define   BL_UART_WLS_5                0x0000
#define   BL_UART_DATA_MASK            0x0003
#define   BL_UART_NONE_PARITY          0x0000
#define   BL_UART_ODD_PARITY           0x0008
#define   BL_UART_EVEN_PARITY          0x0018
#define   BL_UART_MARK_PARITY          0x0028
#define   BL_UART_SPACE_PARITY         0x0038
#define   BL_UART_PARITY_MASK          0x0038
#define   BL_UART_1_STOP               0x0000
#define   BL_UART_1_5_STOP             0x0004  /* Only valid for 5 data bits */
#define   BL_UART_2_STOP               0x0004
#define   BL_UART_STOP_MASK            0x0004
#define   BL_UART_LCR_DLAB             0x0080

/* MCR */
#define   BL_UART_MCR_RTS              0x0002
#define   BL_UART_MCR_LOOPB            0x0010
#define   BL_UART_MCR_XOFF             0x0080


/* LSR */
#define   BL_UART_LSR_DR               0x0001
#define   BL_UART_LSR_OE               0x0002
#define   BL_UART_LSR_PE               0x0004
#define   BL_UART_LSR_FE               0x0008
#define   BL_UART_LSR_BI               0x0010
#define   BL_UART_LSR_THRE             0x0020
#define   BL_UART_LSR_TEMT             0x0040
#define   BL_UART_LSR_FIFOERR          0x0080

/* HIGHSPEED */
#define   BL_UART_SPEED_DIV_16			0x0000
#define   BL_UART_SPEED_DIV_8			0x0001
#define   BL_UART_SPEED_DIV_4			0x0002


#ifdef __cplusplus
}
#endif

#endif /* __BL_UART_HW_H__ */
