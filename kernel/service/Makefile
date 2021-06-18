# Copyright Statement:
#

# This file is only for backward compatible with 4.0.0 and previous version. please use module.mk

SOURCE_DIR = ../..
BINPATH    = ~/gcc-arm-none-eabi/bin

ifeq ($(PRODUCT_VERSION),7687)
PROJ_PATH ?= ../../project/mt7687_hdk/apps/iot_sdk/GCC
endif

ifeq ($(PRODUCT_VERSION),7697)
PROJ_PATH ?= ../../project/mt7697_hdk/apps/iot_sdk/GCC
endif

ifeq ($(PRODUCT_VERSION),2523)
PROJ_PATH ?= ../../project/mt2523_hdk/apps/iot_sdk_dev/GCC
endif

ifeq ($(PRODUCT_VERSION),2533)
PROJ_PATH ?= ../../project/mt2533_evb/apps/headset_gui_ref_design/GCC
endif

ifeq ($(PRODUCT_VERSION),7686)
PROJ_PATH ?= ../../project/mt7686_hdk/apps/iot_sdk_demo/GCC
endif

ifeq ($(PRODUCT_VERSION),7682)
PROJ_PATH ?= ../../project/mt7682_hdk/apps/iot_sdk_demo/GCC
endif

ifeq ($(PRODUCT_VERSION),5932)
PROJ_PATH ?= ../../project/mt5932_hdk/apps/iot_sdk/GCC
endif

CONFIG_PATH ?= .

CFLAGS += -I$(PROJ_PATH)/../inc
CFLAGS += -I../../$(CONFIG_PATH)

FEATURE    ?= feature.mk

-include $(PROJ_PATH)/$(FEATURE)

# Gloabl Config
-include $(SOURCE_DIR)/.config
# IC Config
-include $(SOURCE_DIR)/config/chip/$(IC_CONFIG)/chip.mk
# Board Config
-include $(SOURCE_DIR)/config/board/$(BOARD_CONFIG)/board.mk

ifeq ($(MTK_PORT_SERVICE_ENABLE),y)
CFLAGS += -I$(SOURCE_DIR)/middleware/MTK/port_service/inc
endif

# Project name
TARGET_LIB = libservice

BUILD_DIR  = Build
OUTPATH    = Build

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


