[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

# Overview
NOTE: This is a WIP.

This app generates a todo list from the contents of a project directory. 

To skip a directory, add it to ".gentodoignore".

# Usage
**Command syntax:**
```
gentodo -s <sort-by> -e <regex-file-ext> -f <ignore-file> -o <output-file> -h
```
Sort by:
- `file`
- `type`
- `topic`

Regex file extension:
- i.e. "(cpp|hpp)" for `.cpp` and `.hpp` files

**TODO Comment Syntax:**
Todo comment needse to be:
- one line long
- begin with `TODO:`, `FIXME:`, `HACK:`, or `NOTE:`
- Topics follow the declaration and are formatted the same way
    - i.e. `TEST:`
- Message follows the topic and is terminated by a period (`.`)
```
/* TODO: Add this very cool feature. */
/* FIXME: SORT: Optimize this O(n^n) algo to be O(1). */
/* TODO: TEST: Add unit test for this function. */
```

# Ignore file
`.gentodoignore`... this needs a new name.

The app tries to load this file from the current directory. To specify the ignore file use the `--ignore` option.

# Notes
Supported file extensions? Anything that contains ascii.

