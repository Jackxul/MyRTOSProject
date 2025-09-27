CC        := gcc
BIN       := demo

BUILD_DIR := ./build
FREERTOS_DIR_REL := ../../../FreeRTOS
FREERTOS_DIR     := $(abspath $(FREERTOS_DIR_REL))
KERNEL_DIR       := ${FREERTOS_DIR}/Source

file ?= main

INCLUDE_DIRS  := -I.
INCLUDE_DIRS  += -I${KERNEL_DIR}/include
INCLUDE_DIRS  += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS  += -I${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils

SOURCE_FILES  := $(file).c
SOURCE_FILES  += $(wildcard ${FREERTOS_DIR}/Source/*.c)
SOURCE_FILES  += ${KERNEL_DIR}/portable/MemMang/heap_3.c
SOURCE_FILES  += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES  += ${KERNEL_DIR}/portable/ThirdParty/GCC/Posix/port.c

CFLAGS   := -ggdb3 -O2
LDFLAGS  := -ggdb3 -pthread
CPPFLAGS := $(INCLUDE_DIRS)

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
DEP_FILE  = $(OBJ_FILES:%.o=%.d)

${BIN}: $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN}: ${OBJ_FILES}
	@mkdir -p $(@D)
	$(CC) $^ ${LDFLAGS} -o $@

-include ${DEP_FILE}

${BUILD_DIR}/%.o: %.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@

.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)

