

# compiler and flags
CXX := g++
CXX_FLAGS := -Wall -02

# source files
SENDER_SRC := udp_send_tester.cpp
RECV_SRC := udp_recv_tester.cpp

# Output binaries
SENDER_BIN := udp_sender
RECV_BIN := udp_receiver

# Default target (shows usage)
all:
	@echo "Usage:"
	@echo "  make sender    # To build udp_sender"
	@echo "  make receiver  # To build udp_receiver"

# Compile sender
sender: $(SENDER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SENDER_BIN) $(SENDER_SRC)

# Compile receiver
receiver: $(RECV_SRC)
	$(CXX) $(CXXFLAGS) -o $(RECV_BIN) $(RECV_SRC)

# Clean build files
clean:
	rm -f $(SENDER_BIN) $(RECV_BIN)