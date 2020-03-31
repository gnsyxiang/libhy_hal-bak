# ===============================================================
# 
# Release under GPL-3.0.
# 
# @file    makefile
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    31/03 2020 12:07
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        31/03 2020      create the file
# 
#     last modified: 31/03 2020 12:07
# ===============================================================
TOP_DIR 	:= $(shell pwd)
TARGET_DIR 	:= $(TOP_DIR)/..
INC_DIR 	:= $(TARGET_DIR)/include
LIB_DIR 	:= $(TARGET_DIR)/lib
SRC_DIR 	:= $(TARGET_DIR)/example
3RD_LIB_DIR := $(TARGET_DIR)/3rd_lib

# CFLAGS
CFLAGS     	:= -g -fprofile-arcs -ftest-coverage
CFLAGS     	+= -Wall -Werror -std=gnu99
CFLAGS     	+= -I$(INC_DIR)
CFLAGS 	   	+= -Wno-error=unused-function -Wno-error=unused-variable

# LDFLAGS
LDFLAGS 	+= -Wl,-rpath=$(LIB_DIR)
LDFLAGS 	+= -L$(LIB_DIR) -L$(3RD_LIB_DIR)/tinyalsa/lib
LDFLAGS 	+= -lhal -lgcov -ltinyalsa

SRC_C := $(wildcard $(SRC_DIR)/*.c)
OBJ_C := $(patsubst %.c, %.o, $(SRC_C))

CC 		:= $(CROSS_COMPILE)gcc

all: demo log

log: log.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

demo: demo.o
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_C): %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf log demo

