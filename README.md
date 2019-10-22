# hsm - Hierarchical State Machine

A library for implementing UML 2.0 state diagrams / statecharts in plain C, unit tested and without dynamic allocation or recursion (designed to be suitable for embedded targets).

## Quick Start

### Prerequisites

For Compiling
- `ruby`
- Ruby gem `rake`
- `gcc` (or define your own compiler in project.yml)

### Other Tools

For creation of tags
- `ctags`

For creation of documentation
- `doxygen`

Also includes a configuration file for [Valloric/YouCompleteMe](https://github.com/Valloric/YouCompleteMe), the `vim` plugin.
 
### Building
- Tool documentation is located in `vendor/ceedling/docs`
- Execute `ceedling help` to view available test & build tasks
- Execute `make-all.bat` to do a full clean & build & generate tags & documentation

