all: $(deps)
	cd bin && $(MAKE) $(MAKEFLAGS) $@

install: $(deps)
	cd bin && $(MAKE) $(MAKEFLAGS) $@

uninstall: $(deps)
	cd bin && $(MAKE) $(MAKEFLAGS) $@

