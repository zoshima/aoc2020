declare type Password = {
  policy: { letter: string; min: number; max: number };
  password: string;
};

const input: Password[] = (await Deno.readTextFile("./data/day2.txt"))
  .split("\n")
  .map((s) => {
    // 17-19 f: cnffsfffzhfnsffttms
    const [, min, max, letter, password] =
      /^(\d+)-(\d+) (\w{1}): (\w+)$/.exec(s) || [];

    return {
      policy: {
        letter,
        min: +min,
        max: +max,
      },
      password,
    };
  });

const isValid = (pw: Password): number => {
  const matchA = pw.password[pw.policy.min - 1] === pw.policy.letter;
  const matchB = pw.password[pw.policy.max - 1] === pw.policy.letter;

  return +matchA ^ +matchB;
};

let count = 0;

for (let i = 0; i < input.length; i++) {
  const element = input[i];

  count += isValid(element);
}

console.log(count);

export {};
