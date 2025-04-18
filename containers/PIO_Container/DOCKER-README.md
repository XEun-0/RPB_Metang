docker build -t platformio-dev .

docker run --rm -it -v $(pwd)/:/workspace \
    -w /workspace \
    --device=/dev/ttyUSB0:/dev/ttyUSB0 \
    platformio-dev