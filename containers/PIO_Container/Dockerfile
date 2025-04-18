FROM python:3.10-slim

# Arguments for user setup
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and PlatformIO dependencies
RUN apt-get update && apt-get install -y \
    git \
    curl \
    gcc \
    g++ \
    make \
    python3-pip \
    sudo \
    && pip3 install -U platformio \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user with sudo
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && usermod -aG dialout $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set working directory
WORKDIR /home/$USERNAME

# Switch to non-root user
USER $USERNAME

# Default to bash shell
CMD [ "bash" ]
