
# fjura@fjura:~$ cat /proc/cpuinfo | grep Revision
# Revision        : 902120

# fjura@fjura:~$ lsb_release -a
# No LSB modules are available.
# Distributor ID: Ubuntu
# Description:    Ubuntu 22.04.5 LTS
# Release:        22.04
# Codename:       jammy

FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    wget unzip parted kpartx sudo util-linux dosfstools \
    && apt-get clean


WORKDIR /workspace

COPY customize_rpi_os.sh .
COPY entrypoint.sh .

RUN chmod +x *.sh

ENTRYPOINT ["./entrypoint.sh"]


