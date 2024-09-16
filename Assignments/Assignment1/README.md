# Description:
- This Directory contains following Files having directory Structure:
	```bash 
	2024201066_A1/
	│
	├── 2024201066_A1_Q2.cpp
	├── 2024201066_A1_Q3a.cpp
	├── 2024201066_A1_Q3b.cpp
	├── Makefile
	└──  2024201066_A1_Q4.cpp
	```
- MakeFile is usable for 2024201066_A1_Q4.cpp
	
# Task 2: Trie Harder 
An efficient spell checker using the Trie data structure which supports the
functionalities mentioned below.
1. Spell Check: Check if the input string is present in the dictionary.
2. Autocomplete: Find all the words in the dictionary which begin with the given input.
3. Autocorrect: Find all the words in the dictionary which are at an edit
distance(Levenshtein distance) of at most 3 from the given input.


- Program File: 2024201066_A1_Q2.cpp
- Inputs Format:
   - First line will contain two space separated integers n, q which represents the number of
   words in the dictionary and the number of queries to be processed respectively.
   - Next n lines will contain a single string s which represents a word in the dictionary.
   - Next q lines will contain two space separated values, First one will be an integer ai and
   second will be a string ti.
   - ai = 1 means Spell Check operation needs to be done on ti.
   - ai = 2 means Autcomplete operation needs to be done on ti.
   - ai = 3 means Autocorrect operation needs to be done on ti.
- OutPut Format:
 
	- For each query print the result in a new line.
  - Spell check: Print ‘1’ if string is present in the dictionary, otherwise ‘0’.
  - Autocomplete & Autocorrect: Print the number of words in the first line. The following
  lines will be the set of words in lexicographical order.
  
- Assumptions: Both strings s and t consist of lowercase English letters.

- Constraints:
  ```bash
	1 <= n <= 1000
	1 <= q <= 1000
	1 <= len(s) <= 100 1 <= len(ti) <= 110
  ```

# Task 3: Priority Queue
## part A
- A priority queue is a data structure that maintains a collection of
elements,
each associated with a priority or value. Elements are stored in a way that
allows the retrieval of the element with the highest (or lowest) priority
quickly.
- Program File: 2024201066_A1_Q3a.cpp
- Inputs: none
- OutPuts: Tests operatiions printed.
- For retrieval of the element with the highest (or lowest) priority:
  - use minHeap declaration  (lowest is given first priority)
  - use maxHeap declaration  (highest is given first priority)
### Declaration
```bash
priority_queue pq;  // Creates a max-heap priority queue.

priority_queue pq("greater");  // Creates a min-heap priority queue.
```

### Features
```bash
Push: Add an element to the priority queue.
Pop: Remove the highest-priority element from the priority queue.
Top: Retrieve the highest-priority element without removing it.
Size: Get the current number of elements in the priority queue.
Empty: Check if the priority queue is empty.
```
### How to run project:
- build using command
	```bash
	g++ 2024201066_A1_Q3a.cpp -o 'Executable File Name'
	```
- Run using below syntax
	```bash
	./`Executable File Name`
	```

## part B
if the sales on a
specific day is greater than or equal to the combined sum of the median sale
for a trailing number of d days and the median sale from the first day of the
promotion then offered  free 'Cheeeeeese Maggi'. 
- 2024201066_A1_Q3b.cpp
- Input Format :
  - The first line contains two space-separated integers n and d, the number
  of days of daily sales data, and the number of trailing days respectively.
  - The second line contains n space-separated non-negative integers
  where each integer i denotes sales[i].
- Output Format :
  - int: the total number of days david will offer free maggi to students.
- Constraints :
  - 1<=n<=2*10^5
  - 1<=d<n
  - 1 <= sales[i] <= 10^5

- build using command
	```bash
	g++ 2024201066_A1_Q3a.cpp -o 'Executable File Name'
	```
- Run using below syntax
	```bash
	./`Executable File Name`
	```

# Task 4: Seam Carving 
- Applied seam carving content aware image-resizing (only reduces the image) algorithm on a given image. Take the height and width (in pixels) of the output image as inputs from the user.
- Uses OpenCv Libraries and Sobel function for energy Calculation
- *Inputs:* Image path & name, destination for output image & name, new width and new heigth
- *OutPut:* Resized Image saved at given destination.

## How to run project:
- Recommended: using make command
    ```bash 
     Directory Structure:
        2024201066_A1/
        │
        ├── Makefile
        ├── 2024201066_A1_Q4.cpp
        └── sampleIp/	 
            └── sample1.jpeg
    ```
- 2024201066_A1_Q4.cpp and MakeFile
    1. build using Makefile

        ```bash
        make
        ```
    2. Run using below syntax
        ```bash
        Usage Syntax:
            For both W & H inputs Run it as:  
                ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> <New Width> <New Height>

            ----------(OR)----------

            For only  Width input Run it as:  
                ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> <New Width> 0

            ----------(OR)---------

            For only Height input Run it as:  
                 ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> 0 <New Height>
        ```





        #### Example:
        ```bash
        ./seam_carving ../sampleIp/sample1.jpeg ../resized_image.jpeg 300 400
        ```
        Here:  <br>
            `../sampleIp/sample1.jpeg` is the input image.
            `../resized_image.jpeg` is where the resized image will be saved.
            300 is the target height.
            400 is the target width.
    



### TroubleShooting:

- Check File Permissions:
    ```bash
    ls -l ~/Desktop/seamc/sampleIp/sample1.jpeg
    ls -1 Makefile
    ls -1 CMakeLists.txt
    ```

- Change Permissions if Needed:
    ```bash
    chmod +r ~/path/sample1.jpeg
    chmod 644 Makefile
    chmod 644 CMakeLists.txt
    ```

- Verify Image File Integrity
    ```bash
    eog ~/Desktop/seamc/sampleIp/sample1.jpeg
    ```    

- **Warning upon execution:**  Gtk-Message: 
    Failed  to load module "canberra-gtk-module"
    Reason: cv::imshow Function: This function uses GTK under the hood to create a window and display images. The canberra-gtk-module is used to handle sound events in GTK applications, but it is not required for the image display functionality itself. If the GTK installation on your system is missing certain modules, you might see this warning message. 

    **Solution:** 
    - Ignore it (OR)
    Install GTK Dependency/ canberra-gtk-module
        ```bash 
        sudo apt-get install libcanberra-gtk-module libcanberra-gtk3-module
        ```
### MakeFile Configuration:
  - If want to use make file, create a Makefile file in your project directory with the following config:
    ```bash	
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
        @echo "$(ORG)For both W & H inputs Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) <Input_Name.jpeg> <Output_Name.jpeg> <New Width> <New Height>$(RESET)"
        @echo "$(BLUE)----------------(OR)-----------------$(RESET)"
        @echo "$(ORG)For only  Width input Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) <Input_Name.jpeg> <Output_Name.jpeg> <New Width> 0$(RESET)"
        @echo "$(BLUE)----------------(OR)-----------------$(RESET)"
        @echo "$(ORG)For only Height input Run it as: $(LYELLOW)$(BOLD) ./$(TARGET)$(RESET) $(WHITE) <Input_Name.jpeg> <Output_Name.jpeg> 0 <New Height>$(RESET)"
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
    ```
### **More Options To build:**
  1. Using g++ command from terminal
      ```bash
      Directory Structure:
          2024201066_A1/
          │
          ├── 2024201066_A1_Q4.cpp
          └── sampleIp/	 
              └── sample1.jpeg
      ```
      - build using below command
  
          ```bash
              g++ 2024201066_A1_Q4.cpp -o seam_carving -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
          ```

  2. Using CMakeLists.txt
      
      ```bash
      Directory Structure:
          2024201066_A1/
          │
          ├── CMakeLists.txt
          ├── 2024201066_A1_Q4.cpp
          ├── sampleIp/
          │   └── sample1.jpeg
          └── build/
      ```
     - **MakeLists.txt Configuration:**
        If want to use CMake, create a CMakeLists.txt file in your project directory with the following config:
        ```bash
        cmake_minimum_required(VERSION 3.10)
        project(SeamCarving)

        # Find the OpenCV package
        find_package(OpenCV REQUIRED)

        # Include OpenCV directories
        include_directories(${OpenCV_INCLUDE_DIRS})

        # Define the executable
        add_executable(seam_carving 2024201066_A1_Q4.cpp)

        # Link OpenCV libraries to the executable
        target_link_libraries(seam_carving ${OpenCV_LIBS})
        ```

     - build from below instructions:

         ```bash
             cd your_project_directory
             mkdir build
             cd build
             cmake ..
             make
         ```

  - Run using below syntax
      ```bash
          Usage Syntax:
              For both W & H inputs Run it as:  
                  ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> <New Width> <New Height>

              ----------(OR)----------

              For only  Width input Run it as:  
                  ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> <New Width> 0

              ----------(OR)---------

              For only Height input Run it as:  
                  ./seam_carving  </Input_Name.jpeg> </Output_Name.jpeg> 0 <New Height>
          ```

## How to setup OpenCv

### clean existing libraries (optional)
```bash
sudo apt-get remove --purge libopencv*
sudo apt-get autoremove
sudo apt-get autoclean
```


### Install OpenCV
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```


### Download and Build OpenCV
```bash
cd ~
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install
```

### verify Installation
```bash
ls /usr/include/opencv4
pkg-config --cflags opencv4
```


### Configure VS Code (optional)

- step -1 : Install VS Code Extensions

    Install the C/C++ extension by Microsoft.
    Optionally, install CMake Tools extension if you are using CMake for build configuration.

- step-2: Configure c_cpp_properties.json

    In VS Code, go to the Command Palette (Ctrl+Shift+P), and select C/C++: Edit Configurations (JSON). Add or update the following configuration to include OpenCV headers:

        {
            "configurations": [
            {
            "name": "Linux",
            "includePath": [
            "${workspaceFolder}/**",
            "/usr/local/include/opencv4"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
            }
            ],
            "version": 4
        }
    

- step-3: Configure Build Task	
    Create a `tasks.json` in the .vscode folder of your project directory to build your project using CMake:
    ``` bash
        {
            "version": "2.0.0",
            "tasks": [
            {
            "label": "build",
            "type": "shell",
            "command": "cmake",
            "args": [
            "-S.",
            "-Bbuild"
            ],
            "group": {
            "kind": "build",
            "isDefault": true
            },
            "problemMatcher": [],
            {
            "label": "build and run",
            "type": "shell",
            "dependsOn": "build",
            "command": "${workspaceFolder}/build/seam_carving",
            "group": {
            "kind": "build",
            "isDefault": true
            },
            "problemMatcher": []
            ]
        }
    ```

    Create a `launch.json` in the .vscode folder of your project directory to build your project using CMake:
    ``` bash
        {
            "version": "0.2.0",
            "configurations": [
            {
                "name": "Debug",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/build/my_opencv_app",
                "args": [],
                "stopAtEntry": false,
                "cwd": "${workspaceFolder}",
                "environment": [],
                "externalConsole": false,
                "MIMode": "gdb",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    }
                ],
                "preLaunchTask": "build",
                "miDebuggerPath": "/usr/bin/gdb",
                "internalConsoleOptions": "openOnSessionStart"
            }
            ]
        }
    ```