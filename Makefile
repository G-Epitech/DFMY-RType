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
TESTS_ABRA_NAME 	= abra_tests
TESTS_ZYGARDE_NAME 	= zygrade_tests
TESTS_PORYGON_NAME 	= porygon_tests
BUILD_PATH 			= $(shell pwd)/build
SQL_PATH 			= $(shell pwd)/server/game.schema.sql

COVERAGE_IGNORE_TARGETS = 	tests \
							cmake-build-debug-coverage \

COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

TOOLCHAIN_FLAG = -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake

LINT_DIRS = client/src \
			libs/abra/src \
			libs/game/src \
			libs/zygarde/src \
			libs/porygon/src \
			libs/mew/src \
			server/src

LINT_FILES = $(shell find $(LINT_DIRS) -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.cc' -o -name '*.cxx' \))

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
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG) -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(BUILD_PATH)
			@cmake --build $(BUILD_PATH) --target $(SERVER_NAME)
.PHONY: $(SERVER_NAME)

$(CLIENT_NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG) -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(BUILD_PATH)
			@cmake --build $(BUILD_PATH) --target $(CLIENT_NAME)
.PHONY: $(CLIENT_NAME)

clean:
			@rm -rf $(BUILD_PATH)
.PHONY: clean

fclean:		clean
			@rm -f $(NAME)
			@rm -f $(TESTS_SERVER_NAME) $(TESTS_CLIENT_NAME) $(TESTS_ABRA_NAME) $(TESTS_ZYGARDE_NAME)
			@rm -f $(SERVER_NAME) $(CLIENT_NAME)
.PHONY: fclean

re:
			@$(MAKE) fclean
			@$(MAKE) all
.PHONY: re

generate_tests:
		@cmake -B $(BUILD_PATH) -DCOVERAGE=ON $(TOOLCHAIN_FLAG) -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(BUILD_PATH)

tests_run: generate_tests
	@cmake --build $(BUILD_PATH) --target $(TESTS_SERVER_NAME) $(TESTS_CLIENT_NAME) $(TESTS_ABRA_NAME) $(TESTS_ZYGARDE_NAME) $(TESTS_PORYGON_NAME)
	@$(BUILD_PATH)/$(TESTS_CLIENT_NAME) --gtest_brief=1
	@$(BUILD_PATH)/$(TESTS_SERVER_NAME) --gtest_brief=1
	@$(BUILD_PATH)/$(TESTS_ABRA_NAME) --gtest_brief=1
	@$(BUILD_PATH)/$(TESTS_ZYGARDE_NAME) --gtest_brief=1
	@$(BUILD_PATH)/$(TESTS_PORYGON_NAME) --gtest_brief=1
.PHONY: tests_run

tests_run_server:
		@cmake --build $(BUILD_PATH) --target $(TESTS_SERVER_NAME)
		@$(BUILD_PATH)/$(TESTS_SERVER_NAME) --gtest_brief=1
.PHONY: tests_run_server

tests_run_porygon:
		@cmake --build $(BUILD_PATH) --target $(TESTS_PORYGON_NAME)
		@$(BUILD_PATH)/$(TESTS_PORYGON_NAME) --gtest_brief=1
.PHONY: tests_run_porygon

tests_run_client:
		@cmake --build $(BUILD_PATH) --target $(TESTS_CLIENT_NAME)
		@$(BUILD_PATH)/$(TESTS_CLIENT_NAME) --gtest_brief=1
.PHONY: tests_run_client

tests_run_abra:
		@cmake --build $(BUILD_PATH) --target $(TESTS_ABRA_NAME)
		@$(BUILD_PATH)/$(TESTS_ABRA_NAME) --gtest_brief=1
.PHONY: tests_run_abra

tests_run_zygarde:
		@cmake --build $(BUILD_PATH) --target $(TESTS_ZYGARDE_NAME)
		@$(BUILD_PATH)/$(TESTS_ZYGARDE_NAME) --gtest_brief=1
.PHONY: tests_run_zygarde

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

setup-database:
			@(cat $(SQL_PATH) | mysql -u root -p) && echo "Database setup done."
.PHONY: setup-database

DEFAULT_GOAL := all
