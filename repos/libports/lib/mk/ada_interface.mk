
include $(REP_DIR)/lib/import/import-ada_interface.mk

SRC_ADS += cxx.ads \
	   cxx-block.ads \
	   cxx-block-client.ads \
	   cxx-genode.ads \
	   internals.ads \
	   internals-block.ads \
	   cai.ads \
	   cai-block.ads

SRC_ADB += cai-block-client.adb

SRC_CC += block_client.cc block_server.cc

CC_CXX_OPT += -Wno-attributes

LIBS = base spark

vpath %.cc $(CAI_PLATFORM_DIR)
vpath %.ads $(CAI_PLATFORM_DIR) $(CAI_INC_DIR)
vpath %.adb $(CAI_PLATFORM_DIR)

SHARED_LIB = yes
