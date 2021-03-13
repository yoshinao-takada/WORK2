MKLROOT = /opt/intel/sw_dev_tools/mkl
MKL_INC = -DMKL_ILP64 -I$(MKLROOT)/include
DEBUG_CC_FLAGS = $(MKL_INC) -I.. -c -g -w
RELEASE_CC_FLAGS = $(MKL_INC) -I.. -c -O3 -w
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libBLmath.a
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/libBLmath.a
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/BLsa.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/BLsa.o

#--------------------- debug --------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_TARGET_DIR)
	$(AR) r $@ $^
	ranlib $@

$(DEBUG_OBJECT_DIR)/BLsa.o	:	BLsa.c BLsa.h
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

$(RELEASE_OBJECT_DIR)/BLsa.o	:	BLsa.c BLsa.h
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
