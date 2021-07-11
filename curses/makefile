DEBUG_CC_FLAGS = -I.. -c -g -w
RELEASE_CC_FLAGS = -I.. -c -O3 -w
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libBLcurses.a
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/libBLcurses.a
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/BLtwowin.o $(DEBUG_OBJECT_DIR)/BLgetline.o $(DEBUG_OBJECT_DIR)/BLsubwin.o \
	$(DEBUG_OBJECT_DIR)/BLmultiwin.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/BLtwowin.o $(RELEASE_OBJECT_DIR)/Blgetline.o $(RELEASE_OBJECT_DIR)/BLsubwin.o \
	$(RELEASE_OBJECT_DIR)/BLmultiwin.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_TARGET_DIR)
	$(AR) r $@ $^
	ranlib $@

$(DEBUG_OBJECT_DIR)/BLtwowin.o	:	BLtwowin.c BLtwowin.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLgetline.o	:	BLgetline.c BLgetline.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsubwin.o	:	BLsubwin.c BLsubwin.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLmultiwin.o	:	BLmultiwin.c BLmultiwin.h
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

$(RELEASE_OBJECT_DIR)/BLtwowin.o	:	BLtwowin.c BLtwowin.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLgetline.o	:	BLgetline.c BLgetline.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsubwin.o	:	BLsubwin.c BLsubwin.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLmultiwin.o	:	BLmultiwin.c BLmultiwin.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
