# Battleship Game - README

## 🚢 Battleship Game Overview

This is a complete Battleship game where you play against the computer. It features:
- An 8×8 grid for both player and the computer
- 7 types of ships with different lengths
- Colourful console display showing hits/misses
- Proper ship placement validation
- Turn-based gameplay until all ships are sunk

## 📄 About comp_placements.txt
This text file contains 6 different pre-set ship arrangements for the computer. Each block represents one complete setup. It gives the computer ready-to-use ship placements and ensures valid configurations.

### File Rules:
- **6 blocks** (separated by blank lines)
- **7 ships per block** (one for each ship type)
- **Format for each line**: `[Symbol] [Row] [Col] [H/V]`
  - Symbols: C, T, B, R, S, D, A
  - Coordinates: 0-7 (8×8 grid)
  - H = Horizontal, V = Vertical

### Example Block:
```
C 0 0 H  ← 5-length Carrier at top-left, going right
T 2 0 V  ← 4-length Tank below Carrier, going down
B 1 1 V  ← 4-length Battleship, going down
R 2 3 H  ← 3-length Cruiser in middle, going right
S 5 5 V  ← 3-length Submarine near bottom-right, going down
D 7 2 H  ← 2-length Destroyer at bottom, going right
A 6 6 H  ← 2-length Boat near the corner, going right
```

The game randomly selects one of these 6 blocks for the computer's ship placement, ensuring varied gameplay while maintaining valid configurations.
