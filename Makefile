.SUFFIXES:

.DEFAULT_GOAL := help

ROOT_DIR := $(CURDIR)
export ROOT_DIR

BUILD_3DS := build-3ds
TARGET_3DS := cinnamon
SOURCES_3DS := src src/n3ds
INCLUDES_3DS := src src/n3ds vendor vendor/stb/ds

BUILD_WIIU := build-wiiu

.PHONY: help 3ds 3ds-clean wiiu wiiu-clean

help:
	@echo "Available targets: 3ds, 3ds-clean, wiiu, wiiu-clean"

wiiu:
	@cmake -S "$(ROOT_DIR)" -B "$(ROOT_DIR)/$(BUILD_WIIU)" -G "Unix Makefiles" \
		-DCMAKE_MAKE_PROGRAM=/usr/bin/make \
		-DCMAKE_TOOLCHAIN_FILE="$(DEVKITPRO)/cmake/WiiU.cmake" \
		-DPLATFORM=wiiu \
		-DCMAKE_BUILD_TYPE=Release
	@cmake --build "$(ROOT_DIR)/$(BUILD_WIIU)"

wiiu-clean:
	@rm -rf "$(ROOT_DIR)/$(BUILD_WIIU)"

THREEDS_GOALS := 3ds 3ds-inner

ifneq ($(filter $(THREEDS_GOALS),$(MAKECMDGOALS)),)

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(ROOT_DIR)
include $(DEVKITARM)/3ds_rules

ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS := -g -Wall -O2 -mword-relocations \
	-ffunction-sections \
	$(ARCH)

CFLAGS += $(INCLUDE) -D__3DS__ -DENABLE_BC16
ASFLAGS := -g $(ARCH)
LDFLAGS = -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS := -lcitro2d -lcitro3d -lctru -lm
LIBDIRS := $(PORTLIBS) $(CTRULIB)

ifneq ($(BUILD_3DS),$(notdir $(CURDIR)))

export OUTPUT := $(ROOT_DIR)/$(BUILD_3DS)/$(TARGET_3DS)
export VPATH := $(foreach dir,$(SOURCES_3DS),$(ROOT_DIR)/$(dir))
export DEPSDIR := $(ROOT_DIR)/$(BUILD_3DS)

CFILES := $(foreach dir,$(SOURCES_3DS),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir,$(SOURCES_3DS),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES := $(foreach dir,$(SOURCES_3DS),$(notdir $(wildcard $(dir)/*.s)))

ifeq ($(strip $(CPPFILES)),)
export LD := $(CC)
else
export LD := $(CXX)
endif

export OFILES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE := $(foreach dir,$(INCLUDES_3DS),-I$(ROOT_DIR)/$(dir)) \
	$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
	-I$(ROOT_DIR)/$(BUILD_3DS)
export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)
export _3DSXDEPS :=

3ds: $(ROOT_DIR)/$(BUILD_3DS)
	@$(MAKE) --no-print-directory -C "$(ROOT_DIR)/$(BUILD_3DS)" -f "$(ROOT_DIR)/Makefile" 3ds-inner

$(ROOT_DIR)/$(BUILD_3DS):
	@mkdir -p "$@"

else

3ds-inner: $(OUTPUT).3dsx

$(OUTPUT).3dsx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

-include $(DEPSDIR)/*.d

endif

endif

3ds-clean:
	@rm -rf "$(ROOT_DIR)/$(BUILD_3DS)"
