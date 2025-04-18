docker build -t esp-idf-container .

docker run --rm -it --privileged -v /dev:/dev -v $(pwd):/workspace esp-idf-container

