# EmbeddedSystemsDevelopment
Repository for Embedded Systems Development Module

Team 0xDEADBEEF
>@hsert29
>@dansteer
>@HarrisonJM

#Directory Structure

The top level folder (where this file is located) Contains any notes and none code related things.

ECGReader contains the CMake Structure.
```
.
├── ECGReader
│   ├── CMakeLists.txt
│   ├── myApps
│   │   ├── CMakeLists.txt
│   │   ├── networkedECG
│   │   │   └── CMakeLists.txt
│   │   └── standaloneECG
│   │       └── CMakeLists.txt
│   ├── myLibraries
│   │   ├── CMakeLists.txt
│   │   └── display
│   │       ├── CMakeLists.txt
│   │       └── display.c
│   └── otherLibraries
└── README.md
```

myApps contains any executables related to the assignment
myLibraries contains all libraries written for the purposes of making the executables work
otherLibraries will contain any 3rd party libraries we've used for convenience and repackaged for the markers convenience
