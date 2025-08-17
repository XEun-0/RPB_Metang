#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <vector>

// Get the local IP of the interface
bool getPPPIP(const std::string &iface, std::string &ip) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) return false;

    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ-1);
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        close(fd);
        return false;
    }

    struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;
    ip = inet_ntoa(addr->sin_addr);
    close(fd);
    return true;
}

// Get the remote (peer) IP of the PPP interface
bool getPPPRemoteIP(const std::string &iface, std::string &peerIP) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) return false;

    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ-1);
    if (ioctl(fd, SIOCGIFDSTADDR, &ifr) < 0) {
        close(fd);
        return false;
    }

    struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_dstaddr;
    peerIP = inet_ntoa(addr->sin_addr);
    close(fd);
    return true;
}

// Check if a default route exists via the given interface
bool hasRoute(const std::string &iface) {
    std::ifstream routeFile("/proc/net/route");
    if (!routeFile.is_open()) {
        return false;
    }

    std::string line;
    getline(routeFile, line); // skip header
    while (getline(routeFile, line)) {
        std::istringstream iss(line);
        std::string ifName, dest, gateway;
        iss >> ifName >> dest >> gateway;
        if (ifName == iface && dest == "00000000") {
            return true; // default route exists
        }
    }
    return false;
}

// Combined check
bool verifyPPP(const std::string &iface,
               const std::string &expectedLocal,
               const std::string &expectedRemote) {
    std::string localIP, remoteIP;

    if (!getPPPIP(iface, localIP)) return false;
    if (!getPPPRemoteIP(iface, remoteIP)) return false;

    if (localIP != expectedLocal) return false;
    if (remoteIP != expectedRemote) return false;

    if (!hasRoute(iface)) return false;

    return true;
}

int main() {
    std::string iface = "ppp0";
    std::string expectedLocal = "192.168.100.2";  // replace with actual
    std::string expectedRemote = "192.168.100:193";   // replace with actual

    if (verifyPPP(iface, expectedLocal, expectedRemote)) {
        std::cout << iface << " is up with correct IPs and route.\n";
    } else {
        std::cout << iface << " is not configured correctly or route missing.\n";
    }

    return 0;
}
