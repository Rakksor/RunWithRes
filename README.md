# RunWithRes
RunWithRes is a command line utility to automatically switch the desktop resolution when running a program. 

Before starting the specified program the desktop resolution is changed to the given values and after the program terminates the resolution is changed back to the previously used one.

## Download
The latest release containing an example file for easy setup can be found [here](https://github.com/Rakksor/RunWithRes/releases/latest)

## Usage
### General
```
usage: runwithres <width> <height> <path to program> <arguments>
			 
       note that <arguments> is optional and that if you have multiple arguments
       you have to enclose the list of arguments with quotation marks (")
```

### Examples
running a program at a desktop resolution of 800x600:
```
runwithres 800 600 "C:\path\to the\program.exe"
```

running a program with additional arguments at a desktop resolution of 1024x768
```
runwithres 800 600 "C:\path\to the\program.exe" "/a /b /c"
```
