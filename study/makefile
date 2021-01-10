DEF_TEST_DATA = -DTEST_DATA=\"../TestData/\"
DEF_WORK_DATA = -DWORK_DATA=\"../../WorkData/\"
DEBUG_CC_FLAGS = -I/usr/local/include/opencv4 -I.. -c -g $(DEF_TEST_DATA) $(DEF_WORK_DATA)
RELEASE_CC_FLAGS = -I/usr/local/include/opencv4 -I.. -c -O3 $(DEF_TEST_DATA) $(DEF_WORK_DATA)
LIBS = -L/usr/local/lib -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lstdc++ -lpthread
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release

DEBUG_TARGET = $(DEBUG_TARGET_DIR)/study.exe
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/study.exe
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/study_main.o \
	$(DEBUG_OBJECT_DIR)/BLrandimg.o $(DEBUG_OBJECT_DIR)/BLmargincopy2D.o \
	$(DEBUG_OBJECT_DIR)/BLfilter2D.o \
	$(DEBUG_OBJECT_DIR)/UTmargincopy2D.o $(DEBUG_OBJECT_DIR)/BLsat.o \
	$(DEBUG_OBJECT_DIR)/UTsat.o $(DEBUG_OBJECT_DIR)/UTcommon.o \
	$(DEBUG_OBJECT_DIR)/UTfilter2D.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/study_main.o \
	$(RELEASE_OBJECT_DIR)/BLrandimg.o $(RELEASE_OBJECT_DIR)/BLmargincopy2D.o \
	$(RELEASE_OBJECT_DIR)/BLfilter2D.o \
	$(RELEASE_OBJECT_DIR)/UTmargincopy2D.o $(RELEASE_OBJECT_DIR)/BLsat.o \
	$(RELEASE_OBJECT_DIR)/UTsat.o $(RELEASE_OBJECT_DIR)/UTcommon.o \
	$(RELEASE_OBJECT_DIR)/UTfilter2D.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_TARGET_DIR)
	$(CC) -o $@ $^ -L$(DEBUG_TARGET_DIR) -lBLbase $(LIBS)

$(DEBUG_OBJECT_DIR)/study_main.o	:	study_main.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLrandimg.o	:	BLrandimg.c BLrandimg.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLmargincopy2D.o	:	BLmargincopy2D.c BLmargincopy2D.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLsat.o	:	BLsat.c BLsat.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/BLfilter2D.o	:	BLfilter2D.c BLfilter2D.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/UTmargincopy2D.o	:	UTmargincopy2D.c UTmargincopy2D.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/UTsat.o	:	UTsat.c UTsat.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/UTcommon.o	:	UTcommon.cpp UTcommon.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/UTfilter2D.o	:	UTfilter2D.c UTfilter2D.h
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -r $(DEBUG_TARGET)


#-------------------- release -------------------------------
.PHONY	:	release

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS)
	mkdir -p $(RELEASE_TARGET_DIR)
	$(CC) -o $@ $^ -L$(RELEASE_TARGET_DIR) -lBLbase $(LIBS)

$(RELEASE_OBJECT_DIR)/study_main.o	:	study_main.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLrandimg.o	:	BLrandimg.c BLrandimg.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLmargincopy2D.o	:	BLmargincopy2D.c BLmargincopy2D.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLsat.o	:	BLsat.c BLsat.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/BLfilter2D.o	:	BLfilter2D.c BLfilter2D.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/UTmargincopy2D.o	:	UTmargincopy2D.c UTmargincopy2D.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/UTsat.o	:	UTsat.c UTsat.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/UTcommon.o	:	UTcommon.cpp UTcommon.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/UTfilter2D.o	:	UTfilter2D.c UTfilter2D.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)