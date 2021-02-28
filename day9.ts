const input: number[] = (await Deno.readTextFile("./data/day9.txt"))
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

function getContiguousSet(
  num: number
): { set: number[]; min: number; max: number } | null {
  const lim = input.length / 2;

  let setLength = 2;

  do {
    for (let i = 0; i < input.length - setLength; i++) {
      let sum = 0;
      let min = input[i];
      let max = min;

      for (let j = 0; j < setLength; j++) {
        const _num = input[i + j];

        sum += _num;

        if (_num < min) {
          min = _num;
        }

        if (_num > max) {
          max = _num;
        }
      }

      if (sum === num) {
        return {
          set: input.slice(i, i + setLength),
          min: min,
          max: max,
        };
      }
    }
  } while (++setLength < lim);

  return null;
}

for (let i = preample; i < input.length; i++) {
  const num = input[i];

  if (!getAddendants(num, i)) {
    // 127
    const set = getContiguousSet(num);

    if (set) {
      console.log(set, set.min + set.max);
      Deno.exit();
    }
  }
}

export {};
