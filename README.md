*Made by braugust and maissat as part of the 42 curriculum.*

Our first 3d video game using the ray-casting Technology. This project is a DOOM-like inspired by *Wolfenstein 3D*, built in C using the MiniLibX graphical library. It explores the concepts of raycasting, window management,
and mathematical projections.

---

## 🚀 Features

* **3D Perspective Rendering**: Real-time raycasting engine to convert a 2D map array into a pseudo-3D graphical view.
* **Textured Walls**: North, South, East, and West walls can have different textures (`.xpm` or `.png` depending on your version).
* **Floor & Ceiling Colors**: Fully customizable using RGB color codes.
* **Smooth Controls**: 
  * `W`, `A`, `S`, `D` keys to move around the maze.
  * Left and Right arrow keys to rotate the camera view smoothly.
  * `ESC` or clicking the window cross closes the application cleanly.
* **Map Parsing**: Parses and validates a `.cub` scene description file, handling error detection for open maps, missing textures, or invalid characters.

---

## 🛠️ Key Concepts Learned

* **Raycasting Mathematics**: Using trigonometry, vectors, and DDA (Digital Differential Analysis) algorithms to calculate ray collisions and wall distances without fish-eye distortion.
* **Graphic Library (MiniLibX)**: Managing windows, hooks, loops, and rendering pixel-by-pixel.
* **Performance Optimization**: Efficient loops and memory layout to ensure smooth rendering.
* **Rigorous Memory & Resource Management**: Handling file parsing safely, ensuring all allocated textures, windows, and structures are properly freed on exit without any memory leaks.

---

## 💻 How to Run it

1. Clone the repository:
```bash
git clone https://github.com/Marr1one/Cub3d.git && cd cub3d
```
2. Compile the project:
```bash
make
```
3. Start Cub3D with a map file:
```bash
./cub3D maps/valid_map.cub
```
