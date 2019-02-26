
CAI_INC_DIR = $(call select_from_ports,ada-interface)/ada-interface/src
CAI_PLATFORM_DIR = $(call select_from_ports,ada-interface)/ada-interface/platform/genode

INC_DIR += $(CAI_INC_DIR) $(CAI_PLATFORM_DIR)

#vpath block-client.ads $(CAI_INC_DIR)
