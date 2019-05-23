include $(REP_DIR)/lib/mk/spark.inc

ADALIB     = $(ADA_RTS)/adalib
ADAINCLUDE = $(ADA_RTS)/adainclude

SRC_ADS += system.ads \
	   s-soflin.ads \
	   s-unstyp.ads \
	   interfac.ads \
	   i-cexten.ads \
	   a-except.ads \
	   ada.ads

SRC_ADB += s-stalib.adb s-secsta.adb s-parame.adb i-c.adb s-arit64.adb s-stoele.adb
CUSTOM_ADA_FLAGS = --RTS=$(ADA_RTS) -c -gnatg -gnatp -gnatpg -gnatn2

# C runtime glue code
SRC_CC += genode.cc
SRC_C += init.c

# Ada packages that implement runtime functionality
SRC_ADS += runtime_lib.ads \
	   runtime_lib-exceptions.ads
SRC_ADB += runtime_lib-secondary_stack.adb \
	   runtime_lib-strings.adb \
	   runtime_lib-debug.adb \
	   runtime_lib-platform.adb \
	   s-init.adb

vpath %.cc  $(ADA_RUNTIME_PLATFORM_DIR)

vpath s-soflin.ads $(ADA_RUNTIME_DIR)
vpath a-except.ads $(ADA_RUNTIME_DIR)

vpath s-secsta.adb $(ADA_RUNTIME_DIR)
vpath s-soflin.adb $(ADA_RUNTIME_DIR)
vpath s-stalib.adb $(ADA_RUNTIME_DIR)
vpath s-parame.adb $(ADA_RUNTIME_DIR)
vpath a-except.adb $(ADA_RUNTIME_DIR)
vpath i-c.adb $(ADA_RUNTIME_DIR)

vpath %.ads $(ADA_RTS_SOURCE)
vpath %.adb $(ADA_RTS_SOURCE)

vpath runtime_lib% $(ADA_RUNTIME_LIB_DIR)
vpath init.c $(ADA_RUNTIME_LIB_DIR)
vpath s-init.adb $(ADA_RUNTIME_COMMON_DIR)

SHARED_LIB = yes
