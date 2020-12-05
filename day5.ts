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

let highestId = 0;

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

  if (id > highestId) {
    highestId = id;
  }
}

console.log(highestId);

export {};
