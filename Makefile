# Copyright (c) 2026 Christiaan (chris@boreddev.nl)
# Lua Standalone Makefile

CC = x86_64-elf-gcc
LD = x86_64-elf-ld

ifneq ($(BOREDOS_SDK),)
  ifeq ($(wildcard $(BOREDOS_SDK)/lib/libc.a),)
    BOOTSTRAP_SDK = $(BOREDOS_SDK)
    SDK_PATH      = $(BOREDOS_SDK)
  else
    SDK_PATH      = $(BOREDOS_SDK)
  endif
endif

ifeq ($(SDK_PATH),)
  SDK_PATH = $(abspath build/sdk)
  ifeq ($(wildcard $(SDK_PATH)/lib/libc.a),)
    BOOTSTRAP_SDK = $(SDK_PATH)
  endif
endif

DESTDIR ?= $(abspath build/dist)

LUA_CFLAGS = -std=gnu11 -ffreestanding -O2 -fno-stack-protector -fno-stack-check \
             -fno-lto -fno-pie -m64 -march=x86-64 -mno-red-zone \
             -isystem src/sysinclude -I. -I$(SDK_PATH)/include -Isrc -DLUA_USE_C89 \
             -Wno-conversion -Wno-sign-conversion -Wno-double-promotion \
             -Wno-unused-parameter -Wno-missing-declarations -Wno-shadow -Wno-undef \
             -Wno-redundant-decls -Wno-old-style-definition -Wno-missing-prototypes \
             -Wno-implicit-fallthrough -Wno-type-limits

LDFLAGS = -m elf_x86_64 -nostdlib -static -no-pie -Ttext=0x40000000 \
          --no-dynamic-linker -z text -z max-page-size=0x1000 -e _start \
          -L$(SDK_PATH)/lib

APPS    = lua.elf

all: bootstrap-sdk $(APPS)

.PHONY: bootstrap-sdk
bootstrap-sdk:
ifdef BOOTSTRAP_SDK
	@if [ ! -f "$(BOOTSTRAP_SDK)/lib/libc.a" ]; then \
		if [ -d "../libc" ]; then \
			echo "[STANDALONE] Peer libc found at ../libc. Building standard SDK..."; \
			$(MAKE) -C ../libc SDK_DIR=$(BOOTSTRAP_SDK) install; \
		else \
			echo "[STANDALONE] SDK and peer libc not found. Fetching libc from GitHub..."; \
			mkdir -p build; \
			if [ ! -d "build/libc_src" ]; then \
				git clone https://github.com/boredos/libc.git build/libc_src; \
			fi; \
			$(MAKE) -C build/libc_src SDK_DIR=$(BOOTSTRAP_SDK) install; \
		fi \
	fi
endif

obj/lua_onelua.o: src/boredos_onelua.c
	@mkdir -p obj
	$(CC) $(LUA_CFLAGS) -c $< -o $@

lua.elf: obj/lua_onelua.o
	$(LD) $(LDFLAGS) $(SDK_PATH)/lib/crt0.o $< -lc -o $@

install: all
	mkdir -p $(DESTDIR)/bin
	cp $(APPS) $(DESTDIR)/bin/

clean:
	rm -rf obj build $(APPS)
