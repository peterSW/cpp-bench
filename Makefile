
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

ACCEPTANCE_SRC := $(wildcard tests/acceptance/*.cc)
ACCEPTANCE_OBJ := $(addprefix $(OBJ_DIR)/,$(ACCEPTANCE_SRC:.cc=.o))

ACCEPTANCE_TEST_BIN := $(BUILD_DIR)/acceptance_tests

.PHONY : all
all : $(ACCEPTANCE_TEST_BIN)

.PHONY : check
check : $(ACCEPTANCE_TEST_BIN)
	$(ACCEPTANCE_TEST_BIN)

include tps/gmock.mk


$(ACCEPTANCE_TEST_BIN) : | $(BUILD_DIR)
$(ACCEPTANCE_TEST_BIN) : LDFLAGS := $(LDFLAGS_FOR_GMOCK_TESTS)
$(ACCEPTANCE_TEST_BIN) : $(ACCEPTANCE_OBJ) $(GMOCK_MAIN_LIB)
	$(CXX) $^ $(LDFLAGS) -o $@

$(ACCEPTANCE_OBJ) : $(ACCEPTANCE_SRC) | $(GMOCK_DIR) $(dir $(ACCEPTANCE_OBJ))
$(ACCEPTANCE_OBJ) : CPPFLAGS := $(CPPFLAGS_FOR_GMOCK_TESTS)
$(ACCEPTANCE_OBJ) : CXXFLAGS := $(CXXFLAGS_FOR_GMOCK_TESTS)

$(OBJ_DIR)/%.o : %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(dir $(ACCEPTANCE_OBJ)) :
	mkdir -p $@
$(OBJ_DIR) : $(BUILD_DIR)
	mkdir $@
$(BUILD_DIR) :
	mkdir $@

.PHONY : clean cleanall
clean :
	$(RM) $(ACCEPTANCE_OBJ) $(ACCEPTANCE_TEST_BIN)

cleanall : clean
	$(GMOCK_CLEAN_CMD)

