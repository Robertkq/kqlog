## kqlog

header-only, easy to use, C++ logging library
minimum C++17

## Setup

clone the repo with `--recursive`, it will clone:
[kqlog](https://github.com/Robertkq/kqlog),
[fmt](https://github.com/fmtlib/fmt),
[magic_enum](https://github.com/Neargye/magic_enum),
[Catch2](https://github.com/catchorg/Catch2).

## Platforms
* Linux: clang 15.0.7
* Windows: clang 15.0.7

## Features
---
* Header only
* Allows user defined log types(/levels)
* Log filtering
* Log color
* Custom formtting for log pattern
* Rich formatting, by [fmt](https://github.com/fmtlib/fmt)
* Thread safe
* Backup
* xml for .npp log files (in progress)

## Pattern flags
| flag | meaning | example |
| :----: | :-------: | :-------: |
|`%V`|The log itself|"your text"|
|`%T`|Event type|"Debug" / "Info" / "YourEvent"|
|`%Y`|Year|"2023"|
|`%M`|Month 01-12|"06"|
|`%m`|Month full name|"June"|
|`%b`|Month abbriviated name|"Jun"|
|`%D`|Day 01-31|"23"|
|`%d`|Day full name|"Friday"|
|`%B`|Day abbriviated name|"Fri"|
|`%H`|Hours 00-23|"18"|
|`%N`|Minutes 00-59|"42"|
|`%S`|Seconds 00-59|"36"|
|`%t`|Thread id|"1234"|
|`%L`|Caller's source line|"123"|
|`%F`|Caller's function name|"my_func"|
|`%s`|Caller's source file|"my_func_impl.cpp"|
|`%%`|The % sign|"%"|
|`%K`|Black color|![black](https://placehold.co/15x15/black/black.png)|
|`%R`|Red color|![red](https://placehold.co/15x15/red/red.png)|
|`%G`|Green color|![green](https://placehold.co/15x15/green/green.png)|
|`%y`|Yellow color|![yellow](https://placehold.co/15x15/yellow/yellow.png)|
|`%E`|Blue color|![blue](https://placehold.co/15x15/blue/blue.png)|
|`%g`|Magenta color|![magenta](https://placehold.co/15x15/magenta/magenta.png)|
|`%C`|Cyan oclor|![cyan](https://placehold.co/15x15/cyan/cyan.png)|
|`%W`|White color|![white](https://placehold.co/15x15/white/white.png)|

## Usage example
---
### Custom log file
by default the logger will output into `./output/logs.txt` (filename="logs.txt", directory="output/")
you can change it by providing a filename and directory in the constructor
e.g
```
kq::logger logger("myfile.txt", "myDirectory/myOutputDirectory/");
```
Make sure to include any **/** in your directory

---
### Declare a logger with your own custom enum
```
enum class myTypes { /* your types here */ };
kq::logger<myTypes> loggers;
```
if no template argument is provided, kq::default_symbols is used as a default, containing:
(macros)
1. KQDEBUG
2. KQINFO
3. KQWARNING
4. KQERROR
5. KQCRITICAL
--- 
### How to log with your logger
call .out() with an enum type and a format string with all it's argument wrapped in {}
e.g
```
logger.out( KQINFO, { "{} is a nice {}", "Today", "day" } );
output: `[2023-02-27 06:38:11] [INFO] [main@07] Today is a nice day`
```
---
### Custom pattern
by default the logger will have the following pattern:
```
[{%Y}-{%M}-{%D} {%H}:{%N}:{%S}] [{%T}] [{%F}@{%L}] {%V}
```

see [Pattern Flags](#pattern-flags) for reference
you can change this pattern with `.set_pattern()` and provide a string containing the new pattern
to reset to the default pattern call the function with no arguments

---
### Rainbow
```
kq::logger Logger("logs.txt", "output/");
    for(int i = 0; i < 10; ++i)
    {
        Logger.set_pattern("{%R}[{%Y}-{%M}-{%D}{%y} {%H}:{%N}:{%S}] {%G}[{%T}] {%E}[{%F}@{%L}] {%V}\n");
        Logger.out(KQINFO, {"{%C} {0:5} {%g}START", i + 10});
        Logger.set_pattern("{%y}[{%Y}-{%M}-{%D}{%G} {%H}:{%N}:{%S}] {%C}[{%T}] [{%F}@{%L}] {%V}\n");
        Logger.out(KQDEBUG, {"{%g} {0:5} {%R}CONTINUE", i + 10});
        Logger.set_pattern("{%G}[{%Y}-{%M}-{%D}{%C} {%H}:{%N}:{%S}] {%E}[{%T}] [{%F}@{%L}] {%V}\n");
        Logger.out(KQCRITICAL, {"{%R} {0:5} {%E}END", i + 10});
    }
```
![Rainbow Example](https://github.com/Robertkq/kqlog/blob/main/img/RainbowExample.png)

### Other
this project was made by [me](www.github.com/robertkq) and [norctus](www.github.com/norctus)   
we took inspiration from other loggers like [spdlog](https://github.com/gabime/spdlog) and [plog](https://github.com/SergiusTheBest/plog)   
but we've added our on twist and took a more flexible and different approach on our logger