# cub3D — progress & handoff notes

Quick state of the project so it can be picked up on any machine (or by Antony).

## Where we are

**Phase 0 (setup) — DONE.**
- Repo structure, Makefile, shared header, and a window that opens and closes
  cleanly on ESC and the red cross. Builds clean under `-Wall -Wextra -Werror`.
- Confirmed rendering a black 1280x720 window.

## Fresh-machine setup (do this after cloning)

```
git clone https://github.com/mohamadDekmak/Cub3d.git
cd Cub3d
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux && make && cd ..
make
./cub3D maps/valid/simple.cub
```

`minilibx-linux/` is gitignored on purpose — each machine fetches it itself.
Requires (WSL/Ubuntu): `build-essential libx11-dev libxext-dev libbsd-dev`.

## Key decisions made

- **No garbage collector.** Allocations are few and mostly one-time (map grid,
  4 texture paths, temporary parse buffers). Cleanup is handled by `free_game()`
  plus storing every pointer in the `t_game`/`t_map` struct and NULL-init up front.
- **mlx_hook cast:** callbacks are cast `(int (*)(void))(void *)fn` to satisfy
  modern GCC under `-Werror` (MiniLibX uses an old function-pointer style).
- **libft lives in `tt/`** — NOT yet built or linked by the Makefile.
  Must be wired into the Makefile before Phase 1 uses `ft_split` etc.
  (Consider renaming `tt/` -> `libft/` for clarity/eval.)

## Architecture (the contract)

Single `t_game` passed everywhere, no globals. Structs in `includes/cub3d.h`:
- `t_map`  = parser output (grid, w/h, floor/ceiling colors, 4 texture paths)
- `t_player` = position (x,y) + direction vector + camera plane
- `t_img`  = one MLX image buffer (frame + 4 textures)

## Work split (m + Antony)

- **m:** parsing + validation + memory (Phase 1 owner)
- **Antony:** raycasting + rendering + input (Phase 2+ owner)
- Both agree on `cub3d.h` first; meet at a fully-populated `t_game`.

## Next up: Phase 1 — parsing

1. Wire libft (`tt/`) into the Makefile (build + link).
2. Read the `.cub`, parse the 6 elements (NO/SO/WE/EA/F/C), validate.
3. Load map into `grid`, validate it is closed and has exactly one player.
4. On any error: print `Error\n` + message, free everything, exit.

See PLAN.md for the full phase-by-phase plan.
