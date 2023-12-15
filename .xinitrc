if [ "${XDG_SESSION_DESKTOP}" == "dwm" ]; then
    exec dbus-launch --sh-syntax --exit-with-session dwm
fi
