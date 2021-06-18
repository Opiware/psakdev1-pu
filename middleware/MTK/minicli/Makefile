# Copyright Statement:
#

# This file is only for backward compatible with 4.0.0 and previous version. please use module.mk

SOURCE_DIR = ../../..
BINPATH     = ~/gcc-arm-none-eabi/bin
PROJ_PATH   ?= $(SOURCE_DIR)/project/mt7687_hdk/apps/iot_sdk/GCC
CONFIG_PATH ?= .

CFLAGS += -I$(PROJ_PATH)/../inc
CFLAGS += -I$(SOURCE_DIR)/$(CONFIG_PATH)

FEATURE    ?= feature.mk

include $(PROJ_PATH)/$(FEATURE)

# Gloabl Config
-include $(SOURCE_DIR)/.config
# IC Config
-include $(SOURCE_DIR)/config/chip/$(IC_CONFIG)/chip.mk
# Board Config
-include $(SOURCE_DIR)/config/board/$(BOARD_CONFIG)/board.mk

# Project name
TARGET_LIB=libminicli

BUILD_DIR = Build
OUTPATH = Build


# Sources
include $(SOURCE_DIR)/middleware/MTK/minicli/module.mk


C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)


.PHONY: all $(TARGET_LIB).a

all: $(TARGET_LIB).a m
	@echo Build $< Done

include $(SOURCE_DIR)/.rule.mk

clean:
	rm -rf $(OUTPATH)/$(TARGET_LIB).a
	rm -rf $(BUILD_DIR)

prebuilt_install:
	mkdir -p $(SOURCE_DIR)/prebuilt/middleware/MTK/minicli/lib
	
	cp $(BUILD_DIR)/$(TARGET_LIB).a $(SOURCE_DIR)/prebuilt/middleware/MTK/minicli/lib
