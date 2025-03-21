ROOT_DIR := $(abspath $(CURDIR)/..)

SO_MAJOR := 1
SO_MINOR := 0

SHARED_TARGET := libgic.so
STATIC_TARGET := libgic.a

TARGET := $(SHARED_TARGET) $(STATIC_TARGET)

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))


INCS := $(ROOT_DIR)/include
CFLAGS ?= -O3 -Wall -Wextra -I$(INCS) \
	  -fPIC

all: $(TARGET)

$(SHARED_TARGET): $(OBJS)
	$(CC) -shared -o $@.$(SO_MAJOR).$(SO_MINOR) $^
	ln -sfT $@.$(SO_MAJOR).$(SO_MINOR) $@.$(SO_MAJOR)
	ln -sfT $@.$(SO_MAJOR) $@

$(STATIC_TARGET): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o $(TARGET)

.PHONY: all clean $(TARGET)
