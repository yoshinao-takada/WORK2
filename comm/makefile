DEBUG_CC_FLAGS = -I.. -c -g
RELEASE_CC_FLAGS = -I.. -c -O3
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libBLcomm.a
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/libBLcomm.a
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/BLser.o $(DEBUG_OBJECT_DIR)/BLsio.o \
	$(DEBUG_OBJECT_DIR)/BLsiotty.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/BLser.o $(RELEASE_OBJECT_DIR)/BLsio.o \
	$(RELEASE_OBJECT_DIR)/BLsiotty.o

#--------------------- debug --------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_TARGET_DIR)
	$(AR) r $@ $^
	ranlib $@

$(DEBUG_OBJECT_DIR)/BLser.o	:	BLser.c BLser.h BLser_ID.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsio.o	:	BLsio.c BLsio.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsiotty.o	:	BLsiotty.c BLsiotty.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -f $(DEBUG_TARGET)


#-------------------- release -------------------------------
.PHONY	:	release

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS)
	mkdir -p $(RELEASE_TARGET_DIR)
	$(AR) r $@ $^
	ranlib $@

$(RELEASE_OBJECT_DIR)/BLser.o	:	BLser.c BLser.h BLser_ID.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsio.o	:	BLsio.c BLsio.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsiotty.o	:	BLsiotty.c BLsiotty.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
