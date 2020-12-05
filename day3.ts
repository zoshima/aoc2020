declare type Position = {
  x: number;
  y: number;
};

declare type Strategy = {
  right: number;
  down: number;
};

const input: boolean[][] = (await Deno.readTextFile("./data/day3.txt"))
  .split("\n")
  .map((s) => [...s].map((c) => c === "#"));

const hasTree = (position: Position): boolean => {
  const row = input[position.y];

  const repCount = Math.floor(position.x / row.length);
  const x = position.x - repCount * row.length;

  return row[x];
};

const traverse = (currentPos: Position, strat: Strategy): Position | null => {
  const newPosition = {
    y: currentPos.y + strat.down,
    x: currentPos.x + strat.right,
  } as Position;

  if (newPosition.y >= input.length) {
    return null;
  }

  return newPosition;
};

const strategies: Strategy[] = [
  { right: 1, down: 1 },
  { right: 3, down: 1 },
  { right: 5, down: 1 },
  { right: 7, down: 1 },
  { right: 1, down: 2 },
];

let result = 1;

for (let i = 0; i < strategies.length; i++) {
  const strat = strategies[i];

  let currentPosition: Position | null = { x: 0, y: 0 } as Position;
  let count = 0;

  while (currentPosition) {
    currentPosition = traverse(currentPosition, strat);

    if (currentPosition && hasTree(currentPosition)) {
      count++;
    }
  }

  console.log(strat, count);

  result *= count;
}

console.log(result);

export {};
