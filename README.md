# Лабораторная работа №4

репозиторий: https://github.com/Shohiii/lab04

Условие лабораторной работы: https://github.com/tp-labs/lab04

## Цель работы

Настроить систему непрерывной интеграции (CI) для проекта, разработанного в лабораторной работе №3.

Необходимо организовать автоматическую сборку проекта:

* в Linux с компилятором GCC;
* в Linux с компилятором Clang;
* в Windows с компилятором MSVC.

Все варианты сборки должны быть описаны в одном файле конфигурации CI.

## Исходный проект

В качестве основы используется проект из лабораторной работы №3.

Проект содержит следующие библиотеки и приложения:

* `formatter_lib`;
* `formatter_ex_lib`;
* `solver_lib`;
* `hello_world_application`;
* `solver_application`.

Структура проекта:

```text
.
├── .github
│   └── workflows
│       └── ci.yml
├── formatter_lib
├── formatter_ex_lib
├── hello_world_application
├── solver_application
├── solver_lib
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Проверка локальной сборки

Для конфигурации проекта была выполнена команда:

```bash
cmake -S . -B build
```

После успешной конфигурации проект был собран:

```bash
cmake --build build
```

Результат сборки:

```text
[ 20%] Built target formatter
[ 40%] Built target formatter_ex
[ 60%] Built target solver_lib
[ 80%] Built target hello_world
[100%] Built target solver
```

Таким образом, локальная сборка проекта завершилась успешно.

## Настройка GitHub Actions

Для автоматической сборки был создан один файл:

```text
.github/workflows/ci.yml
```

Для запуска нескольких вариантов сборки используется `matrix`.

Конфигурация включает три варианта:

```yaml
matrix:
  include:
    - os: ubuntu-latest
      compiler: g++
      name: Linux GCC

    - os: ubuntu-latest
      compiler: clang++
      name: Linux Clang

    - os: windows-latest
      compiler: cl
      name: Windows MSVC
```

Полный файл конфигурации:

```yaml
name: Lab04 CI

on:
  push:
  pull_request:

jobs:
  build:
    strategy:
      fail-fast: false
      matrix:
        include:
          - os: ubuntu-latest
            compiler: g++
            name: Linux GCC

          - os: ubuntu-latest
            compiler: clang++
            name: Linux Clang

          - os: windows-latest
            compiler: cl
            name: Windows MSVC

    name: ${{ matrix.name }}
    runs-on: ${{ matrix.os }}

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Configure Linux
        if: runner.os != 'Windows'
        run: cmake -S . -B build -DCMAKE_CXX_COMPILER=${{ matrix.compiler }}

      - name: Build Linux
        if: runner.os != 'Windows'
        run: cmake --build build

      - name: Configure Windows
        if: runner.os == 'Windows'
        run: cmake -S . -B build

      - name: Build Windows
        if: runner.os == 'Windows'
        run: cmake --build build --config Release
```

## Отправка изменений в репозиторий

Изменения были добавлены в Git:

```bash
git add -A
```

Создан коммит:

```bash
git commit -m "Fix lab04 project and add CI matrix"
```

Изменения отправлены в удалённый репозиторий:

```bash
git push origin master
```

После отправки изменений GitHub Actions автоматически запустил CI.

## Результат CI

Запуск GitHub Actions:

```text
Lab04 CI
Run ID: 34829669152
```

Результаты:

```text
✓ Windows MSVC
✓ Linux GCC
✓ Linux Clang
```

Все три сборки успешно завершены.

Ссылка на запуск GitHub Actions:

https://github.com/Shohiii/lab04/actions/runs/34829669152

## Вывод

В ходе лабораторной работы была настроена система непрерывной интеграции GitHub Actions для проекта из лабораторной работы №3.

В одном файле конфигурации CI организованы три варианта автоматической сборки:

* Linux GCC;
* Linux Clang;
* Windows MSVC.

Все варианты сборки завершились успешно.
