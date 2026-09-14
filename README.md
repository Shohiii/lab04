# Лабораторная работа №3

Условие лабораторной работы: https://github.com/tp-labs/lab03

## Цель работы

Получить практические навыки работы с системой сборки CMake: создание статических библиотек, настройка зависимостей между ними и сборка приложений.

Репозиторий с выполненной лабораторной работой:

https://github.com/Shohiii/lab03

## Исходная структура проекта

Была сохранена исходная структура проекта:

```text
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── formatter_ex_lib
│   ├── CMakeLists.txt
│   ├── formatter_ex.cpp
│   └── formatter_ex.h
├── formatter_lib
│   ├── CMakeLists.txt
│   ├── formatter.cpp
│   └── formatter.h
├── hello_world_application
│   ├── CMakeLists.txt
│   └── hello_world.cpp
├── preview.png
├── solver_application
│   ├── CMakeLists.txt
│   └── equation.cpp
└── solver_lib
    ├── CMakeLists.txt
    ├── solver.cpp
    └── solver.h
```

Исходные каталоги `formatter_lib`, `formatter_ex_lib`, `hello_world_application`, `solver_lib` и `solver_application` не переносились и не переименовывались.

## 1. Библиотека formatter

В каталог `formatter_lib` был добавлен файл `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.5)

project(formatter)

add_library(formatter STATIC
    formatter.cpp
)

target_include_directories(formatter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Создаётся статическая библиотека `formatter`.

## 2. Библиотека formatter_ex

В каталог `formatter_ex_lib` был добавлен файл `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.5)

project(formatter_ex)

add_library(formatter_ex STATIC
    formatter_ex.cpp
)

target_include_directories(formatter_ex PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(formatter_ex
    formatter
)
```

Библиотека `formatter_ex` использует библиотеку `formatter`.

## 3. Библиотека solver_lib

В каталог `solver_lib` был добавлен файл `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.5)

project(solver_lib)

add_library(solver_lib STATIC
    solver.cpp
)

target_include_directories(solver_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Создаётся статическая библиотека `solver_lib`.

При сборке проекта современным компилятором GCC потребовалось подключить заголовочный файл `<cmath>` и использовать `std::sqrt` вместо `std::sqrtf`.

Фрагмент `solver.cpp`:

```cpp
#include <cmath>
#include "solver.h"

#include <stdexcept>
```

Вычисление корней:

```cpp
x1 = (-b - std::sqrt(d)) / (2 * a);
x2 = (-b + std::sqrt(d)) / (2 * a);
```

## 4. Приложение hello_world

В каталог `hello_world_application` был добавлен `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.5)

project(hello_world)

add_executable(hello_world
    hello_world.cpp
)

target_link_libraries(hello_world
    formatter_ex
)
```

Приложение `hello_world` связывается с библиотекой `formatter_ex`.

## 5. Приложение solver

В каталог `solver_application` был добавлен `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.5)

project(solver)

add_executable(solver
    equation.cpp
)

target_link_libraries(solver
    formatter_ex
    solver_lib
)
```

Приложение `solver` использует библиотеки `formatter_ex` и `solver_lib`.

## 6. Корневой CMakeLists.txt

Корневой файл `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.5)

project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)
```

Таким образом, один корневой файл CMake подключает все библиотеки и приложения проекта.

## 7. Конфигурация проекта

Для сборки была создана отдельная директория `_build`.

Команда:

```bash
cmake -S . -B _build
```

Основная часть вывода:

```text
-- The C compiler identification is GNU 15.2.0
-- The CXX compiler identification is GNU 15.2.0
-- Detecting C compiler ABI info - done
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/nikita/lab03/_build
```

## 8. Сборка проекта

Команда:

```bash
cmake --build _build
```

Вывод:

```text
[ 10%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 20%] Linking CXX static library libformatter.a
[ 20%] Built target formatter
[ 30%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 40%] Linking CXX static library libformatter_ex.a
[ 40%] Built target formatter_ex
[ 50%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 60%] Linking CXX static library libsolver_lib.a
[ 60%] Built target solver_lib
[ 70%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 80%] Linking CXX executable hello_world
[ 80%] Built target hello_world
[ 90%] Building CXX object solver_application/CMakeFiles/solver.dir/equation.cpp.o
[100%] Linking CXX executable solver
[100%] Built target solver
```

Проект успешно собран.

## 9. Проверка hello_world

Команда:

```bash
./_build/hello_world_application/hello_world
```

Вывод:

```text
-------------------------
hello, world!
-------------------------
```

Приложение работает корректно.

## 10. Проверка solver

Команда:

```bash
./_build/solver_application/solver
```

Для проверки были введены коэффициенты квадратного уравнения:

```text
1
-3
2
```

То есть решалось уравнение:

```text
x² - 3x + 2 = 0
```

Полученный вывод:

```text
-------------------------
x1 = 1.000000
-------------------------
-------------------------
x2 = 2.000000
-------------------------
```

Получены правильные корни `1` и `2`.

## Вывод

В ходе лабораторной работы была изучена система сборки CMake. Для существующих библиотек и приложений были созданы отдельные файлы `CMakeLists.txt`, настроены зависимости между целями и создан общий корневой файл сборки.

Исходная структура проекта была сохранена. Проект успешно конфигурируется и собирается, приложения `hello_world` и `solver` запускаются и работают корректно.

