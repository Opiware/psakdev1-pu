# Copyright Statement:
#
.NOTPARALLEL:

SOURCE_DIR = ../../..
BINPATH = ~/gcc-arm-none-eabi/bin
PROJ_PATH = ../../../project/mt7687_hdk/apps/iot_sdk/GCC

FEATURE    ?= feature.mk

include $(PROJ_PATH)/$(FEATURE)

# Gloabl Config
-include $(SOURCE_DIR)/.config
# IC Config
-include $(SOURCE_DIR)/config/chip/$(IC_CONFIG)/chip.mk
# Board Config
-include $(SOURCE_DIR)/config/board/$(BOARD_CONFIG)/board.mk

# suppress all building warning in this module
CFLAGS += -w

CFLAGS += -I$(PROJ_PATH)/../inc
# Project name
TARGET_LIB=libhttpd

BUILD_DIR = Build
OUTPATH = Build

ifeq ($(TGN_VERIFI_ENABLE), 1)
CFLAGS         += -DTGN_VERIFI_ENABLE=1
endif

# Sources
include module.mk

C_OBJS = $(C_FILES:%.c=$(BUILD_DIR)/%.o)
HTML_OBJS = $(HTML_CS:%.c=$(BUILD_DIR)/%.o)
HTM_OBJS = $(HTM_CS:%.c=$(BUILD_DIR)/%.o)
CSS_OBJS = $(CSS_CS:%.c=$(BUILD_DIR)/%.o)
JS_OBJS = $(JS_CS:%.c=$(BUILD_DIR)/%.o)
JPEG_OBJS = $(JPEG_CS:%.c=$(BUILD_DIR)/%.o)
JPG_OBJS = $(JPG_CS:%.c=$(BUILD_DIR)/%.o)
GIF_OBJS = $(GIF_CS:%.c=$(BUILD_DIR)/%.o)
WEBPAGE_OBJS = $(WEBPAGE_C:%.c=$(BUILD_DIR)/%.o)

.PHONY: $(TARGET_LIB).a

all: web_c/web_c.o $(TARGET_LIB).a
	-rm -f ./web_c/.objfiles
	-rm -f ./web_c/*.bin
	-rm -f ./web_c/*.dbg
	-rm -f ./web_c/web_list
	-rm -f ./web_c/webcomp_sin
	@echo Build $< Done

$(TARGET_LIB).a: web_c/web_c.o $(HTML_OBJS) $(HTM_OBJS) $(JPEG_OBJS) $(JPG_OBJS) $(GIF_OBJS) $(CSS_OBJS) $(JS_OBJS) $(WEBPAGE_OBJS) $(C_OBJS)
	@echo Gen $(TARGET_LIB).a
	@echo Gen $(TARGET_LIB).a >>$(BUILD_LOG)
	@echo $(AR) -r $(OUTPATH)/$@ $^
	#@$(AR) -r $(OUTPATH)/$@ $^ >>$(BUILD_LOG)
	@$(AR) -r $(OUTPATH)/$@ $(HTML_OBJS) $(HTM_OBJS) $(JPEG_OBJS) $(JPG_OBJS) $(GIF_OBJS) $(CSS_OBJS) $(JS_OBJS) $(WEBPAGE_OBJS) $(C_OBJS) >>$(BUILD_LOG)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo Build... $$(basename $@)
	@echo Build... $@ >> $(BUILD_LOG)
	@echo $(CC) $(CFLAGS) $@ >> $(BUILD_LOG)
	@$(CC) $(CFLAGS) -c $< -o $@ 2>>$(ERR_LOG)

$(BUILD_DIR)/%.d: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@set -e; rm -f $@; \
	export D_FILE="$@"; \
	export B_NAME=`echo $$D_FILE | sed 's/\.d//g'`; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's@\(.*\)\.o@'"$$B_NAME\.o $$B_NAME\.d"'@g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -rf $(OUTPATH)/$(TARGET_LIB).a
	rm -rf $(BUILD_DIR)

#################################################################################
DOS2UNIX = dos2unix
WEB_DIR	= web_html

web_c/web_c.o: webcomp_sin $(WEB_DIR)/*
	echo "make web pages library"
	rm -rf $(wildcard $(WEB_DIR)/*.bak)
	$(DOS2UNIX) $(WEB_DIR)/*.* ;
ifeq ($(CROSS_COMPILE),win)
	find $(WEB_DIR) -name "*.*" | sort > web_list
else
	find $(WEB_DIR) -name "*.*" > web_list
endif
	if [ ! -e web_c ] ; then mkdir web_c ; else rm -f web_c/* ; fi
	sh ./webcomp.sh $(WEB_DIR)
	-mv -f webpage.h ./inc/webpage.h
	-mv -f webdata.h ./inc/webdata.h
	-mv -f webpage.c ./web_c/webpage.c
	-mv -f webcomp_sin ./web_c/webcomp_sin
	-mv -f web_list ./web_c/web_list
	-mv -f webdata.bin ./web_c/webdata.bin
ifeq ($(CROSS_COMPILE),win)
	dos2unix ./web_c/webpage.c ;
endif

webcomp_sin: webcomp_sin.c
	@echo "clean webpages.."
	-rm -rf web_c
	-rm -f ./inc/webpage.h
	-rm -f ./inc/webdata.h
	find . \( -name '*.[oasd]' -o -name '.*.flags' \) -type f -print | xargs rm -f
	gcc -o webcomp_sin webcomp_sin.c;

#################################################################################

