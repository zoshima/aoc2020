const input: string[] = (await Deno.readTextFile("./data/day7.txt")).split(
  "\n"
);

const containerMap: { [key: string]: string[] } = {};
const bags: { [key: string]: { [key: string]: number } } = {};

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

  // build container map
  for (const value of values) {
    if (!containerMap[value.key]) {
      containerMap[value.key] = [];
    }

    if (!containerMap[value.key].includes(key)) {
      containerMap[value.key].push(key);
    }
  }

  // build containing map
  bags[key] = values.reduce((prev, curr) => {
    return {
      ...prev,
      [curr.key]: curr.value,
    };
  }, {});
}

function findContainers(bag: string): string[] {
  const containers: string[] = containerMap[bag] || [];
  const length: number = containers.length;

  for (let i = 0; i < length; i++) {
    containers.push(...findContainers(containers[i]));
  }

  return containers;
}

function countContent(bag: string): number {
  let count = 0;

  for (const childBag in bags[bag]) {
    const numChildBags = bags[bag][childBag];

    count += numChildBags + numChildBags * countContent(childBag);
  }

  return count;
}

// const containers = findContainers("shiny gold");
// const containersSet = new Set(containers);

// console.log(containersSet.size);
console.log(countContent("shiny gold"));
