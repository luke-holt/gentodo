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
The todo comment *must* begin with "TODO:" or "FIXME:". You can add tags to these comments by adding them after "TODO:".
```
/* TODO: Add this very cool feature. */
/* FIXME: Optimize this O(n^n) algo to be O(1). */
/* TODO: TEST: Add unit test for this function */
```

# Notes
Supported file extensions? All?
List of dirs/files to ignore?
