
C_SRC := alt_pll_reconfig.cpp
CFLAGS := -march=armv7-a -mfloat-abi=hard -mfpu=vfp3 -mthumb-interwork -mthumb -Og -g -feliminate-unused-debug-types -W -Wall -Werror -Itclap/ -Wwrite-strings -pedantic \

CC := $(CROSS_COMPILE)g++

ifeq ($(or $(COMSPEC),$(ComSpec)),)
RM := rm -rf
else
RM := cs-rm -rf
endif

ELF ?= $(basename $(firstword $(C_SRC)))

.PHONY: all
all:  $(ELF)

.PHONY:
clean:
	$(RM) $(OBJ) *.objdump *.map *.d $(ELF)

$(ELF): $(C_SRC)
	$(CC) $(CFLAGS) $< -o $@

