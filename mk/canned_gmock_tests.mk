
SRC := $(TEST_CATEGORY)_SRC
OBJ := $(TEST_CATEGORY)_OBJ
BIN := $(TEST_CATEGORY)_TEST_BIN



TEST_category := $(shell echo $(TEST_CATEGORY) | tr A-Z a-z)

$(SRC) := $(shell find tests/$(TEST_category)/ -name *.cc)
$(SRC) := $(wildcard $($(SRC)))

$(OBJ) := $($(SRC):.cc=.o)
$(OBJ) := $(addprefix $(OBJ_DIR)/,$($(OBJ)))

$(BIN) := $(BUILD_DIR)/$(TEST_category)_tests

$($(BIN)) : | $(BUILD_DIR)
$($(BIN)) : LDFLAGS := $(LDFLAGS_FOR_GMOCK_TESTS)
$($(BIN)) : $($(OBJ)) $(GMOCK_MAIN_LIB)
	$(CXX) $^ $(LDFLAGS) -o $@


$($(OBJ)) : $($(SRC)) | $(GMOCK_DIR) $(dir $($(OBJ)))
$($(OBJ)) : CPPFLAGS := $(CPPFLAGS_FOR_GMOCK_TESTS) -I include
$($(OBJ)) : CXXFLAGS := $(CXXFLAGS_FOR_GMOCK_TESTS)

$(dir $($(OBJ))) :
	mkdir -p $@


CLEAN_TGT := clean_tests

