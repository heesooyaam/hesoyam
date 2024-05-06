def load_player_map(filename: str) -> list[list[str]]:
    with open(filename) as f:
        map = [[ch for ch in line if ch in (".", "X")] for line in f]
        if len(map) < 2 or len(map) > 500:
            raise ValueError(f"File {filename} has too few lines")
        if not all([len(line) == len(m[0]) for line in m]):
            raise ValueError(f"File {filename} has lines with different length")
        if len(m[0]) != len(m):
            raise ValueError(f"File {filename} has not square matrix")
        return map


def read_next_turn():
    try:
        x, y = [int(i) for i in input("Enter x y:\n").split(maxsplit=1)]
    except Exception as exc:
        print(f"Error: {exc}")


player1 = load_player_map("player1.txt")
player2 = load_player_map("player2.txt")

if len(player1) != len(player2):
    print("Players should have the same number of rows")
    exit(0)


def read_next_turn() -> tuple[int, int] | None:
    try:
        x, y = [int(i) for i in input("Enter x y:\n").split(maxsplit=1)]
    except Exception as e:
        print(f"Error: {e}")
        raise

    if not (0 < x <= len(player1)):
        print(f"Error: {x} not in range [1, {len(player1)}]")
        raise
    if not (0 < y <= len(player1)):
        print(f"Error: {y} not in range [1, {len(player1)}]")
        raise
    return x, y


def process_turn(target_payer_matrix: list[list[str]], x: int, y: int):
    if target_payer_matrix[x][y] == "X":
        target_payer_matrix[x][y] = "🔥"
    elif target_payer_matrix[x][y] == ".":
        target_payer_matrix[x][y] = "💦"
    else:
        raise ValueError(f"Target cell ({x}, {y}) is not X or .")


def game_is_over():
    player1_lose = not any(ch == "X" for line in player1 for ch in line)
    player2_lose = not any(ch == "X" for line in player1 for ch in line)
    if player1_lose or player2_lose:
        print(f"Player {1 if player1_lose else 2} lose")
    return player1_lose or player2_lose


def game_loop():
    player1_turn = True
    while not game_is_over():
        try:
            x, y = read_next_turn()
            process_turn(player2 if player1_turn else player1, x, y)
        except Exception:
            continue
        player1_turn = not player1_turn








