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

TOOLCHAIN_FLAG = -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_PATH)/scripts/buildsystems/vcpkg.cmake

ifdef DEBUG
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
else
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release
endif

all:		$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(SERVER_NAME)

$(CLIENT_NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS) $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(CLIENT_NAME)

clean:
			@rm -rf $(BUILD_PATH)

fclean:		clean
			@rm -f $(NAME)
			@rm -f $(TESTS_SERVER_NAME) $(TESTS_CLIENT_NAME)
			@rm -f $(SERVER_NAME) $(CLIENT_NAME)

re:
			@$(MAKE) fclean
			@$(MAKE) all

tests_run: tests_run_server tests_run_client

tests_run_server:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(TESTS_SERVER_NAME)
			@./$(TESTS_SERVER_NAME) --gtest_brief=1

tests_run_client:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON $(TOOLCHAIN_FLAG)
			@cmake --build $(BUILD_PATH) --target $(TESTS_CLIENT_NAME)
			@./$(TESTS_CLIENT_NAME) --gtest_brief=1

coverage:
			@gcovr $(COVERAGE_IGNORE)

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch

.PHONY: all clean fclean re tests_run update coverage coverage-branch $(NAME)

DEFAULT_GOAL := all
