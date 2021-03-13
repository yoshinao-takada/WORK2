MKLROOT = /opt/intel/sw_dev_tools/mkl
MKL_INC = -DMKL_ILP64 -I$(MKLROOT)/include
MATH_WORK_DIR = \"../../WorkData/math/\"
DEBUG_CC_FLAGS = $(MKL_INC) -I.. -c -g -w -DMATH_WORK_DIR=$(MATH_WORK_DIR)
RELEASE_CC_FLAGS = $(MKL_INC) -I.. -c -O3 -w -DMATH_WORK_DIR=$(MATH_WORK_DIR)
DEBUG_TARGET_DIR = ../debug
RELEASE_TARGET_DIR = ../release
MKL_LIB_DIR = -L/opt/intel/sw_dev_tools/mkl/lib/intel64
MKL_LIBS = $(MKL_LIB_DIR) -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core
BL_DEBUG_LIBS = -L$(DEBUG_TARGET_DIR) -lBLbase -lBLmath
BL_RELEASE_LIBS = -L$(RELEASE_TARGET_DIR) -lBLbase -lBLmath
PLATFORM_LIBS = -lpthread -lm -ldl
DEBUG_OBJECT_DIR = o/debug
RELEASE_OBJECT_DIR = o/release
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/mathUT.exe
RELEASE_TARGET = $(RELEASE_TARGET_DIR)/mathUT.exe
DEBUG_OBJECTS = $(DEBUG_OBJECT_DIR)/ut_main.o $(DEBUG_OBJECT_DIR)/sa.o
RELEASE_OBJECTS = $(RELEASE_OBJECT_DIR)/ut_main.o $(RELEASE_OBJECT_DIR)/sa.o

#-------------------- debug -------------------------------
.PHONY	:	debug

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TARGET_DIR)/libBLbase.a $(DEBUG_TARGET_DIR)/libBLmath.a
	$(CC) -o $@ $^ $(BL_DEBUG_LIBS) $(MKL_LIBS) $(PLATFORM_LIBS)

$(DEBUG_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) CC=$(CC) debug

$(DEBUG_TARGET_DIR)/libBLmath.a	:
	cd ../math && $(MAKE) CC=$(CC) debug

$(DEBUG_OBJECT_DIR)/ut_main.o	:	ut_main.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<

$(DEBUG_OBJECT_DIR)/sa.o	:	sa.c
	mkdir -p $(DEBUG_OBJECT_DIR)
	$(CC) $(DEBUG_CC_FLAGS) -o $@ $<


.PHONY	:	clean_debug
clean_debug	:
	rm -rf $(DEBUG_OBJECT_DIR)
	rm -f $(DEBUG_TARGET)
	cd ../base && $(MAKE) $@
	cd ../math && $(MAKE) $@


#-------------------- release -------------------------------
.PHONY	:	release

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TARGET_DIR)/libBLbase.a $(RELEASE_OBJECT_DIR)/libBLmath.a
	mkdir -p $(RELEASE_TARGET_DIR)
	$(CC) -o $@ -L$(RELEASE_TARGET_DIR) $^ -lBLbase -lpthread

$(RELEASE_TARGET_DIR)/libBLbase.a	:
	cd ../base && $(MAKE) release

$(RELEASE_OBJECT_DIR)/ut_main.o	:	ut_main.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

$(RELEASE_OBJECT_DIR)/sa.o	:	sa.c
	mkdir -p $(RELEASE_OBJECT_DIR)
	$(CC) $(RELEASE_CC_FLAGS) -o $@ $<

.PHONY	:	clean_release
clean_release	:
	rm -rf $(RELEASE_OBJECT_DIR)
	rm -f $(RELEASE_TARGET)
	cd ../base && $(MAKE) $@
	cd ../math && $(MAKE) $@
