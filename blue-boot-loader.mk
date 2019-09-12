TARGET = tiny
BUILD_DIR = ./build/blue-boot-loader

DEVICE := stm8s103f3
DEVICE_TYPE := STM8S103
STLINK := stlinkv2
OPENOCD_CFG := openocd/stm8s103.cfg

MAIN := src/app/blue-boot-loader/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/blue-boot-loader \

LIB_FILES := \
  src/peripheral/clock.c \

LIB_DIRS := \
  lib/tiny/src \
  src/device \

INC_DIRS := \
  lib/stm8/inc \
  src/peripheral \

include makefile-worker.mk
