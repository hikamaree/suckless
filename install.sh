#!/bin/sh

sudo pacman -S --noconfirm xorg-xinit xorg-server xorg-xset libxft libx11 libxinerama webkit2gtk maim xclip picom feh

cd dwm
sudo make clean install
cd ../dwmblocks
sudo make clean install
cd ../dmenu
sudo make clean install
cd ../st
sudo make clean install
cd ..

sudo cp xorg/20-amdgpu.conf /etc/X11/xorg.conf.d/20-amdgpu.conf
sudo cp xorg/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf

cp -rf config/* $HOME/.config/

sudo cp scripts/* /usr/local/bin/
