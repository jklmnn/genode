
CAI_INC_DIR = $(call select_from_ports,ada-interface)/ada-interface/src
CAI_PLATFORM_DIR = $(call select_from_ports,ada-interface)/ada-interface/platform/genode

INC_DIR += $(CAI_INC_DIR) $(CAI_PLATFORM_DIR)

SRC_CC += cai_main.cc
SRC_ADB += cai-component.adb

vpath cai_main.cc $(CAI_PLATFORM_DIR)
vpath cai-component.adb $(CAI_PLATFORM_DIR)
