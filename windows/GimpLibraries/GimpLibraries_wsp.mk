.PHONY: clean All

All:
	@echo ----------Building project:[ GimpLibraries - Debug ]----------
	@"$(MAKE)" -f "GimpLibraries.mk" PreBuild && "$(MAKE)" -f "GimpLibraries.mk"
clean:
	@echo ----------Cleaning project:[ GimpLibraries - Debug ]----------
	@"$(MAKE)" -f "GimpLibraries.mk" clean
