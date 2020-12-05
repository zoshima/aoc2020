const input: string[] = (await Deno.readTextFile("./data/day5.txt")).split(
  "\n"
);

const parseSequence = (
  seq: string,
  lowerBound: number,
  upperBound: number,
  lowerBoundMk: "B" | "R",
  upperBoundMk: "F" | "L",
  round: (n: number) => number
): number => {
  let min = lowerBound;
  let max = upperBound;

  for (const char of [...seq]) {
    const increment = round((max - min) / 2);

    switch (char) {
      case upperBoundMk:
        max -= increment;
        break;
      case lowerBoundMk:
        min += increment;
        break;
      default:
        return -1;
    }
  }

  return round(min);
};

const ids: number[] = [];

for (const sequence of input) {
  const row = parseSequence(
    sequence.substring(0, 7),
    0,
    127,
    "B",
    "F",
    Math.round
  );
  const column = parseSequence(
    sequence.substring(7),
    0,
    7,
    "R",
    "L",
    Math.round
  );

  const id = row * 8 + column;

  // if (row !== 0 && row !== 127) {
  ids.push(id);
  // }
}

const sortedIds = ids.sort();
for (let i = 0; i < sortedIds.length; i++) {
  const id = sortedIds[i];
  const nextId = sortedIds[i + 1];

  if (nextId - id !== 1) {
    console.log(id + 1);
    Deno.exit();
  }
}

export {};
