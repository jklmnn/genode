
include $(REP_DIR)/lib/import/import-ada_interface.mk

SRC_ADS += cxx.ads \
	   cxx-block.ads \
	   cxx-genode.ads \
	   internals.ads \
	   internals-block.ads \
	   block.ads

SRC_ADB += block-client.adb

SRC_CC += block_class.cc

LIBS = base spark

vpath %.cc $(CAI_PLATFORM_DIR)
vpath %.ads $(CAI_PLATFORM_DIR) $(CAI_INC_DIR)
vpath %.adb $(CAI_PLATFORM_DIR)

SHARED_LIB = yes
