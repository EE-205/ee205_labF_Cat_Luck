Cat Luck
========

<img src=".doxygen/images/logo_Luck_1484_1330.png" style="width:300px; float: left; margin: 0 10px 10px 0;" alt="Lucky Cat"/>

Cats make their own luck

#### Links
The project's home page:
 https://github.com/EE-205/ee205_labF_cat_luck 
 (hosted by GitHub)

The source code is documented at:
 https://www2.hawaii.edu/~marknels/ee205/ee205_labF_cat_luck 
(hosted by The University of Hawaiʻi at Mānoa)

# Cat Luck
| Name                      | Value        |
|---------------------------|--------------|
| Estimated time to compete | 4 hours      |
| Point value               | Extra credit |
| Prerequisites             | EE 205       |
| Link                      | TBD          |

The goal of this lab is to:
  1. Write a simulation in C++

We are going to simulate a lottery (or lotto) which is a game where a group of
people pick a set of numbers in an attempt to match their set with a random 
drawing for a prize.

## Rules
  - When a ball (a number) is drawn, it is not returned... In other words, no 
    duplicate numbers (within a drawing).
  - It is, however, possible for two independent drawings to draw the same set 
    of numbers... in fact, if you match the "winning draw", then you win.
  - The order of the draw is not significant
  - No "bonus numbers"


# Makefile {#MakeTargets}
This simulation uses the following `Makefile` targets:

| Command              | Purpose                                                        |
|----------------------|----------------------------------------------------------------|
| `make`               | Compile (with clang++)                                         |
| `make run`           | Compile and run it                                             |
| `make test`          | Compile and run the Boost unit tests                           |
| `make debug`         | Compile with debug mode ( `DEBUG` is defined)                  |
| `make clean`         | Remove all compiler-generated files                            |
| `make doc`           | Make a Doxygen website                                         |
| `make lint`          | Use `clang-tidy` to do static analysis on the source code      |
| `make valgrind`      | Use `valgrind` to do dynamic analysis on a run                 |
| `make test-valgrind` | Use `valgrind` to do dynamic analysis on a Boost unit test run |


# Toolchain
This project is the product of a tremendous amount of R&D and would not be
possible without the following world-class tools:

| Tool           | Website                    |                                                          Logo                                                          |
|----------------|----------------------------|:----------------------------------------------------------------------------------------------------------------------:|
| **gcc**        | https://gcc.gnu.org        |        <img src=".doxygen/images/logo_gcc.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="GCC"/>        |
| **llvm/clang** | https://clang.llvm.org     |      <img src=".doxygen/images/logo_llvm.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="clang"/>       |
| **Boost**      | https://boost.org          |      <img src=".doxygen/images/logo_boost.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Boost"/>      |
| **Doxygen**    | https://doxygen.nl         |    <img src=".doxygen/images/logo_doxygen.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Doxygen"/>    |
| **DOT**        | https://graphviz.org       |        <img src=".doxygen/images/logo_dot.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Dot"/>        |
| **Git**        | https://git-scm.com        |        <img src=".doxygen/images/logo_git.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Git"/>        |
| **GitHub**     | https://github.com         |     <img src=".doxygen/images/logo_github.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="GitHub"/>     |
| **Linux**      | https://kernel.org         |      <img src=".doxygen/images/logo_linux.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Linux"/>      |
| **ArchLinux**  | https://archlinux.org      |  <img src=".doxygen/images/logo_archlinux.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="ArchLinux"/>  |
| **VirtualBox** | https://www.virtualbox.org | <img src=".doxygen/images/logo_virtualbox.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="VirtualBox"/> |
| **Valgrind**   | https://valgrind.org       |   <img src=".doxygen/images/logo_valgrind.png" style="height:40px; float: center; margin: 0 0 0 0;" alt="Valgrind"/>   |
