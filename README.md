# 🖥️ LC3 Simulator

The project is an LC3 Simulator, which includes both an assembler and a hardware simulator for the LC3 architecture. The LC3 (Little Computer 3) is a simple educational computer architecture used to teach computer organization and assembly language programming.

> **Note:** This project is still under development and may not be fully functional. in soon we will release the first version.

## 📥 Getting Started

1. prerequisites

    - QT6.7

2. clone the repository

    If you have [Git](https://git-scm.com/) installed:

    ```bash
    git clone https://github.com/Mr-MRF-Dev/LC3-Simulator.git
    ```

    If you have [GitHub CLI](https://cli.github.com/) installed:

    ```bash
    gh repo clone Mr-MRF-Dev/LC3-Simulator
    ```

    Navigate to the Project Directory

    ```bash
    cd LC3-Simulator
    ```

3. Build the Project

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4. Run the Project

    ```bash
    ./LC3-Simulator
    ```

<!--

### 🛠️ Building on Windows

1. Install [CMake](https://cmake.org/download/) and [MinGW](https://sourceforge.net/projects/mingw-w64/). Make sure to add the MinGW bin directory to your system PATH.
2. Install [QT6](https://www.qt.io/download) and add the bin directory to your system PATH.
3. Clone the repository and navigate to the project directory.

-->

### ⌨️ Code With VS Code

1. Install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension for Visual Studio Code.

2. install the [Qt for VS Code](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.qt&ssr=false#overview) extension for Visual Studio Code.
3. Add the QT root path in the QT extension settings.

4. Press `Ctrl + Shift + P` and select `CMake: Configure` to configure the project.

5. Press `Ctrl + Shift + P` and select `CMake: Build` to build the project.

## 📁 Folder Structure

The project directory is structured as follows:

```plaintext
LC3-Simulator/
├── build/              # Directory for build output
├── src/                # Source code for the simulator and assembler
│   ├── main/           # Gui Main application code (Qt)
│   ├── Assembly/       # Assembly language code
│   ├── Assembler/      # Assembler-specific code
│   └── simulator/      # Simulator-specific code
├── CMakeLists.txt      # CMake build configuration file
└── README.md           # Project README file
```

## 🤝 Contributing

We welcome any contributions you may have. If you're interested in helping out, please fork the repository and create an [Issue](https://github.com/Mr-MRF-Dev/LC3-Simulator/issues) or [Pull Request](https://github.com/Mr-MRF-Dev/LC3-Simulator/pulls). We'll be happy to review your contributions.

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
