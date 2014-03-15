
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

include tps/gmock.mk
TEST_CATEGORY := ACCEPTANCE
include mk/canned_gmock_tests.mk
TEST_CATEGORY := UNIT
include mk/canned_gmock_tests.mk
#TEST_CATEGORY := UNIT
#include mk/canned_gmock_tests.mk

.PHONY : all
all : $(ACCEPTANCE_TEST_BIN) $(UNIT_TEST_BIN)

.PHONY : check
check : $(ACCEPTANCE_TEST_BIN) $(UNIT_TEST_BIN)
	$(ACCEPTANCE_TEST_BIN)
	$(UNIT_TEST_BIN)


include mk/rules.mk

.PHONY : clean cleanall
clean :
	$(ACCEPTANCE_CLEAN_CMD)

cleanall : clean
	$(GMOCK_CLEAN_CMD)

