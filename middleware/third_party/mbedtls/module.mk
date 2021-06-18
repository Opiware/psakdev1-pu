# Copyright Statement:
#

MBEDTLS_SRC = middleware/third_party/mbedtls


#
# Get the list of C files
#

mbedtls_PATH = $(shell pwd)

C_FILES += $(MBEDTLS_SRC)/port/porting_layer.c \
$(MBEDTLS_SRC)/library/aes.c \
$(MBEDTLS_SRC)/library/aesni.c \
$(MBEDTLS_SRC)/library/arc4.c \
$(MBEDTLS_SRC)/library/asn1parse.c \
$(MBEDTLS_SRC)/library/asn1write.c \
$(MBEDTLS_SRC)/library/base64.c \
$(MBEDTLS_SRC)/library/bignum.c \
$(MBEDTLS_SRC)/library/blowfish.c \
$(MBEDTLS_SRC)/library/camellia.c \
$(MBEDTLS_SRC)/library/ccm.c \
$(MBEDTLS_SRC)/library/certs.c \
$(MBEDTLS_SRC)/library/cipher.c \
$(MBEDTLS_SRC)/library/cipher_wrap.c \
$(MBEDTLS_SRC)/library/ctr_drbg.c \
$(MBEDTLS_SRC)/library/debug.c \
$(MBEDTLS_SRC)/library/des.c \
$(MBEDTLS_SRC)/library/dhm.c \
$(MBEDTLS_SRC)/library/ecdh.c \
$(MBEDTLS_SRC)/library/ecdsa.c \
$(MBEDTLS_SRC)/library/ecp.c \
$(MBEDTLS_SRC)/library/ecp_curves.c \
$(MBEDTLS_SRC)/library/entropy.c \
$(MBEDTLS_SRC)/library/entropy_poll.c \
$(MBEDTLS_SRC)/library/error.c \
$(MBEDTLS_SRC)/library/gcm.c \
$(MBEDTLS_SRC)/library/havege.c \
$(MBEDTLS_SRC)/library/hmac_drbg.c \
$(MBEDTLS_SRC)/library/md2.c \
$(MBEDTLS_SRC)/library/md4.c \
$(MBEDTLS_SRC)/library/md5.c \
$(MBEDTLS_SRC)/library/md.c \
$(MBEDTLS_SRC)/library/md_wrap.c \
$(MBEDTLS_SRC)/library/memory_buffer_alloc.c \
$(MBEDTLS_SRC)/library/oid.c \
$(MBEDTLS_SRC)/library/padlock.c \
$(MBEDTLS_SRC)/library/pem.c \
$(MBEDTLS_SRC)/library/pk.c \
$(MBEDTLS_SRC)/library/pkcs11.c \
$(MBEDTLS_SRC)/library/pkcs12.c \
$(MBEDTLS_SRC)/library/pkcs5.c \
$(MBEDTLS_SRC)/library/pkparse.c \
$(MBEDTLS_SRC)/library/pk_wrap.c \
$(MBEDTLS_SRC)/library/pkwrite.c \
$(MBEDTLS_SRC)/library/platform.c \
$(MBEDTLS_SRC)/library/ripemd160.c \
$(MBEDTLS_SRC)/library/rsa.c \
$(MBEDTLS_SRC)/library/sha1.c \
$(MBEDTLS_SRC)/library/sha256.c \
$(MBEDTLS_SRC)/library/sha512.c \
$(MBEDTLS_SRC)/library/ssl_cache.c \
$(MBEDTLS_SRC)/library/ssl_ciphersuites.c \
$(MBEDTLS_SRC)/library/ssl_cli.c \
$(MBEDTLS_SRC)/library/ssl_srv.c \
$(MBEDTLS_SRC)/library/ssl_tls.c \
$(MBEDTLS_SRC)/library/threading.c \
$(MBEDTLS_SRC)/library/timing.c \
$(MBEDTLS_SRC)/library/version.c \
$(MBEDTLS_SRC)/library/version_features.c \
$(MBEDTLS_SRC)/library/x509.c \
$(MBEDTLS_SRC)/library/x509_create.c \
$(MBEDTLS_SRC)/library/x509_crl.c \
$(MBEDTLS_SRC)/library/x509_crt.c \
$(MBEDTLS_SRC)/library/x509_csr.c \
$(MBEDTLS_SRC)/library/x509write_crt.c \
$(MBEDTLS_SRC)/library/x509write_csr.c \
$(MBEDTLS_SRC)/library/xtea.c \
$(MBEDTLS_SRC)/library/ssl_cookie.c \
$(MBEDTLS_SRC)/library/ssl_ticket.c \
$(MBEDTLS_SRC)/library/cmac.c \
$(MBEDTLS_SRC)/library/ecjpake.c \
$(MBEDTLS_SRC)/library/net_sockets.c \


#################################################################################
#include path
CFLAGS  += -I./src/mbedtls/configs
CFLAGS  += $(FPUFLAGS) -DPRODUCT_VERSION=$(PRODUCT_VERSION)
CFLAGS  += -fno-common
CFLAGS  += -fomit-frame-pointer
CFLAGS  += -DSUPPORT_MBEDTLS
CFLAGS  += -I./src/mbedtls/include
CFLAGS	+= -I$(SOURCE_DIR)/middleware/third_party/lwip/src/include
CFLAGS  += -I$(SOURCE_DIR)/middleware/third_party/lwip/src/include/lwip
CFLAGS  += -I$(SOURCE_DIR)/middleware/third_party/lwip/ports/include
CFLAGS  += -I$(SOURCE_DIR)/middleware/third_party/mbedtls/include
CFLAGS  += -I$(SOURCE_DIR)/middleware/third_party/mbedtls/configs
CFLAGS  += -I$(SOURCE_DIR)/kernel/rtos/FreeRTOS/Source/include 
CFLAGS  += -I$(SOURCE_DIR)/kernel/rtos/FreeRTOS/Source/portable/GCC/ARM_CM4F
CFLAGS  += -I$(SOURCE_DIR)/kernel/service/inc

