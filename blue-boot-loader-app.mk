TARGET = tiny
BUILD_DIR = ./build/blue-boot-loader-app

DEVICE := stm8s103f3
DEVICE_TYPE := STM8S103
STLINK := stlinkv2
OPENOCD_CFG := openocd/stm8s103.cfg

MAIN := src/app/blue-boot-loader-app/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/blue-boot-loader-app \

LIB_FILES := \
  src/peripheral/clock.c \
  src/peripheral/pb5_heartbeat.c \
  src/peripheral/tim4_system_tick.c \
  src/peripheral/watchdog.c \

LIB_DIRS := \
  lib/tiny/src \
  src/device \

INC_DIRS := \
  lib/stm8/inc \
  src/peripheral \

include makefile-worker.mk
