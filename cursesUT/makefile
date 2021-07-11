DEBUG_CC_FLAGS = -I.. -c -g -D_DEBUG -w $(BASE_WORK_DIR)
RELEASE_CC_FLAGS = -I.. -c -O3 -DNDEBUG -w $(BASE_WORK_DIR)
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/cursesUT.exe
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/cursesUT.exe
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/curses_main.o \
	$(DEBUG_OBJECT_DIR)/mwin.o $(DEBUG_OBJECT_DIR)/vgetl.o $(DEBUG_OBJECT_DIR)/logger.o \
	$(DEBUG_OBJECT_DIR)/multiwin.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/curses_main.o \
	$(RELEASE_OBJECT_DIR)/mwin.o $(RELEASE_OBJECT_DIR)/vgetl.o $(RELEASE_OBJECT_DIR)/logger.o \
	$(RELEASE_OBJECT_DIR)/multiwin.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TARGET_DIR)/libBLcurses.a
	mkdir -p $(DEBUG_TARGET_DIR)
	$(CC) -o $@ -L$(DEBUG_TARGET_DIR) $^ -lBLcurses -lBLbase -lpthread -lncurses

$(DEBUG_TARGET_DIR)/libBLcurses.a	:
	cd ../curses && $(MAKE) debug

$(DEBUG_OBJECT_DIR)/curses_main.o	:	curses_main.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/mwin.o	:	mwin.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/vgetl.o	:	vgetl.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/logger.o	:	 logger.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/multiwin.o	:	 multiwin.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -f $(DEBUG_TARGET)
	cd ../curses && $(MAKE) $@

