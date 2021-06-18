# Copyright Statement:
#

$(NAME)_PATH = middleware/third_party/httpd
C_FILES  += $($(NAME)_PATH)/src/os_port.c	\
		$($(NAME)_PATH)/src/axhttpd.c	\
		$($(NAME)_PATH)/src/proc.c	\
		$($(NAME)_PATH)/src/tdate_parse.c \
		$($(NAME)_PATH)/src/base64.c \
		$($(NAME)_PATH)/src/httpd_api.c \
		$($(NAME)_PATH)/src/auth_check.c \
 		$($(NAME)_PATH)/src/cgi_api.c \
 		$($(NAME)_PATH)/src/web_proc.c \
 		$($(NAME)_PATH)/src/cgi.c \
 		$($(NAME)_PATH)/web_c/webpage.c \
 		$($(NAME)_PATH)/web_c/web__AP_html.c \
 		$($(NAME)_PATH)/web_c/web__index_html.c \
 		$($(NAME)_PATH)/web_c/web__Test1_html.c \
 		$($(NAME)_PATH)/web_c/web__Test_html.c 

LwIP_VER ?= lwip-master
CFLAGS      += -I$(SOURCE_DIR)/middleware/third_party/httpd/inc
CFLAGS      += -I$(SOURCE_DIR)/middleware/third_party/httpd/Generate_file
CFLAGS      += -I$(SOURCE_DIR)/middleware/third_party/lwip/src/include
CFLAGS      += -I$(SOURCE_DIR)/middleware/third_party/lwip/ports/include
CFLAGS      += -I$(SOURCE_DIR)/middleware/MTK/nvdm/inc
CFLAGS  	+= -I$(SOURCE_DIR)/kernel/rtos/FreeRTOS/Source/include
CFLAGS  	+= -I$(SOURCE_DIR)/kernel/rtos/FreeRTOS/Source/portable/GCC/ARM_CM4F
CFLAGS  	+= -I$(SOURCE_DIR)/kernel/service/inc
CFLAGS  	+= -I$(SOURCE_DIR)/driver/chip/mt$(PRODUCT_VERSION)/inc
CFLAGS  	+= -I$(SOURCE_DIR)/driver/chip/inc

HTML_SRCS  	= $(wildcard web_html/*.html)
HTML_CS 	= $(patsubst web_html/%.html, middleware/third_party/httpd/web_c/web__%_html.c, $(HTML_SRCS))

HTM_SRCS  	= $(wildcard web_html/*.htm)
HTM_CS		= $(patsubst web_html/%.htm, middleware/third_party/httpd/web_c/web__%_htm.c, $(HTM_SRCS))

CSS_SRCS  	= $(wildcard web_html/*.css)
CSS_CS 		= $(patsubst web_html/%.css, middleware/third_party/httpd/web_c/web__%_css.c, $(CSS_SRCS))

JS_SRCS  	= $(wildcard web_html/*.js)
JS_CS 		= $(patsubst web_html/%.js, middleware/third_party/httpd/web_c/web__%_js.c, $(JS_SRCS))

JPEG_SRCS  	= $(wildcard web_html/*.jpeg)
JPEG_CS		= $(patsubst web_html/%.jpeg, middleware/third_party/httpd/web_c/web__%_jpeg.c, $(JPEG_SRCS))

JPG_SRCS  	= $(wildcard web_html/*.jpg)
JPG_CS 		= $(patsubst web_html/%.jpg, middleware/third_party/httpd/web_c/web__%_jpg.c, $(JPG_SRCS))

GIF_SRCS  	= $(wildcard web_html/*.gif)
GIF_CS 		= $(patsubst web_html/%.gif, middleware/third_party/httpd/web_c/web__%_gif.c, $(GIF_SRCS))

WEBPAGE_C	= middleware/third_party/httpd/web_c/webpage.c

###################################################
MID_HTTPD_PATH = $(SOURCE_DIR)/middleware/third_party/httpd
###################################################

###################################################
#MODULE_PATH += $(MID_HTTPD_PATH)
###################################################
