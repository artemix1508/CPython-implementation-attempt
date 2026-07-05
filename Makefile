# CPython 3.14 port for BoredOS
# Based on Lua standalone Makefile by Christiaan (chris@boreddev.nl)

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

DESTDIR  ?= $(abspath build/dist)
CPYTHON  = src/cpython-3.14.3

PY_CFLAGS = \
    -include src/sysinclude/sys/stat.h \
    -std=gnu11 \
    -include src/sysinclude/fcntl.h \
    -include src/sysinclude/locale.h \
    -include src/sysinclude/time.h \
    -DDOUBLE_IS_LITTLE_ENDIAN_IEEE754 \
    -include src/sysinclude/inttypes.h \
    -include src/sysinclude/dirent.h \
    -include src/sysinclude/math.h \
    -ffreestanding \
    -O2 \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fno-pie \
    -m64 \
    -Dfileno=__boredos_fileno \
    -march=x86-64 \
    -mno-red-zone \
    -isystem src/sysinclude \
    -I src/sysinclude \
    -I$(CPYTHON) \
    -I$(CPYTHON)/Include \
    -I$(CPYTHON)/Include/internal \
    -I$(SDK_PATH)/include \
    -DPy_BUILD_CORE \
    -DPy_NO_ENABLE_SHARED \
    -DWITHOUT_COMPLEX \
    -Wno-conversion \
    -Wno-sign-conversion \
    -Wno-unused-parameter \
    -Wno-missing-declarations \
    -Wno-shadow \
    -Wno-undef \
    -Wno-implicit-fallthrough \
    -Wno-type-limits \
    -Wno-missing-prototypes \
    -Wno-pedantic \
    -Wno-error

LDFLAGS = \
    -m elf_x86_64 \
    -nostdlib \
    -static \
    -no-pie \
    -Ttext=0x40000000 \
    --no-dynamic-linker \
    -z text \
    -z max-page-size=0x1000 \
    -e _start \
    -L$(SDK_PATH)/lib

# Source files
PYTHON_SRCS := $(filter-out \
    $(CPYTHON)/Python/bytecodes.c \
    $(CPYTHON)/Python/optimizer_bytecodes.c \
    $(CPYTHON)/Python/dynload_hpux.c \
    $(CPYTHON)/Python/dynload_aix.c \
    $(CPYTHON)/Python/dynload_dl.c \
    $(CPYTHON)/Python/dynload_shlib.c \
    $(CPYTHON)/Python/dynload_win.c \
    $(CPYTHON)/Python/frozen.c \
    $(CPYTHON)/Python/frozenmain.c \
    $(CPYTHON)/Python/emscripten_signal.c \
    $(CPYTHON)/Python/emscripten_trampoline.c \
    $(CPYTHON)/Python/emscripten_trampoline_inner.c \
    $(CPYTHON)/Python/emscripten_syscalls.c \
    $(CPYTHON)/Python/wasm_assets.c \
    $(CPYTHON)/Python/thread_nt.c \
    $(CPYTHON)/Python/thread_wasi.c \
    $(CPYTHON)/Python/parking_lot.c \
    , $(wildcard $(CPYTHON)/Python/*.c))
OBJECTS_SRCS := $(wildcard $(CPYTHON)/Objects/*.c)
PARSER_SRCS  := $(wildcard $(CPYTHON)/Parser/*.c)
MODULES_SRCS := $(CPYTHON)/Modules/main.c \
                $(CPYTHON)/Modules/getbuildinfo.c \
                $(CPYTHON)/Modules/_io/_iomodule.c \
                $(CPYTHON)/Modules/_io/bufferedio.c \
                $(CPYTHON)/Modules/_io/bytesio.c \
                $(CPYTHON)/Modules/_io/fileio.c \
                $(CPYTHON)/Modules/_io/iobase.c \
                $(CPYTHON)/Modules/_io/stringio.c \
                $(CPYTHON)/Modules/_io/textio.c \
                $(CPYTHON)/Modules/posixmodule.c \
                $(CPYTHON)/Modules/errnomodule.c \
                $(CPYTHON)/Modules/timemodule.c \
                $(CPYTHON)/Modules/mathmodule.c \
                $(CPYTHON)/Modules/_weakref.c \
                $(CPYTHON)/Modules/_functoolsmodule.c \
                $(CPYTHON)/Modules/_collectionsmodule.c \
                $(CPYTHON)/Modules/itertoolsmodule.c \
                $(CPYTHON)/Modules/_sre/sre.c \
                $(CPYTHON)/Modules/_codecsmodule.c \
                $(CPYTHON)/Modules/_tracemalloc.c \
                $(CPYTHON)/Modules/gcmodule.c \
                $(CPYTHON)/Modules/symtablemodule.c \
                $(CPYTHON)/Modules/atexitmodule.c

EXTRA_SRCS := src/boredos_mathstubs.c
ALL_SRCS := $(PYTHON_SRCS) $(OBJECTS_SRCS) $(PARSER_SRCS) $(MODULES_SRCS) $(EXTRA_SRCS)

obj/boredos_mathstubs.o: src/boredos_mathstubs.c
	@mkdir -p obj
	$(CC) $(PY_CFLAGS) -c $< -o $@

# Generate object file paths
PYOBJS := $(patsubst $(CPYTHON)/%.c, obj/%.o, $(ALL_SRCS)) obj/boredos_mathstubs.o

APPS = python.elf

all: bootstrap-sdk $(APPS)

.PHONY: bootstrap-sdk
bootstrap-sdk:
ifdef BOOTSTRAP_SDK
	@if [ ! -f "$(BOOTSTRAP_SDK)/lib/libc.a" ]; then \
		if [ -d "../libc" ]; then \
			echo "[STANDALONE] Peer libc found at ../libc. Building standard SDK..."; \
			$(MAKE) -C ../libc SDK_DIR=$(BOOTSTRAP_SDK) install; \
        rm -f $(SDK_PATH)/include/sys/stat.h $(SDK_PATH)/include/stdio.h $(SDK_PATH)/include/locale.h; \
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

obj/%.o: $(CPYTHON)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(PY_CFLAGS) -c $< -o $@

python.elf: $(PYOBJS)
	$(LD) $(LDFLAGS) $(SDK_PATH)/lib/crt0.o $^ -lc -o $@

install: all
	mkdir -p $(DESTDIR)/bin
	cp $(APPS) $(DESTDIR)/bin/

.PHONY: bup
bup: all
	rm -rf build/package
	mkdir -p build/package/bin
	cp python.elf build/package/bin/
	@echo 'name = "python"' > build/package/MANIFEST.toml
	@echo 'version = "3.14.3"' >> build/package/MANIFEST.toml
	@echo '[install]' >> build/package/MANIFEST.toml
	@echo 'bin = "/bin"' >> build/package/MANIFEST.toml
	mkdir -p build
	tar -cf build/python.tar -C build/package MANIFEST.toml bin
	lz4 -f build/python.tar build/python.bup
	rm -f build/python.tar
	rm -rf build/package

clean:
	rm -rf obj build $(APPS)