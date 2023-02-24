## kqlog

header-only, easy to use, C++ logging library

## Setup

clone the repo and run `make install`, the script will clone [magic_enum](https://github.com/Neargye/magic_enum), [fmt](https://github.com/fmtlib/fmt) in [vendor/](https://github.com/Robertkq/kqlog/tree/main/vendor)

## Platforms
* Linux: clang 10.0
* Windows: clang 10.0

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
![Rainbow Example]()

