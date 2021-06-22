BASE_WORK_DIR = -DBASE_WORK_DIR=\"../../WorkData/base/\"
DEBUG_CC_FLAGS = -I.. -c -g -w $(BASE_WORK_DIR)
RELEASE_CC_FLAGS = -I.. -c -O3 -w $(BASE_WORK_DIR)
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/baseUT.exe
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/baseUT.exe
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/ut_main.o $(DEBUG_OBJECT_DIR)/ts.o $(DEBUG_OBJECT_DIR)/thread.o \
	$(DEBUG_OBJECT_DIR)/UTarray.o $(DEBUG_OBJECT_DIR)/ringbuf.o $(DEBUG_OBJECT_DIR)/ser.o \
	$(DEBUG_OBJECT_DIR)/ringbufex.o $(DEBUG_OBJECT_DIR)/heapdebug.o $(DEBUG_OBJECT_DIR)/bsearch.o \
	$(DEBUG_OBJECT_DIR)/systick.o $(DEBUG_OBJECT_DIR)/dispatcher.o $(DEBUG_OBJECT_DIR)/settings.o \
	$(DEBUG_OBJECT_DIR)/fifo.o $(DEBUG_OBJECT_DIR)/ptrq.o $(DEBUG_OBJECT_DIR)/ptrq2.o \
	$(DEBUG_OBJECT_DIR)/textutil.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/ut_main.o $(RELEASE_OBJECT_DIR)/ts.o $(RELEASE_OBJECT_DIR)/thread.o \
	$(RELEASE_OBJECT_DIR)/UTarray.o $(RELEASE_OBJECT_DIR)/ringbuf.o $(RELEASE_OBJECT_DIR)/ser.o \
	$(RELEASE_OBJECT_DIR)/ringbufex.o $(RELEASE_OBJECT_DIR)/heapdebug.o $(RELEASE_OBJECT_DIR)/bsearch.o \
	$(RELEASE_OBJECT_DIR)/systick.o $(RELEASE_OBJECT_DIR)/dispatcher.o $(RELEASE_OBJECT_DIR)/settings.o \
	$(RELEASE_OBJECT_DIR)/fifo.o $(RELEASE_OBJECT_DIR)/ptrq.o $(RELEASE_OBJECT_DIR)/ptrq2.o \
	$(RELEASE_OBJECT_DIR)/textutil.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TARGET_DIR)/libBLbase.a
	mkdir -p $(DEBUG_TARGET_DIR)
	$(CC) -o $@ -L$(DEBUG_TARGET_DIR) $^ -lBLbase -lpthread

$(DEBUG_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) debug

$(DEBUG_OBJECT_DIR)/ut_main.o	:	ut_main.c ts.h thread.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ts.o	:	ts.c ts.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/thread.o	:	thread.c thread.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/UTarray.o	:	UTarray.c UTarray.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ringbuf.o	:	ringbuf.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ser.o	:	ser.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ringbufex.o	:	ringbufex.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/heapdebug.o	:	heapdebug.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/bsearch.o	:	bsearch.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/systick.o	:	systick.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/dispatcher.o	:	dispatcher.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/settings.o	:	settings.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/fifo.o	:	fifo.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ptrq.o	:	ptrq.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/ptrq2.o	:	ptrq2.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/textutil.o	:	textutil.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -f $(DEBUG_TARGET)
	cd ../base && $(MAKE) $@


#-------------------- release -------------------------------
.PHONY	:	release

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TARGET_DIR)/libBLbase.a
	mkdir -p $(RELEASE_TARGET_DIR)
	$(CC) -o $@ -L$(RELEASE_TARGET_DIR) $^ -lBLbase -lpthread

$(RELEASE_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) release

$(RELEASE_OBJECT_DIR)/ut_main.o	:	ut_main.c ts.h thread.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ts.o	:	ts.c ts.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/thread.o	:	thread.c thread.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/UTarray.o	:	UTarray.c UTarray.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ringbuf.o	:	ringbuf.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ser.o	:	ser.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ringbufex.o	:	ringbufex.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/heapdebug.o	:	heapdebug.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/bsearch.o	:	bsearch.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/systick.o	:	systick.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/dispatcher.o	:	dispatcher.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/settings.o	:	settings.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/fifo.o	:	fifo.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ptrq.o	:	ptrq.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/ptrq2.o	:	ptrq2.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/textutil.o	:	textutil.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
	cd ../base && $(MAKE) $@
