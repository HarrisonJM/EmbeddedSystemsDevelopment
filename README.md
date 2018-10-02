# EmbeddedSystemsDevelopment
Repository for Embedded Systems Development Module

Team 0xDEADBEEF
### @hsert29
### @dansteer
### @HarrisonJM 

#Directory Structure

The top level folder (where this file is located) Contains any notes and none code related things.

ECGReader contains the CMake Structure.
```
.
├── ECGReader\n
│   ├── CMakeLists.txt\n
│   ├── myApps\n
│   │   ├── CMakeLists.txt\n
│   │   ├── networkedECG\n
│   │   │   └── CMakeLists.txt\n
│   │   └── standaloneECG\n
│   │       └── CMakeLists.txt\n
│   ├── myLibraries\n
│   │   ├── CMakeLists.txt\n
│   │   └── display\n
│   │       ├── CMakeLists.txt\n
│   │       └── display.c\n
│   └── otherLibraries\n
└── README.md\n
```

myApps contains any executables related to the assignment
myLibraries contains all libraries written for the purposes of making the executables work
otherLibraries will contain any 3rd party libraries we've used for convenience and repackaged for the markers convenience
