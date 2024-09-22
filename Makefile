##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

NAME 				= rtype
BINARIES			= r-type_client r-type_server
TESTS_NAME_SERVER 	= r-type_server_tests
TESTS_NAME_CLIENT 	= r-type_client_tests
BUILD_PATH 			= build

COVERAGE_IGNORE_TARGETS = 	tests \
							cmake-build-debug-coverage \

COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

CMAKE_FLAGS = -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_PATH)/scripts/buildsystems/vcpkg.cmake

ifdef DEBUG
	CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Debug
else
	CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Release
endif

all:		$(NAME)

$(NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS)
			@cmake --build $(BUILD_PATH)

clean:
			@rm -rf $(BUILD_PATH)

fclean:		clean
			@rm -f $(NAME)
			@rm -f $(TESTS_NAME_SERVER) $(TESTS_NAME_CLIENT)
			@rm -f $(BINARIES)

re:
			@$(MAKE) fclean
			@$(MAKE) all

tests_run: tests_run_server tests_run_client

tests_run_server:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON
			@cmake --build $(BUILD_PATH) --target $(TESTS_NAME_SERVER)
			@./$(TESTS_NAME_SERVER) --gtest_brief=1

tests_run_client:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON
			@cmake --build $(BUILD_PATH) --target $(TESTS_NAME_CLIENT)
			@./$(TESTS_NAME_CLIENT) --gtest_brief=1

coverage:
			@gcovr $(COVERAGE_IGNORE)

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch

.PHONY: all clean fclean re tests_run update coverage coverage-branch $(NAME)

DEFAULT_GOAL := all
