##
## EPITECH PROJECT, 2024
## rtype
## File description:
## Makefile
##

NAME 			= rtype
TESTS_NAME 		= rtype_tests
BUILD_PATH 		= build
COVERAGE_IGNORE_TARGETS = 	tests \
							cmake-build-debug-coverage \

COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

CMAKE_FLAGS = -DCMAKE_TOOLCHAIN_FILE=/home/sdragos/vcpkg/scripts/buildsystems/vcpkg.cmake

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
			@rm -f $(TESTS_NAME)

re:
			@$(MAKE) fclean
			@$(MAKE) all

tests_run:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON
			@cmake --build $(BUILD_PATH) --target $(TESTS_NAME)
			@./$(TESTS_NAME) --gtest_brief=1

coverage:
			@gcovr $(COVERAGE_IGNORE)

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch

.PHONY: all clean fclean re tests_run update coverage coverage-branch $(NAME)
DEFAULT_GOAL := all