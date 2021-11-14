# Guxt Decompilation Project

A decompilation of 2007 freeware shmup by Studio Pixel.

100% playable.

Mostly based on work of [@tilderain](https://github.com/tilderain).

Reverse engineering of remaining parts and various fixups was done by me (Alula).

You need data files from original game and place them in same directory as your freshly compiled `pxGame.exe`.

Get them from there: https://studiopixel.jp/binaries/guxt_1020_wz.zip

Note from IDB:

```
Guxt IDB v0.4a
TODO: fix inconsistent entity/npchar naming + structs
	  fix inconsistent variable capitalization
	  
NOTE: carets/bullets/npchars are probably all one struct in the code, but are seperated here for "clarity"

thx 2 noxid for decoded PximgDecode function
thx 2 idioticbaka1824 for entity documentation

idb by rain do not steal
```

Original code and assets is © Daisuke Amaya/Studio Pixel (and maybe Nicalis if they own the IP for his old games).