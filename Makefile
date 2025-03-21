ROOT_DIR := $(abspath $(CURDIR))

SUBDIR ?= $(ROOT_DIR)/lib

TARGET := test.out

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
LIBDIR := $(ROOT_DIR)/lib
LIBS := -Wl,--rpath=$(LIBDIR) -L$(LIBDIR) -lgic

INCS := $(ROOT_DIR)/include
CFLAGS ?= -O3 -Wall -Wextra -I$(INCS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(MAKE) -C $(SUBDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o $(TARGET)

.PHONY: all clean $(TARGET)
