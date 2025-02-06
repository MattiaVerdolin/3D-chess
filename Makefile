MAKE = make

all: build_engine build_client build_test

build_engine: 
	$(MAKE) -C engine all

build_client: build_engine
	$(MAKE) -C client all

build_test: build_engine build_client
	$(MAKE) -C test run_tests

clean: clean_engine clean_client clean_test

clean_engine: 
	$(MAKE) -C engine clean

clean_client: 
	$(MAKE) -C client clean

clean_test:
	$(MAKE) -C test clean

.PHONY: clean_engine clean_client clean_test

