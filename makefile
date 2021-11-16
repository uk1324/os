BUILD_DIR := ./build
SRC_DIR := ./src

OUT_BIN := $(BUILD_DIR)/os.out

QEMU := qemu-system-i386.exe

AS := i686-elf-as
G++ := i686-elf-g++
LD := i686-elf-ld

G++_INCLUDE_DIRS := $(SRC_DIR)

AS_FLAGS := -msyntax=intel -mnaked-reg

# "-c" - Only compile don't link
G++_FLAGS := -std=c++2a -ffreestanding -O2 -fno-exceptions -fno-rtti -c \
	-masm=intel \
	-DKERNEL_DEBUG \
	-I $(G++_INCLUDE_DIRS) \
	-Wall
# -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
# -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
# -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
# -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
# -Wswitch-default -Wundef -Werror -Wno-unused # -Wsign-conversion
#-Wmissing-declarations

CPP_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")
ASM_FILES := $(shell find $(SRC_DIR) -type f -name "*.s")

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES)) \
			 $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(ASM_FILES))

.PHONY: all
all: $(OUT_BIN)

$(OUT_BIN): $(OBJ_FILES)
	ls $(BUILD_DIR)
	$(LD) -T link.ld -o $(OUT_BIN) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(G++) $(G++_FLAGS) -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) -o $@ $<

.PHONY: run
run:
	$(QEMU) -serial stdio -kernel $(OUT_BIN)

.PHONY: clean
clean:
	rm -r build