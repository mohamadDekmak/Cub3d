# cub3D — Project Plan (m & Antony)

A raycaster in C using MiniLibX, inspired by Wolfenstein 3D. This plan covers what to build, how to structure it cleanly, and how to split the work between two people.

---

## 1. What the project actually asks for

**Goal:** render a first-person 3D view of a maze from a 2D `.cub` map file, using raycasting.

**Mandatory requirements (all must be perfect):**

- Written in C, follows the Norm, no leaks, no crashes (segfault/double free = 0).
- Makefile with rules: `NAME`, `all`, `clean`, `fclean`, `re`, `bonus`. Flags `-Wall -Wextra -Werror`. No relinking.
- Uses MiniLibX. Window must behave smoothly (minimize, switch focus, etc.).
- Takes one argument: a `*.cub` scene file.
- Different wall textures per side: **N, S, E, W**.
- Floor and ceiling each get their own RGB color.
- Controls: **W/A/S/D** move, **← / →** rotate the view, **ESC** quits cleanly, red-cross close button quits cleanly.
- Robust parser: any invalid input → print `Error\n` + an explicit message, then exit cleanly.

**`.cub` file format:**

- 6 elements before the map, in any order, separated by blank lines allowed:
  - `NO`, `SO`, `WE`, `EA` → texture paths
  - `F R,G,B` → floor color (0–255)
  - `C R,G,B` → ceiling color (0–255)
- Map comes **last**. Only chars: `0` (empty), `1` (wall), `N/S/E/W` (player start + facing). Spaces are valid and must be handled. Exactly one player.
- Map **must be closed/surrounded by walls**, or it's an error.

**Bonus (only graded if mandatory is flawless):** wall collisions, minimap, doors, animated sprites, mouse look. Don't touch these until mandatory is 100%.

---

## 2. Build phases (recommended order)

Do these roughly in sequence — each phase produces something testable.

**Phase 0 — Setup (½ day)**
Repo, folder structure, Makefile skeleton, copy `libft`, get MiniLibX compiling, open a blank window that closes on ESC and the red cross. This de-risks the environment before any real code.

**Phase 1 — Parsing (2–3 days)**
Read the `.cub`, extract the 6 elements, validate colors and texture paths, load the map into a 2D grid, validate the map (closed, one player, only legal chars, handle spaces). Every failure prints `Error\n` + message and frees everything. This is where most points are won or lost.

**Phase 2 — Raycasting core (3–4 days)**
DDA algorithm: cast one ray per screen column, find wall hit distance, compute wall slice height, draw floor/ceiling colors. Get a working untextured 3D view first.

**Phase 3 — Player movement & input (1–2 days)**
Hook keys: W/A/S/D move along direction/plane vectors, arrows rotate. Redraw each frame. Keep it smooth.

**Phase 4 — Textures (2 days)**
Load the 4 wall textures via MiniLibX, determine which side each ray hit (N/S/E/W), sample the correct texture column per wall slice. Apply floor/ceiling colors.

**Phase 5 — Polish & leak hunt (1–2 days)**
Free all images, textures, map, and the display on exit. Run `valgrind`, test malformed maps, weird spacing, missing elements, bad RGB, non-`.cub` args. Write the README.

**Phase 6 — Bonus (only if mandatory is perfect)**
Collisions → minimap → doors → sprites → mouse.

---

## 3. Clean code structure

```
cub3d/
├── Makefile
├── README.md
├── includes/
│   └── cub3d.h            # structs, prototypes, macros, enums
├── libft/                 # your libft + its Makefile
├── minilibx/              # if compiling from source
├── maps/                  # test .cub files (valid + invalid)
│   ├── valid/
│   └── invalid/
└── src/
    ├── main.c             # entry: arg check, orchestration
    ├── parsing/
    │   ├── parse_file.c   # read file, dispatch lines to elements/map
    │   ├── parse_elements.c  # NO/SO/WE/EA/F/C
    │   ├── parse_map.c    # build grid, store player
    │   ├── validate_map.c # closed check, one player, char check
    │   └── parse_utils.c
    ├── render/
    │   ├── raycast.c      # DDA loop, per-column
    │   ├── draw.c         # draw wall slice, floor, ceiling
    │   ├── textures.c     # load + sample textures
    │   └── image.c        # pixel put, mlx image buffer helpers
    ├── player/
    │   ├── moves.c        # W/A/S/D translation
    │   └── rotate.c       # arrow rotation
    ├── events/
    │   ├── hooks.c        # key/close hooks
    │   └── loop.c         # render loop callback
    └── utils/
        ├── errors.c       # error print + clean exit
        └── free.c         # free everything
```

**Core data structures (in `cub3d.h`):**

```c
typedef struct s_img {          // one mlx image buffer
    void  *ptr;
    char  *addr;
    int    bpp;
    int    line_len;
    int    endian;
    int    width;
    int    height;
} t_img;

typedef struct s_map {
    char **grid;                // the map as 2D char array
    int    width;
    int    height;
    int    fl_color;            // packed floor RGB
    int    ce_color;            // packed ceiling RGB
    char  *tex_path[4];         // NO, SO, WE, EA
} t_map;

typedef struct s_player {
    double x, y;                // position
    double dir_x, dir_y;        // direction vector
    double plane_x, plane_y;    // camera plane
} t_player;

typedef struct s_game {
    void      *mlx;
    void      *win;
    t_img      frame;           // main render buffer
    t_img      tex[4];          // loaded wall textures
    t_map      map;
    t_player   player;
} t_game;
```

**Rules to keep it clean:** one `t_game *game` passed everywhere (no globals), every allocation has a matching free path, parser never touches rendering and vice-versa, all errors funnel through one `error_exit()`.

---

## 4. Splitting the work with Antony

The natural clean split is **Parser (m)** vs **Renderer (Antony)** — they meet at one shared contract: a fully-populated `t_game`. As long as you both agree on `cub3d.h` up front, you can work in parallel with almost no collisions.

**Together first (Day 1, pair):**
Agree on `cub3d.h` (all structs above), the Makefile, folder structure, and get MiniLibX opening a window. Commit this as the shared foundation. This is the single most important step — the header is your API contract.

| | **m** | **Antony** |
|---|---|---|
| **Owns** | Parsing + validation + memory | Raycasting + rendering + input |
| **Phase 1** | `.cub` reading, element parsing, map grid, closed-map validation, error/free system | Window loop, hooks (ESC + red cross), image buffer helpers (`pixel_put`) |
| **Phase 2** | Test map generator, invalid-map suite, leak checks on parser | DDA raycasting, untextured 3D view, floor/ceiling fill |
| **Phase 3** | Player struct init from map (spawn pos + facing) | W/A/S/D + arrow movement, per-frame redraw |
| **Phase 4** | Texture path validation, help load textures | Texture loading + side detection + column sampling |
| **Phase 5** | Full parser leak/edge audit, write README | Render leak audit (free images/textures) |

**Why this split works:** m guarantees that when the renderer receives `t_game`, the map is valid, closed, textures paths are set, colors packed, and player position/orientation are ready. Antony never has to trust raw input — he trusts the struct. Clear boundary = fewer merge conflicts and easy blame-free debugging.

**Workflow tips:**
- Branch per feature (`git checkout -b parse-map`), small PRs, review each other's code (also good for defense — you must explain each other's work).
- Keep a `maps/invalid/` folder growing as you find edge cases.
- Integrate early: as soon as the parser fills `t_game`, feed it to the renderer even if rendering is basic. Don't wait until the end to connect the halves.
- Run `norminette` and `valgrind` before every merge.

---

## 5. Common failure points to watch (these cost people the eval)

- Map with spaces / non-rectangular map not handled → the closed-map check must treat spaces and edges as open and fail correctly.
- Map not on the last line, or duplicated elements, not rejected.
- Missing one of the 6 elements, or RGB out of `[0,255]`.
- Texture file missing / wrong extension / unreadable.
- Leaks on the *error* paths (people free on success but leak when exiting early).
- Fisheye effect (use perpendicular distance, not euclidean).
- Window not closing cleanly on red cross.

---

## 6. Suggested timeline

Roughly **2 weeks** for a solid mandatory part working ~in parallel:

- Days 1: shared setup (both)
- Days 2–4: parsing (m) ‖ window+raycast skeleton (Antony)
- Days 5–7: raycasting + movement (Antony) ‖ map validation + tests (m)
- Days 8–9: textures (Antony) ‖ texture validation + edge maps (m)
- Days 10–11: integration, leak hunt, README (both)
- Days 12+: bonus only if mandatory is flawless

---

*Note: I'm not 100% certain on exact day estimates — they depend on your pace and how much MiniLibX/math you already know. Treat the timeline as a guide, not a deadline. Everything about the requirements and `.cub` format above is taken directly from your subject PDF (version 12.0).*
