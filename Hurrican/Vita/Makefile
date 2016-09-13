PHONY := all package clean
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CC := arm-vita-eabi-gcc
CXX := arm-vita-eabi-g++
STRIP := arm-vita-eabi-strip

PROJECT_TITLE := Hurrican
PROJECT_TITLEID := FFFF00002

PROJECT := hurrican

SRC_DIR := ..
OBJ_DIR := obj

SRC_C := $(SRC_DIR)/Wrap/unrarlib.c
SRC_CPP := $(call wildcard, $(SRC_DIR)/*.cpp $(SRC_DIR)/Wrap/*.cpp $(SRC_DIR)/Vita/*.cpp)
SRC_GXP := $(call wildcard, $(SRC_DIR)/Vita/*.gxp)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_C:$(SRC_DIR)/%.c=%.o)) $(addprefix $(OBJ_DIR)/, $(SRC_CPP:$(SRC_DIR)/%.cpp=%.o))
GXP_HS := $(SRC_GXP:%.gxp=%.h)

CFLAGS := -I$(SRC_DIR)/inc -I$(SRC_DIR)/Wrap
CXXFLAGS := $(CFLAGS) -std=c++11

.SECONDARY: $(GXP_HS)

all: install

install: package
	ftp -v -u ftp://192.168.0.108:1337/ux0:/Homebrew/$(PROJECT).vpk $(PROJECT).vpk

package: $(PROJECT).vpk

$(PROJECT).vpk: eboot.bin param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
	--add sce_sys/icon0.png=sce_sys/icon0.png \
	--add sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
	--add sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
	--add sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	$(PROJECT).vpk

eboot.bin: $(PROJECT).velf
	vita-make-fself $(PROJECT).velf eboot.bin

param.sfo:
	vita-mksfoex -s TITLE_ID="$(PROJECT_TITLEID)" "$(PROJECT_TITLE)" param.sfo

$(PROJECT).velf: $(PROJECT).elf
	$(STRIP) -g $<
	vita-elf-create $< $@

$(PROJECT).elf: $(OBJS)
	$(CXX) -Wl,-q -o $@ $^ -lSceGxm_stub

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(GXP_HS)
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(GXP_HS)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

%.h : %.gxp
	xxd -i <$< >$@

clean:
	rm -f $(PROJECT).velf $(PROJECT).elf $(PROJECT).vpk param.sfo eboot.bin $(OBJS) $(GXP_HS)
