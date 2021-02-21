const input: string[] = (await Deno.readTextFile("./data/day7.txt")).split(
  "\n"
);

const containerMap: { [key: string]: string[] } = {};

for (const line of input) {
  if (!line) {
    continue;
  }

  const cols = line.split(/ bag[s]? /g);

  const key = cols[0].trim(); // ex. [ "dull magenta", "contain 5 dim plum bags, 5 dark coral bags. ]
  const values = ((cols[1].match(/[0-9]+.*?(?=bag)/g) as string[]) || []) // ex [ "5 dim plum ", "5 dark coral " ]
    .map((value: string) => {
      const fwc = value.indexOf(" ");

      return {
        key: value.substring(fwc).trim(),
        value: Number(value.substring(0, fwc)),
      };
    });

  for (const value of values) {
    if (!containerMap[value.key]) {
      containerMap[value.key] = [];
    }

    if (!containerMap[value.key].includes(key)) {
      containerMap[value.key].push(key);
    }
  }
}

function findContainers(bag: string): string[] {
  const containers: string[] = containerMap[bag] || [];
  const length: number = containers.length;

  for (let i = 0; i < length; i++) {
    containers.push(...findContainers(containers[i]));
  }

  return containers;
}

const containers = findContainers("shiny gold");
const containersSet = new Set(containers);

console.log(containersSet.size);
