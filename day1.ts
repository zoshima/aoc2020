const input: number[] = (await Deno.readTextFile("./data/day1.txt"))
  .split("\n")
  .map((s) => Number(s));

const targetSum = 2020;

for (let j = 0; j < input.length; j++) {
  const _targetSum = targetSum - input[j];
  const cache: number[] = [];

  for (let i = 0; i < input.length; i++) {
    const element = input[i];

    if (cache.includes(_targetSum - element)) {
      console.log(input[j] * element * (_targetSum - element));
      Deno.exit(1);
    } else {
      cache.push(element);
    }
  }
}

export {};
