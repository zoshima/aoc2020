const input: number[] = (await Deno.readTextFile("./data/day8.txt"))
  .split("\n")
  .filter((s) => !!s)
  .map((s) => Number(s));

const preample = 25;

function getAddendants(
  num: number,
  index: number
): { a: number; b: number } | null {
  for (let i = index - preample; i < index - 1; i++) {
    if (input[i] >= num) {
      continue;
    }

    for (let j = i + 1; j < index; j++) {
      if (input[j] >= num) {
        continue;
      }

      if (input[i] + input[j] === num) {
        return {
          a: input[i],
          b: input[j],
        };
      }
    }
  }

  return null;
}

for (let i = preample; i < input.length; i++) {
  const num = input[i];

  if (!getAddendants(num, i)) {
    console.log(num);
    Deno.exit();
  }
}

export {};
