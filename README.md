# Overview
NOTE: This is a WIP.

This app generates a todo list from the contents of a project directory. 

To skip a directory, add it to ".gentodoignore".

# Usage
**Command syntax:**
```
gentodo  <-- Generates list for working directory.
gentodo ./src <-- Generates list for src directory.
```

**TODO Comment Syntax:**
Todo comment will be:
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

# Notes
Supported file extensions? All?
List of dirs/files to ignore?
