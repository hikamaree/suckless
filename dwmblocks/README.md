# Introduction
This is my build of dwmblocks. It is a tool to modify the statis bar for dwm. It has modules for:
1. Internet bandwidth
2. Volume level
3. Brightnest
4. Battery
5. Time

# What is dwmblocks?
As described by torrinfail:

> Modular status bar for dwm written in c.
> # modifying blocks
> The statusbar is made from text output from commandline programs.
> Blocks are added and removed by editing the blocks.h header file.

# Dependencies
* DWM
* pulseaudio (uses pactl)
* brillo

# Running dwmblocks
In your `~/.xinitrc` file put: 

``` bash
dwmblocks 2>&1 >/dev/null &
```
