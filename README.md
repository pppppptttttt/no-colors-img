## Description

40 minute of automation of 3 minute work. Well, i was bored. But now it is 5 seconds work!

Script to discard color channels and leave only one (or two, if there was transparency). Output will be in png format

Will compile in unix linux/macos, but no platforme-dependend code is used, so windows compilation script is welcomed in PR!
(not sure about mac os, but have no machine to check)

**Requirenments**: C++ compiler that supports c++17

## Instructions for linux/macos systems:

**Clone & Build**:
```sh
git clone git@github.com:pppppptttttt/no-colors-img.git
cd no-colors-img
make
```
If you want to **install globally**:
```sh
sudo make install
```
**Uninstall**:
```sh
sudo make uninstall
```
**Usage**:
```sh
./no-colors-img <path/to-file> <path-to-output>
```

*NB*: parallel image generation. kinda nice^_^
