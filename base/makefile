DEBUG_CC_FLAGS = -I.. -c -g
RELEASE_CC_FLAGS = -I.. -c -O3
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libBLbase.a
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/libBLbase.a
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/BLts.o $(DEBUG_OBJECT_DIR)/BLthread.o \
	$(DEBUG_OBJECT_DIR)/BLprocess.o $(DEBUG_OBJECT_DIR)/BLfile.o $(DEBUG_OBJECT_DIR)/BLarray.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/BLts.o $(RELEASE_OBJECT_DIR)/BLthread.o \
	$(RELEASE_OBJECT_DIR)/BLprocess.o $(RELEASE_OBJECT_DIR)/BLfile.o $(RELEASE_OBJECT_DIR)/BLarray.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_TARGET_DIR)
	$(AR) r $@ $^
	ranlib $@

$(DEBUG_OBJECT_DIR)/BLts.o	:	BLts.c BLts.h BLbase.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLthread.o	:	BLthread.c BLthread.h BLbase.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLprocess.o	:	BLprocess.c BLprocess.h BLbase.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLfile.o	:	BLfile.c BLfile.h BLbase.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLarray.o	:	BLarray.c BLarray.h BLbase.h
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

$(RELEASE_OBJECT_DIR)/BLts.o	:	BLts.c BLts.h BLbase.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLthread.o	:	BLthread.c BLthread.h BLbase.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLprocess.o	:	BLprocess.c BLprocess.h BLbase.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLfile.o	:	BLfile.c BLfile.h BLbase.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLarray.o	:	BLarray.c BLarray.h BLbase.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)