# Snake

## About
The Snake game written in C and using Raylib for graphics.

## Usage
If you don't have [Raylib](https://github.com/raysan5/raylib) natively
installed, you first need a `.config` file that contains the paths to the 
local instance of the raylib library and include files. It should look like
the following:
```conf
LIBDIR=/path/to/raylib/library
INCLUDES=/path/to/raylib/headers
```

To build the program, simply run `make`. If you are on Windows, you will 
need to copy the `raylib.dll` file into your current directory, if you 
haven't done so already, or don't have Raylib natively installed.

Be sure to check the 
[Raylib instructions](https://github.com/raysan5/raylib#build-and-installation)
for building and installing to make sure you have the requisite packages
installed on your machine.

## Controls
With the game running you have the following control options:

| **Key**      | **Action**       |
|--------------|------------------|
| `Space Bar`  | Pause and Resume |
| `CTRL+N`     | Restart          |
| `Esc`        | Quit             |
| `Arrow keys` | Moving           |