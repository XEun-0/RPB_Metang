FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    cups \
    hplip \
    printer-driver-hpijs \
    avahi-daemon \
    sudo \
 && rm -rf /var/lib/apt/lists/*

# Allow web admin without auth
RUN sed -i '/<Location \/>/,/<\/Location>/s/Require local/Allow all/' /etc/cups/cupsd.conf

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 631

ENTRYPOINT ["/entrypoint.sh"]
