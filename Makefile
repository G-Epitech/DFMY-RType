##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

SERVER_NAME 		= r-type_server
CLIENT_NAME			= r-type_client
TESTS_SERVER_NAME 	= r-type_server_tests
TESTS_CLIENT_NAME 	= r-type_client_tests
BUILD_PATH 			= build

COVERAGE_IGNORE_TARGETS = 	tests \
							cmake-build-debug-coverage \

COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

TOOLCHAIN_FLAG = -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake

LINT_DIRS = client \
			common \
			server
LINT_FILES = $(shell find $(LINT_DIRS) -type f -regex '.*\.\(cpp\|hpp\|cc\|cxx\)')

ifdef DEBUG
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
else
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release
endif

all:
		@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG)
		@cmake --build $(BUILD_PATH)
.PHONY: all

$(SERVER_NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(SERVER_NAME)
.PHONY: $(SERVER_NAME)

$(CLIENT_NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(CLIENT_NAME)
.PHONY: $(CLIENT_NAME)

clean:
			@rm -rf $(BUILD_PATH)
.PHONY: clean

fclean:		clean
			@rm -f $(NAME)
			@rm -f $(TESTS_SERVER_NAME) $(TESTS_CLIENT_NAME)
			@rm -f $(SERVER_NAME) $(CLIENT_NAME)
.PHONY: fclean

re:
			@$(MAKE) fclean
			@$(MAKE) all
.PHONY: re

tests_run: tests_run_server tests_run_client
.PHONY: tests_run

tests_run_server:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(TESTS_SERVER_NAME)
			@./$(TESTS_SERVER_NAME) --gtest_brief=1
.PHONY: tests_run_server

tests_run_client:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(TESTS_CLIENT_NAME)
			@./$(TESTS_CLIENT_NAME) --gtest_brief=1
.PHONY: tests_run_client

coverage:
			@gcovr $(COVERAGE_IGNORE)
.PHONY: coverage

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch
.PHONY: coverage-branch

lint:
			@cpplint --recursive --quiet $(LINT_DIRS)
.PHONY: lint

format:
			@clang-format -i $(LINT_FILES)
.PHONY: format

format-check:
			@@clang-format --dry-run -i $(LINT_FILES)
.PHONY: format-check

DEFAULT_GOAL := all
