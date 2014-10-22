SRC_DIR = $(PWD)
TESTS:=$(shell ls -d *Test/)
ROOT_TEST_DIR=./ROOTExamples/
LOG=JPet.log
all: compile_test 
	echo $(TESTS)
	cd $(ROOT_TEST_DIR); make;
compile_test:
	@($(foreach TEST, $(TESTS), cd $(SRC_DIR)/$(TEST);$(MAKE)||exit $$? ;))
run: all
	./run_tests.pl 
	cd $(ROOT_TEST_DIR); ./run_tests.sh
clean:
	@($(foreach TEST, $(TESTS), cd $(SRC_DIR)/$(TEST);$(MAKE) clean;))
	cd $(ROOT_TEST_DIR); $(MAKE) clean
	rm -f $(LOG)
