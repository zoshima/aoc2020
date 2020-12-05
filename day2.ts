declare type Password = {
  policy: { letter: string; min: number; max: number };
  password: string;
};

const input: Password[] = (await Deno.readTextFile("./data/day2.txt"))
  .split("\n")
  .map((s) => {
    const a = s.split(":");
    const b = a[0].split(" ");
    const c = b[0].split("-");

    const letter = b[1];
    const password = a[1].trim();
    const min = Number(c[0]);
    const max = Number(c[1]);

    return {
      policy: {
        letter,
        min,
        max,
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
