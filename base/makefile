DEBUG_CC_FLAGS = -I.. -c -g -w
RELEASE_CC_FLAGS = -I.. -c -O3 -w
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libBLbase.a
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/libBLbase.a
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/BLts.o $(DEBUG_OBJECT_DIR)/BLthread.o \
	$(DEBUG_OBJECT_DIR)/BLprocess.o $(DEBUG_OBJECT_DIR)/BLfile.o $(DEBUG_OBJECT_DIR)/BLarray.o \
	$(DEBUG_OBJECT_DIR)/BLringbuf.o $(DEBUG_OBJECT_DIR)/BLser.o $(DEBUG_OBJECT_DIR)/BLfsm.o \
	$(DEBUG_OBJECT_DIR)/BLheapdebug.o $(DEBUG_OBJECT_DIR)/BLlogger.o \
	$(DEBUG_OBJECT_DIR)/BLbsearch.o $(DEBUG_OBJECT_DIR)/BLsystick.o \
	$(DEBUG_OBJECT_DIR)/BLdispatcher.o $(DEBUG_OBJECT_DIR)/BLsettings.o \
	$(DEBUG_OBJECT_DIR)/BLminififo.o $(DEBUG_OBJECT_DIR)/BLptrq.o \
	$(DEBUG_OBJECT_DIR)/BLtextutil.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/BLts.o $(RELEASE_OBJECT_DIR)/BLthread.o \
	$(RELEASE_OBJECT_DIR)/BLprocess.o $(RELEASE_OBJECT_DIR)/BLfile.o $(RELEASE_OBJECT_DIR)/BLarray.o \
	$(RELEASE_OBJECT_DIR)/BLringbuf.o $(RELEASE_OBJECT_DIR)/BLser.o $(RELEASE_OBJECT_DIR)/BLfsm.o \
	$(RELEASE_OBJECT_DIR)/BLheapdebug.o $(RELEASE_OBJECT_DIR)/BLlogger.o \
	$(RELEASE_OBJECT_DIR)/BLbsearch.o $(RELEASE_OBJJECT_DIR)/BLsystick.o \
	$(RELEASE_OBJECT_DIR)/BLdispatcher.o $(RELEASE_OBJJECT_DIR)/BLsettings.o \
	$(RELEASE_OBJECT_DIR)/BLminififo.o $(RELEASE_OBJJECT_DIR)/BLptrq.o \
	$(RELEASE_OBJECT_DIR)/BLtextutil.o

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

$(DEBUG_OBJECT_DIR)/BLringbuf.o	:	BLringbuf.c BLringbuf.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLser.o	:	BLser.c BLser.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLfsm.o	:	BLfsm.c BLfsm.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLheapdebug.o	:	BLheapdebug.c BLheapdebug.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLlogger.o	:	BLlogger.c BLlogger.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLbsearch.o	:	BLbsearch.c BLbsearch.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsystick.o	:	BLsystick.c BLsystick.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLdispatcher.o	:	BLdispatcher.c BLdispatcher.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsettings.o	:	BLsettings.c BLsettings.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLminififo.o	:	BLminififo.c BLminififo.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLptrq.o	:	BLptrq.c BLptrq.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLtextutil.o	:	BLtextutil.c BLtextutil.h
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

$(RELEASE_OBJECT_DIR)/BLringbuf.o	:	BLringbuf.c BLringbuf.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLser.o	:	BLser.c BLser.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLfsm.o	:	BLfsm.c BLfsm.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLheapdebug.o	:	BLheapdebug.c BLheapdebug.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLlogger.o	:	BLlogger.c BLlogger.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLbsearch.o	:	BLbsearch.c BLbsearch.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsystick.o	:	BLsystick.c BLsystick.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLdispatcher.o	:	BLdispatcher.c BLdispatcher.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsettings.o	:	BLsettings.c BLsettings.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLminififo.o	:	BLminififo.c BLminififo.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLptrq.o	:	BLptrq.c BLptrq.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLtextutil.o	:	BLtextutil.c BLtextutil.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
