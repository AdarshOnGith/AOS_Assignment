# Makefile for seam_carving

# Compiler and flags
CXX = g++
CXXFLAGS = -I/usr/local/include/opencv4
LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

# Source and target
SRC = 2024201066_A1_Q4.cpp
TARGET = seam_carving


# Color codes
WHITE = \033[97m
CYAN = \033[96m
RESET = \033[0m
BLUE = \033[94m
GBG = \033[42m
BOLD = \033[1m
LYELLOW = \033[93m
ORG = \033[91m

# Default rule
all: $(TARGET)
	@echo ""
	@echo "$(BLUE)---------------------------------------------------------------$(RESET)"
	@echo "$(GBG)$(WHITE)$(BOLD)Build complete. $(RESET)"
	@echo "$(CYAN)Target executable name is:$(WHITE)$(BOLD) $(TARGET)$(RESET)"
	@echo ""
	@echo "$(WHITE)Usage Syntax:  $(RESET)"
	@echo "$(ORG)For both W & H inputs Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) </Input_Name.jpeg> </Output_Name.jpeg> <New Width> <New Height>$(RESET)"
	@echo "$(BLUE)----------------(OR)-----------------$(RESET)"
	@echo "$(ORG)For only  Width input Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) </Input_Name.jpeg> </Output_Name.jpeg> <New Width> 0$(RESET)"
	@echo "$(BLUE)----------------(OR)-----------------$(RESET)"
	@echo "$(ORG)For only Height input Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) </Input_Name.jpeg> </Output_Name.jpeg> 0 <New Height>$(RESET)"
	@echo "$(BLUE)---------------------------------------------------------------$(RESET)"
	@echo ""

# Rule to build the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean