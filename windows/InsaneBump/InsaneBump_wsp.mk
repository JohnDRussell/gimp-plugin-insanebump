.PHONY: clean All

All:
	@echo ----------Building project:[ InsaneBump - Release ]----------
	@"$(MAKE)" -f "InsaneBump.mk" && "$(MAKE)" -f "InsaneBump.mk" PostBuild
clean:
	@echo ----------Cleaning project:[ InsaneBump - Release ]----------
	@"$(MAKE)" -f "InsaneBump.mk" clean
