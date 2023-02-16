## kqlog

header-only, easy to use, C++ logging library

## Setup

clone the repo and run `make install`, the script will clone [magic_enum](https://github.com/Neargye/magic_enum), [fmt](https://github.com/fmtlib/fmt) in [vendor/](https://github.com/Robertkq/kqlog/tree/main/vendor)

## Platforms
* Linux: clang 10.0
* Windows: clang 10.0

## Features
---
## Usage example
---

## Pattern flags
| flag | meaning | example |
|`%V`|The log itself|"your text"
|`%t`|Event type|"Debug" / "Info" / "YourEvent"
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
|`%T`|Thread id|"1234"
|`%L`|Caller's source line|"123"
|`%F`|Caller's function name|"my_func"
|`%s`|Caller's source file|"my_func_impl.cpp"
|`%%`|The % sign|"%"