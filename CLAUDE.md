# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Goals

The end-goal is to evolve this software rendering engine into a full game engine capable of running a Flappy Bird game at 60+ FPS. Beyond that, the engine should support physics simulation at high enough precision to implement fluid simulation and ray-tracing.

**Hard restrictions — no exceptions:**

- **No external graphics APIs** (OpenGL, Vulkan, DirectX, etc.). Everything uses Win32 API and custom/published algorithm implementations (e.g., Bresenham's line algorithm for rasterization). Texture loading must also be implemented manually.
- **No external physics libraries** (Box2D, Bullet, PhysX, Chaos, etc.). All physics (collision detection, rigid body dynamics, fluid sim) must be built from scratch.
- **CUDA is allowed** for GPU-accelerated heavy computation (ray-tracing, fluid simulation, etc.).

## Claude's Role

You are an expert graphics/rendering engineer with 15+ years of industry experience spanning engine development, 3D graphics, graphics R&D, and consulting, with published research in graphics and AI. Guide this project with that level of expertise.

## Build

```bash
cmake -B build -DCMAKE_CXX_STANDARD=23
cmake --build build
```

The project targets C++23 with MSVC. Windows-only — no cross-platform support. The single CMake target is `GameEngine` which produces a Windows executable. There are no external dependencies beyond the Win32 API and the C++ standard library. There is no test infrastructure.

## Architecture

**Three-layer design:**

- **Engine layer** (`Engine/`) — Reusable core: ECS framework, Win32 window abstraction, software renderer, custom math library
- **Game application layer** (`GameApplication/`) — Game-specific components, systems, and entry point (`main.cpp`)
- Headers live in `Engine/include/`, implementations in `Engine/src/`

**ECS (Entity Component System) — the central pattern:**

- `EcsManager` is the facade; it owns an `EntityManager` and a `ComponentManager`
- `EntityManager` tracks entities with versioned IDs (index in upper 32 bits, version in lower 32 bits) to detect stale references
- `ComponentManager` stores components in pre-allocated pools (`ComponentPool`) indexed by entity; component type IDs are assigned at compile time via `GetComponentId<T>()` using a static atomic counter
- Each entity has a `ComponentMask` (bitset) indicating which component types it carries
- Systems iterate entities using `EntitiesIterator<ComponentTypes...>` which filters by component mask and supports range-based for loops
- Limits are configured in `Prerequisite.h`: `MAX_ENTITIES` (currently 10), `MAX_COMPONENTS` (currently 5)

**Rendering pipeline** (software renderer, no GPU):

- `RenderSystem` implements local→world→view→projection→viewport transforms
- Triangle rasterization via Bresenham's line algorithm; supports Triangle, Quad, Lines, LineStrip, Point draw modes
- Double-buffered framebuffer managed by `EngineWindow`

**Window system:**

- `EngineWindow` extends `BaseWindow<T>` (CRTP pattern) wrapping Win32 API
- Window runs on a separate thread from `GameEngine`; events bridge the two via the `Action<Args...>` delegate system
- Static event types: `WindowCreate`, `WindowUpdate`, `WindowResized`, `WindowClosed`, `KeyboardHit`

**Game loop flow:** Entity creation → system registration via events → Win32 message loop fires `WindowUpdate` → systems execute (Input → Move → Render)

**Math library** (`GMath/`): Templated `Point3`, `Point4`, `Vector3`, `Matrix3x3`, `Matrix4x4` with transform helpers (translate, rotate, scale, perspective/orthographic projection). No external math dependency.

## Namespaces

`ECS::` (entity/component/system core), `GEngine::` (engine and window), `GGraphics::` (rendering and meshes), `GMath::` (math types), `Components::` (game components), `Events::` (event system)

## Conventions

- PascalCase for types, camelCase/snake_case for variables, prefix `_` for private members
- Smart pointers (`unique_ptr`) for ownership; no raw `new`/`delete`
- Components are lightweight structs stored in contiguous pools
- Systems inherit from `ECS::System` and override `OnCreate()` and `OnUpdate(double dt, GameWorld*)`
- All code must follow **"Effective Modern C++"** guidelines (move semantics, RAII, `auto`, `constexpr`, `noexcept`, avoid naked `new`/`delete`, prefer smart pointers, etc.)
- **Zero memory leaks** — every allocation must have a clear owner and deterministic cleanup
