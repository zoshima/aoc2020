declare type Position = {
  x: number;
  y: number;
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

const traverse = (currentPos: Position): Position | null => {
  const newPosition = {
    y: currentPos.y + 1,
    x: currentPos.x + 3,
  } as Position;

  if (newPosition.y >= input.length) {
    return null;
  }

  return newPosition;
};

let currentPosition: Position | null = { x: 0, y: 0 } as Position;
let count = 0;

while (currentPosition) {
  currentPosition = traverse(currentPosition);

  if (currentPosition && hasTree(currentPosition)) {
    count++;
  }
}

console.log(count);

export {};
