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

DATA_DIR := ../data
DATA_FILES := $(wildcard $(DATA_DIR)/*.bmp $(DATA_DIR)/*.png $(DATA_DIR)/*.wav $(DATA_DIR)/boss_*.it)

SRC_C := $(SRC_DIR)/Wrap/unrarlib.c
SRC_CPP := $(call wildcard, $(SRC_DIR)/Vita/*.cpp $(SRC_DIR)/Wrap/*.cpp $(SRC_DIR)/*.cpp)
SRC_GXP := $(call wildcard, $(SRC_DIR)/Vita/*.gxp)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_C:$(SRC_DIR)/%.c=%.o)) $(addprefix $(OBJ_DIR)/, $(SRC_CPP:$(SRC_DIR)/%.cpp=%.o))
GXP_HS := $(SRC_GXP:%.gxp=%.h)

CFLAGS := -I$(SRC_DIR)/inc -I$(SRC_DIR)/Wrap
CXXFLAGS := $(CFLAGS) -std=c++11

VITA2D_DIR := vita2d/libvita2d
VITA2D_LIB := $(VITA2D_DIR)/libvita2d.a

.SECONDARY: $(GXP_HS)

all: update

VITA_IP_ADDRESS := 192.168.43.176

install: package
	curl -v -T $(PROJECT).vpk ftp://$(VITA_IP_ADDRESS):1337/ux0:/

update: eboot.bin
	curl -v -T eboot.bin ftp://$(VITA_IP_ADDRESS):1337/ux0:/app/$(PROJECT_TITLEID)/

package: $(PROJECT).vpk

$(PROJECT).vpk: eboot.bin param.sfo $(DATA_FILES)
	vita-pack-vpk -s param.sfo -b eboot.bin \
	--add sce_sys/icon0.png=sce_sys/icon0.png \
	--add sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
	--add sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
	--add sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	--add $(DATA_DIR)/Aztech.it=data/Aztech.it \
	--add $(DATA_DIR)/Blue.it=data/Blue.it \
	--add $(DATA_DIR)/Cracktro.it=data/Cracktro.it \
	--add $(DATA_DIR)/JungleBeats.it=data/JungleBeats.it \
	--add "$(DATA_DIR)/Machine Monotony.it"="data/Machine Monotony.it" \
	--add $(DATA_DIR)/Punisher.it=data/Punisher.it \
	--add $(DATA_DIR)/Tower.it=data/Tower.it \
	--add $(DATA_DIR)/cave.it=data/cave.it \
	--add $(DATA_DIR)/credits.it=data/credits.it \
	--add $(DATA_DIR)/eis.it=data/eis.it \
	--add $(DATA_DIR)/elevator.it=data/elevator.it \
	--add $(DATA_DIR)/factory.it=data/factory.it \
	--add $(DATA_DIR)/flugsack.it=data/flugsack.it \
	--add $(DATA_DIR)/gameover.it=data/gameover.it \
	--add $(DATA_DIR)/highscore.it=data/highscore.it \
	--add $(DATA_DIR)/intro.it=data/intro.it \
	--add $(DATA_DIR)/loststation.it=data/loststation.it \
	--add $(DATA_DIR)/menu.it=data/menu.it \
	--add $(DATA_DIR)/outtro.it=data/outtro.it \
	--add $(DATA_DIR)/stageclear.it=data/stageclear.it \
	$(foreach file,$(DATA_FILES),--add $(file)=$(subst $(DATA_DIR),data,$(file))) \
	$(PROJECT).vpk

eboot.bin: $(PROJECT).velf
	vita-make-fself -s $(PROJECT).velf eboot.bin

param.sfo:
	vita-mksfoex -s TITLE_ID="$(PROJECT_TITLEID)" "$(PROJECT_TITLE)" param.sfo

$(PROJECT).velf: $(PROJECT).elf
	$(STRIP) -g $<
	vita-elf-create $< $@

$(PROJECT).elf: $(OBJS) $(VITA2D_LIB)
	$(CXX) -Wl,-q -o $@ $(OBJS) -lSceGxm_stub

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(GXP_HS) $(VITA2D_LIB)
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(GXP_HS) $(VITA2D_LIB)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

%.h : %.gxp
	xxd -i <$< >$@

$(VITA2D_LIB): installportlibs
	cd $(VITA2D_DIR) && make

installportlibs:
	cd portlibs && make

clean:
	rm -f $(PROJECT).velf $(PROJECT).elf $(PROJECT).vpk param.sfo eboot.bin $(OBJS) $(GXP_HS)
	cd vita2d/libvita2d && make clean
	cd portlibs && make clean
