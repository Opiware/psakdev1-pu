# Copyright Statement:
#

SOURCE_DIR = ../../..
BINPATH     = ~/gcc-arm-none-eabi/bin
PROJ_PATH = ../../../project/mt2523_hdk/apps/iot_sdk_dev/GCC
CONFIG_PATH ?= .

CFLAGS += -I$(PROJ_PATH)/../inc
CFLAGS += -I$(SOURCE_DIR)/$(CONFIG_PATH)

ifdef DISABLE_CLI_MACRO
CFLAGS += -D$(DISABLE_CLI_MACRO)
endif
ifdef DISABLE_OS_MACRO
CFLAGS += -D$(DISABLE_OS_MACRO)
endif

FEATURE    ?= feature.mk

include $(PROJ_PATH)/$(FEATURE)

# Gloabl Config
-include $(SOURCE_DIR)/.config
# IC Config
-include $(SOURCE_DIR)/config/chip/$(IC_CONFIG)/chip.mk
# Board Config
-include $(SOURCE_DIR)/config/board/$(BOARD_CONFIG)/board.mk

# Project name
TARGET_LIB  = libfota

BUILD_DIR = Build
OUTPATH = Build


# Sources
include module.mk

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)


.PHONY: $(TARGET_LIB).a

all: $(TARGET_LIB).a
	@echo Build $< Done

include $(SOURCE_DIR)/.rule.mk

clean:
	rm -rf $(OUTPATH)/$(TARGET_LIB).a
	rm -rf $(BUILD_DIR)


