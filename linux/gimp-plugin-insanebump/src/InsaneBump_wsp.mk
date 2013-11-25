.PHONY: clean All

All:
	@echo ----------Building project:[ InsaneBump - Debug ]----------
	@"$(MAKE)" -f "InsaneBump.mk"
clean:
	@echo ----------Cleaning project:[ InsaneBump - Debug ]----------
	@"$(MAKE)" -f "InsaneBump.mk" clean
