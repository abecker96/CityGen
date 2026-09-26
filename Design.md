# City Generator Design

## Purpose

This project is a C++ city generator. The long-term goal is believable urban layouts. The first version will generate terrain, generate a road sentence with an L-system, and render both interactively. Each part should leave room for later realism without requiring a large rewrite.

## Features

### Initial Prototype

1. Accept a seed and generation settings as program input.
2. Generate a terrain heightmap using seeded Perlin noise.
3. Generate a road-development sentence from an L-system:
   - Start from an axiom.
   - Repeatedly apply a grammar for a deterministic number of iterations.
   - Produce a final sentence representing the road map.
4. Interpret and render the road sentence over the terrain.
5. Provide an interactive 3D viewer with WASD movement and mouse look.

At this stage, terrain and roads will be intentionally independent. Roads may cross water-like low ground or steep terrain because the terrain only contains height values and the road grammar does not inspect it yet. Later work can use terrain samples when selecting and extending roads.


### Road Representation

The L-system output is the source representation of the generated road map. A turtle-style interpreter can convert its symbols into road segments and turns for rendering.

I want the grammar to be data-driven where practical. Rules, iteration count, branch angles, and segment lengths will be configurable rather than compiled into the interpreter. This should make it possible to model different city styles without replacing the central pipeline.

The road model will eventually need more than drawable line segments. Useful later metadata includes road class, width, parent road, generation depth, and endpoints. The first prototype can keep this minimal.

### Later City Generation

Once terrain and road generation are reliable, I want to use their outputs for further city-generation passes. Possible directions include:

- Project roads to a flat 2D planning space, find intersections, and partition the enclosed or nearby space into developable areas.
- Assign broad zones before placing buildings. For example, industrial areas may be separated from residential areas by commercial or office areas, while municipal and commercial areas should remain reasonably accessible from housing.
- Create building placement rules for empty space between roads.
- Experiment with a separate density or building-height map as a simple first building-placement signal.
- Feed terrain constraints into road growth so roads avoid water, react to slope, and eventually follow land features.
- Extend terrain with explicit features such as rivers, ponds, coastlines, and forests rather than relying only on height noise.
- Futher refine terrain map with erosion simulation.

The eventual goal is a layered system of constraints and incentives. The result should respond to terrain, access, land use, and existing infrastructure.

### Export

I want generated terrain, roads, and future city geometry to be exportable for inspection in other tools. I will prefer an established format over a custom format:

- Start with Wavefront OBJ for simple static geometry and broad compatibility.
- Consider glTF later when materials, scene structure, or richer metadata become important.

## Technologies

### Language and Build

- Use modern C++, initially targeting C++23 unless a dependency requires otherwise.
- Use CMake as the build system.
- Enable `-Wall` and treat compiler warnings as priorities.
- Prefer the STL for containers, algorithms, ownership, timing, random-number engines, and file handling before adding utility dependencies.

### Rendering and Input

- Use OpenGL for rendering and GLFW for window creation, input, and OpenGL context management.
- Use GLAD or another focused OpenGL loader for function loading.
- Use GLSL shaders kept in separate source files.
- Start with simple terrain meshes and line-based road rendering.

### Testing and Diagnostics

- Unit-test deterministic, non-graphics code: seed handling, noise sampling, L-system rule application, sentence iteration, and road interpretation.
- Use a lightweight C++ test framework like Catch2 or GoogleTest.
- Keep at least one known seed and expected result for each deterministic stage. Full geometry snapshots can be large, so compare stable hashes or key samples instead.

## Determinism

Given the same seed, generation settings, program version, and platform assumptions, the generator should create the same city every time. This is a core project requirement.

- Pass a seeded random-number engine through generation stages instead of using global randomness.
- Never seed from the current time during normal generation.
- Define an explicit seed type and store it with exported output and debug captures.
- Keep iteration order stable. Avoid depending on unordered-container traversal when it affects generated output.
- Version generation settings and grammar definitions so a saved seed remains meaningful as the project changes.
- Be cautious with floating-point differences across compilers and platforms.

## Data Flow and Boundaries

Generation stages will exchange plain data structures and will remain independent of the renderer. The current intended boundaries are:

```text
Generation settings + seed
		-> Heightmap
		-> L-system sentence
		-> Road graph / road segments
		-> Renderable meshes and export data
```

This separation will allow generation to be tested without a graphics context, the renderer to be replaced later, and city-generation stages to be added between roads and renderable geometry.

## Open Questions

- Which L-system symbols and grammar format best support both early rendering and a later road graph?
- How should roads react to steep slopes, water, and terrain boundaries when terrain-aware growth is introduced?
- Should zoning begin as rule-based labels, a density field, or a parceling pass driven by the road graph?
