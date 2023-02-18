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
* Log filtering (for console)
* Log color (for console) (in progress)
* Custom formtting for log pattern
* Rich formatting, by [fmt](https://github.com/fmtlib/fmt)
* Thread safe
* Backup
* xml for .npp log files (in progress)

## Usage example
---

## Pattern flags
| flag | meaning | example |
| :----: | :-------: | :-------: |
|`%V`|The log itself|"your text"
|`%T`|Event type|"Debug" / "Info" / "YourEvent"
|`%Y`|Year|"2023"|
|`%M`|Month 01-12|"06"|
|`%m`|Month full name|"June"|
|`%b`|Month abbriviated name|"Jun"|
|`%D`|Day 01-31|"23"|
|`%d`|Day full name|"Friday"
|`%B`|Day abbriviated name|"Fri"
|`%H`|Hours 00-23|"18"
|`%N`|Minutes 00-59|"42"
|`%S`|Seconds 00-59|"36"
|`%t`|Thread id|"1234"
|`%L`|Caller's source line|"123"
|`%F`|Caller's function name|"my_func"
|`%s`|Caller's source file|"my_func_impl.cpp"
|`%%`|The % sign|"%"
|`%K`|Black color|<p style="color: black">"some *black* text"</p>
|`%R`|Red color|<p style="color: red">"some *red* text"</p>
|`%G`|Green color|<p style="color: green">some *green* text"</p>
|`%y`|Yellow color|<p style="color: yellow">some *yellow* text"</p>
|`%E`|Blue color|<p style="color: blue">some *blue* text</p>
|`%g`|Magenta color|<p style="color: red">some *magenta* text"</p>
|`%C`|Cyan oclor|<p style="color: cyan">some *cyan* text</p>
|`%W`|White color|<p style="color: white">some *white* text"</p>