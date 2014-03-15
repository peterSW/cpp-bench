GMOCK_DIR := tps/gmock-1.7.0
GTEST_DIR = $(GMOCK_DIR)/gtest

GMOCK_MAIN_LIB := $(GMOCK_DIR)/make/gmock_main.a

$(GMOCK_MAIN_LIB) : $(GMOCK_DIR)
	$(MAKE) -C $(dir $@)

$(GMOCK_HEADERS) : $(GMOCK_DIR)

$(GMOCK_DIR) : $(GMOCK_DIR).zip
	@unzip $^ -d $(dir $@) > /dev/null
	@touch $@
	
$(GMOCK_DIR).zip : $(GMOCK_DIR).curl
	curl -K $^ > $@

define GMOCK_CLEAN_CMD
	$(RM) $(GMOCK_DIR).zip
	$(RM) -r $(GMOCK_DIR)
endef


CPPFLAGS_FOR_GMOCK_TESTS := -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include
CXXFLAGS_FOR_GMOCK_TESTS := -g -Wall -Wextra -pthread 
LDFLAGS_FOR_GMOCK_TESTS := -pthread


