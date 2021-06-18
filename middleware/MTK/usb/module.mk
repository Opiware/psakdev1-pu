# Copyright Statement:
#

FEATURE ?= feature.mk
include $(FEATURE)

USB_CDC_ACM_ENABLE = y
USB_MASS_STORAGE_ENABLE = y

###################################################
# Sources
USB_SRC = middleware/MTK/usb/src

USB_SRC_FILES += $(USB_SRC)/_common/usb_main.c \
             $(USB_SRC)/_common/usb_resource.c \
             $(USB_SRC)/_common/usb_custom.c \
             $(USB_SRC)/_common/usb.c

ifeq ($(USB_CDC_ACM_ENABLE), y)
USB_SRC_FILES += $(USB_SRC)/cdc/usbacm_drv.c \
             $(USB_SRC)/cdc/usbacm_adap.c
endif

ifeq ($(USB_MASS_STORAGE_ENABLE), y)
CFLAGS += -D__USB_MASS_STORAGE_ENABLE__
USB_SRC_FILES += $(USB_SRC)/msc/usbms_adap.c \
                 $(USB_SRC)/msc/usbms_drv.c \
                 $(USB_SRC)/msc/usbms_state.c \
                 $(USB_SRC)/msc/usbms_msdc.c \
                 $(USB_SRC)/msc/USBMS_snand.c
endif

CFLAGS += -D__MTK_TARGET__

C_FILES += $(USB_SRC_FILES)

###################################################
# include path
CFLAGS += -I$(SOURCE_DIR)/middleware/MTK/usb/inc
CFLAGS += -I$(SOURCE_DIR)/middleware/MTK/serial_nand/inc
CFLAGS += -I$(SOURCE_DIR)/driver/chip/inc