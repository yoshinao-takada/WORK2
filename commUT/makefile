DEBUG_CC_FLAGS = -I.. -c -g
RELEASE_CC_FLAGS = -I.. -c -O3
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/commUT.exe
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/commUT.exe
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/ut_main.o $(DEBUG_OBJECT_DIR)/crc.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/ut_main.o $(DEBUG_OBJECT_DIR)/crc.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TARGET_DIR)/libBLbase.a $(DEBUG_TARGET_DIR)/libBLcomm.a
	mkdir -p $(DEBUG_TARGET_DIR)
	$(CC) -o $@ -L$(DEBUG_TARGET_DIR) $^ -lBLbase -lBLcomm -lpthread

$(DEBUG_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) debug

$(DEBUG_TARGET_DIR)/libBLcomm.a	:
	cd ../comm && $(MAKE) debug

$(DEBUG_OBJECT_DIR)/ut_main.o	:	ut_main.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/crc.o	:	crc.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -f $(DEBUG_TARGET)
	cd ../base && $(MAKE) $@
	cd ../comm && $(MAKE) $@


#-------------------- release -------------------------------
.PHONY	:	release

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TARGET_DIR)/libBLbase.a $(RELEASE_TARGET_DIR)/libBLcomm.a
	mkdir -p $(RELEASE_TARGET_DIR)
	$(CC) -o $@ -L$(RELEASE_TARGET_DIR) $^ -lBLbase -lBLcomm -lpthread

$(RELEASE_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) release

$(RELEASE_TARGET_DIR)/libBLcomm.a	:
	cd ../comm && $(MAKE) release

$(RELEASE_OBJECT_DIR)/ut_main.o	:	ut_main.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/crc.o	:	crc.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
	cd ../base && $(MAKE) $@
	cd ../comm && $(MAKE) $@
