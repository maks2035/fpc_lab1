# CMakeList.txt: проект CMake для fpc_lab1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (fpc_lab1 "fpc_lab1.cpp" "fpc_lab1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET fpc_lab1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
