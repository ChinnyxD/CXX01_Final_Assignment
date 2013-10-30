.PHONY: clean All

All:
	@echo "----------Building project:[ CXX_TEST - Debug ]----------"
	@cd "CXX_TEST" && $(MAKE) -f  "CXX_TEST.mk"
clean:
	@echo "----------Cleaning project:[ CXX_TEST - Debug ]----------"
	@cd "CXX_TEST" && $(MAKE) -f  "CXX_TEST.mk" clean
