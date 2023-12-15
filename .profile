if [ "${XDG_SESSION_DESKTOP}" == "dwm" ]; then
    DESKTOP_WALLPAPER="${HOME}/.local/share/backgrounds/dark/black2.jpeg"
    export BROWSER="firefox"
    export BROWSER_ALT="brave"
    export SECONDARY_BROWSER="tabbed surf -e"
    export EREADER="FBReader"

    xcompmgr -o .80 &
    feh --bg-scale ${DESKTOP_WALLPAPER}
fi



