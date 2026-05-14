# cpp-explicit-return
Explicit void return semantic utility for C++ — use RETURN() instead of ambiguous return; in production projects.

## Overview
In C++, the native `return;` statement for void functions has implicit semantic ambiguity. It does not clearly express "returning nothing", leading to inconsistent style and reduced readability in large engineering projects.

`cpp-explicit-return` provides a standardized `RETURN()` macro to make void return **explicit, clear, and consistent**.

## Why RETURN() instead of return?
- **Semantic clarity**: `return;` is ambiguous for void types; `RETURN()` explicitly means "no value to return".
- **Engineering consistency**: Uniform return style across the codebase.
- **Readability**: Makes void return points immediately visible in code reviews.
- **Maintainability**: Reduces misunderstanding caused by implicit syntax.

## Usage
```cpp
#include "return.h"

void test() {
    // Explicit void return
    RETURN();
}

## Recommendation
We strongly recommend using RETURN() in formal engineering and production projects to establish strict, clear, and maintainable coding conventions.
