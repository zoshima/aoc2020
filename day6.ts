const input: string[][] = (await Deno.readTextFile("./data/day6.txt"))
  .split("\n\n")
  .map((p) => p.split("\n"));

const answerMap: { [key: string]: number } = {};

for (const group of input) {
  const localAnswerMap: { [key: string]: number } = {};

  for (const person of group) {
    for (const answer of [...person]) {
      localAnswerMap[answer] = localAnswerMap[answer] + 1 || 1;
    }
  }

  for (const question in localAnswerMap) {
    answerMap[question] = answerMap[question] + 1 || 1;
  }
}

const totalAnswers = Object.values(answerMap).reduce(
  (p: number, c: number) => p + c
);

console.log(totalAnswers);

export {};
