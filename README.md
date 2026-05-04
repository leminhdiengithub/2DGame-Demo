# 🎮 2DGAME-DEMO

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-2.x-red?logoColor=white)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6?logo=windows&logoColor=white)
![Build](https://img.shields.io/badge/build-Makefile%20%2B%20MinGW-yellow)
![Editor](https://img.shields.io/badge/editor-VS%20Code-007ACC?logo=visualstudiocode&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green)

> Dự án game 2D sử dụng **C++** và **SDL2**, build bằng **Makefile + MinGW-w64** trên **Windows**, phát triển với **Visual Studio Code**.

---

## 📋 Mục lục

- [Giới thiệu](#-giới-thiệu)
- [Yêu cầu hệ thống](#-yêu-cầu-hệ-thống)
- [Cài đặt môi trường](#-cài-đặt-môi-trường)
- [Cấu trúc thư mục](#-cấu-trúc-thư-mục)
- [Build & Chạy](#-build--chạy)
- [Cấu hình VS Code](#-cấu-hình-vs-code)
- [Tính năng](#-tính-năng)
- [Đóng góp](#-đóng-góp)
- [Giấy phép](#-giấy-phép)

---

## 🧩 Giới thiệu

**2DGAME-DEMO** được xây dựng bằng **C++17** và thư viện **SDL2**, sử dụng kiến trúc **ECS (Entity-Component-System)** để quản lý game object linh hoạt và hiệu quả.

Dự án được build hoàn toàn trên **Windows** thông qua **MinGW-w64 + Makefile**, không dùng CMake hay Visual Studio IDE.

---

## 💻 Yêu cầu hệ thống

| Thành phần | Yêu cầu |
|---|---|
| OS | Windows 10/11 (64-bit) |
| Trình biên dịch | MinGW-w64 (g++ với C++17) |
| Build tool | GNU Make (mingw32-make) |
| Editor | Visual Studio Code |
| SDL2 | 2.x (đã bundled trong `SDL2-w64/`) |

---

## 📦 Cài đặt môi trường

### 1. Cài MinGW-w64

Tải về tại [winlibs.com](https://winlibs.com/) hoặc [MinGW-w64 releases](https://github.com/niXman/mingw-builds-binaries/releases).

Giải nén và thêm đường dẫn `mingw64\bin` vào **PATH** của hệ thống:

```
Ví dụ: C:\mingw64\bin
```

Kiểm tra cài đặt:

```cmd
g++ --version
mingw32-make --version
```

### 2. Cài Visual Studio Code

Tải tại [code.visualstudio.com](https://code.visualstudio.com/) và cài các extension sau:

- **C/C++** (Microsoft) — IntelliSense, debug
- **C/C++ Extension Pack** (tùy chọn)
- **Makefile Tools** (Microsoft) — hỗ trợ Makefile

### 3. SDL2 (đã tích hợp sẵn)

Thư viện SDL2 đã được bundle trong thư mục `SDL2-w64/` của dự án — **không cần cài thêm**.

---

## 📁 Cấu trúc thư mục

```
2DGAME-DEMO/
├── .vscode/                    # Cấu hình VS Code
│   ├── c_cpp_properties.json   # IntelliSense include paths
│   ├── tasks.json              # Build task (gọi make)
│   └── launch.json             # Debug config
│
├── bin/                        # Output: file .exe sau khi build
│
├── include/                    # Header files (.hpp)
│   ├── ECS/                    # Entity-Component-System
│   ├── Menu/                   # Menu system
│   ├── AssetManager.hpp
│   ├── Collision.hpp
│   ├── Game.hpp
│   ├── GameObject.hpp
│   ├── Map.hpp
│   ├── TextureManager.hpp
│   └── Vector2D.hpp
│
├── res/                        # Tài nguyên game
│   ├── font/                   # Font TTF
│   ├── gfx/                    # Sprite, texture, ảnh
│   └── sounds/                 # Âm thanh, nhạc nền
│
├── SDL2-w64/                   # Thư viện SDL2 prebuilt (Windows 64-bit)
│   ├── include/
│   └── lib/
│
├── src/                        # Source files (.cpp)
│
└── makefile                    # Build script
```

---

## 🔨 Build & Chạy

### Clone repository

```cmd
git clone https://github.com/username/2DGAME-DEMO.git
cd 2DGAME-DEMO
```

### Build bằng Makefile

Mở **Command Prompt** hoặc **Terminal trong VS Code** tại thư mục gốc:

```cmd
mingw32-make
```

File `.exe` sẽ được xuất ra thư mục `bin/`.

### Các lệnh Makefile phổ biến

```cmd
mingw32-make          # Build toàn bộ project
mingw32-make clean    # Xóa file build cũ
mingw32-make run      # Build và chạy luôn
```

### Chạy chương trình

```cmd
bin\2DGAME-DEMO.exe
```

> ⚠️ Đảm bảo các file `.dll` của SDL2 (trong `SDL2-w64\lib\`) nằm cùng thư mục với `.exe` hoặc đã được copy vào `bin\`.

---

## ⚙️ Cấu hình VS Code

### Build từ VS Code (Ctrl+Shift+B)

File `.vscode/tasks.json` mẫu:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build",
      "type": "shell",
      "command": "mingw32-make",
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    },
    {
      "label": "Clean",
      "type": "shell",
      "command": "mingw32-make clean"
    }
  ]
}
```

### IntelliSense — `.vscode/c_cpp_properties.json`

```json
{
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "${workspaceFolder}/include/**",
        "${workspaceFolder}/SDL2-w64/include/**"
      ],
      "defines": ["_DEBUG", "UNICODE"],
      "compilerPath": "C:/mingw64/bin/g++.exe",
      "cppStandard": "c++17",
      "intelliSenseMode": "windows-gcc-x64"
    }
  ],
  "version": 4
}
```

> 💡 Chỉnh `compilerPath` cho đúng với nơi bạn cài MinGW-w64.

---

## ✨ Tính năng

- [x] Kiến trúc ECS (Entity-Component-System)
- [x] Quản lý asset tập trung (`AssetManager`)
- [x] Texture Manager với SDL2 Renderer
- [x] Collision Detection 2D
- [x] Hệ thống Map / Tilemap
- [x] Vector2D math
- [x] Menu system
- [ ] Âm thanh (SDL2_mixer)
- [ ] Animation system
- [ ] Scene Manager

---

## 🤝 Đóng góp

1. Fork repository
2. Tạo branch: `git checkout -b feature/ten-tinh-nang`
3. Commit: `git commit -m "feat: mô tả thay đổi"`
4. Push: `git push origin feature/ten-tinh-nang`
5. Tạo Pull Request

---

## 📄 Giấy phép

Phân phối theo giấy phép **MIT**. Xem file [LICENSE](LICENSE) để biết thêm.

---

<div align="center">
  Made with ❤️ using C++ · SDL2 · MinGW-w64 · VS Code
</div>
