$(OBJ_DIR)/%.o : %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) : $(BUILD_DIR)
	mkdir $@
$(BUILD_DIR) :
	mkdir $@
	
.PHONY : clean_tests
clean_tests :
	$(RM) -r $(BUILD_DIR)/tests
