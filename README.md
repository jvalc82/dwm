## jvalc's build of dwm

## Usage
Get more information about the usage of my build, including useful keybindings
by executing `man dwm` in your terminal.

## Used patches from suckless project
- vanitygapps + dwm-layouts + cfact:    Graphical layouts
- sticky:                               Makes a window persistent across tags
- transfer:                             Moves windows up and down the stack
- xresources:                           Allows configuration of the GUI using .Xresources
- fullscreen:                           Changes the current layout to monacle
- alpha + fix-borders:                  Window transparency 
- shift-tools:                          Cycle through tags
- pertag:                               Apply layout configurations per tag

## Installation 
- `git clone https://github.com/jvalc82/dwm.git`
- `cd dwm`
- `make`
- `sudo make install`

## Future steps
All the code can be expanded from source. Also, to change some of the configurations
you need edit the "config.h", do not edit "config.def.h".
