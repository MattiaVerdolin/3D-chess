# Chessboard Project - SUPSI Graphics Course

## Overview
This project was developed as part of the Graphics course at SUPSI (Scuola universitaria professionale della Svizzera italiana). The goal was to design a **graphics engine** using **OpenGL**, **GLM**, and **FreeGLUT**, followed by integrating interactivity within the scene according to the requirements specified by the professor.

The result is a **chess game simulation**. While the chess logic (rules, turn management, etc.) is not implemented, the focus is on rendering, interaction, and scene management. The project showcases a custom graphics engine capable of handling objects, lights, and interactions with the scene.

---

## Features

### Graphics Engine
- Custom graphics engine built using **OpenGL**, **GLM**, and **FreeGLUT**.
- Dynamic scene rendering.
- Support for multiple cameras.
- Real-time interaction with scene objects.
- Lighting controls for enhanced realism.

### Chessboard Interaction
- A 3D chessboard where pieces can be moved interactively.
- No chess logic, allowing for free placement of pieces.
- Visual representation of interactions between pieces (e.g., "eating" pieces).

---

## Controls
The following controls allow interaction with the chessboard and scene:

- **`C`**: Switch between the available cameras in the scene.
- **Arrow keys (`←`, `→`, `↑`, `↓`)**: Move the dynamic camera.
- **`W`, `A`, `S`, `D`**: Move the selector on the chessboard.
- **`Space`**:
  - Select a piece by positioning the selector over it and pressing `Space`.
  - Move the selected piece by positioning the selector on a target square and pressing `Space` again.
  - If the target square contains another piece, it will be "eaten" (removed from the board).
- **`L`**: Turn the light on or off on the table.

---

## Requirements
To build and run the project, the following libraries are required:

- **OpenGL**
- **GLM**
- **FreeGLUT**
- **FreeImage**

Make sure these libraries are installed on your system before compiling the project.

---

## Building and Running the Project

### Building
1. Navigate to the root directory of the project.
2. Use the provided `Makefile` to build the project:
   ```bash
   make
   ```
3. The output executable will be located in the project directory (e.g., `x64/Debug/`).

### Running
Run the program by providing the path to the scene file (e.g., a `.ovo` file) as an argument:
```bash
./client.exe /path/to/scene.ovo
```

If the project is run using an IDE without specifying a `.ovo` file as a terminal parameter, the program will automatically load the `.ovo` file located in the resources folder (`cg/resources`).

---

## Authors
- **Alessandro Cantoni** (C) SUPSI - [alessandro.cantoni@student.supsi.ch](mailto:alessandro.cantoni@student.supsi.ch)
- **Francesco Fasola** (C) SUPSI - [francesco.fasola@student.supsi.ch](mailto:francesco.fasola@student.supsi.ch)
- **Mattia Verdolin** (C) SUPSI - [mattia.verdolin@student.supsi.ch](mailto:mattia.verdolin@student.supsi.ch)

---

## License
This project was developed for educational purposes as part of the SUPSI Graphics course. Redistribution or use outside the context of the course may require explicit permission from the authors.

