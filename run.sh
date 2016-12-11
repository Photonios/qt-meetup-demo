display=$DISPLAY
socket="/tmp/.X11-unix"

if [ "$(uname)" == "Darwin" ]; then
    ip=10.200.10.1
    sudo ifconfig lo0 alias $ip/24
    display="$ip:0"
fi


docker run --privileged -v $(pwd):/home/developer/image-converter -v $socket:$socket -e DISPLAY=$display -ti photonios/qtcpp:latest
