.PHONY: clean All

All:
	@echo "----------Building project:[ CXX01_Final_Assignment - Debug ]----------"
	@$(MAKE) -f  "CXX01_Final_Assignment.mk"
clean:
	@echo "----------Cleaning project:[ CXX01_Final_Assignment - Debug ]----------"
	@$(MAKE) -f  "CXX01_Final_Assignment.mk" clean
