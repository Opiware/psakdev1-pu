# Copyright Statement:
#

###################################################
# Sources
KERNEL_SERVICE_SRC    = kernel/service/src

KERNEL_SERVICE_FILES += $(KERNEL_SERVICE_SRC)/context_info_save.c \
                        $(KERNEL_SERVICE_SRC)/exception_handler.c \
                        $(KERNEL_SERVICE_SRC)/mtk_HeapSizeGuard.c \
                        $(KERNEL_SERVICE_SRC)/os_cli.c \
                        $(KERNEL_SERVICE_SRC)/os_port_callback.c \
                        $(KERNEL_SERVICE_SRC)/os_trace_callback.c \
                        $(KERNEL_SERVICE_SRC)/syslog.c \
                        $(KERNEL_SERVICE_SRC)/syslog_cli.c \
                        $(KERNEL_SERVICE_SRC)/toi.c \
                        $(KERNEL_SERVICE_SRC)/utils.c \

C_FILES += $(KERNEL_SERVICE_FILES)

###################################################
# include path
CFLAGS += -I$(SOURCE_DIR)/kernel/service/inc
CFLAGS += -I$(SOURCE_DIR)/kernel/rtos/FreeRTOS/Source/include
CFLAGS += -I$(SOURCE_DIR)/middleware/MTK/minicli/inc

