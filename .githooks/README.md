# Git Hooks

This directory contains Git hooks for the project. The hooks are automatically used by Git due to the `core.hooksPath` configuration.

## Current Hooks

### pre-commit
- Automatically formats staged C++ files using clang-format
- Only formats files that are part of the current commit
- Uses the project's `.clang-format` configuration
- Automatically stages the formatted files back into the commit

## Setup

The hooks are automatically set up when you clone the repository. If you need to manually set up the hooks, run:

```bash
git config core.hooksPath .githooks
```

## Requirements

- clang-format must be installed
- The project must have a `.clang-format` configuration file in the root directory 