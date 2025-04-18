FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    git \
    wget \
    flex \
    bison \
    gperf \
    python3 \
    python3-pip \
    python3-venv \
    cmake \
    ninja-build \
    ccache \
    libffi-dev \
    libssl-dev \
    dfu-util \
    && rm -rf /var/lib/apt/lists/*

# Set up ESP-IDF
WORKDIR /opt
RUN git clone --recursive https://github.com/espressif/esp-idf.git
WORKDIR /opt/esp-idf

# Checkout a compatible version (e.g., v5.4)
RUN git checkout v5.4 && git submodule update --init --recursive

RUN ./install.sh
RUN echo 'source /opt/esp-idf/export.sh' >> ~/.bashrc

# Set the default shell
CMD ["/bin/bash"]
