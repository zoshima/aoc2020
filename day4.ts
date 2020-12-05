type Passport = {
  [key: string]: string;
};

const RequiredPassportKeys = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];
const OptionalPassportKeys = ["cid"];

const input: string[] = (await Deno.readTextFile("./data/day4.txt")).split(
  "\n"
);

const passports: Passport[] = [];

// parse input into passport objects
{
  let currentPassport = {} as Passport;
  passports.push(currentPassport);

  for (const _line of input) {
    const line = _line.trim();

    if (line) {
      const kvList = line.split(" ");

      for (const kvString of kvList) {
        const kv = kvString.split(":");

        currentPassport[kv[0]] = kv[1];
      }
    } else {
      currentPassport = {} as Passport;
      passports.push(currentPassport);
    }
  }
}

const isValid = (pass: Passport): boolean => {
  const passportProps = Object.keys(pass);

  if (passportProps.length < RequiredPassportKeys.length) {
    return false;
  }

  for (const requiredProp of RequiredPassportKeys) {
    if (!(passportProps.includes(requiredProp) && !!pass[requiredProp])) {
      return false;
    }
  }

  for (const passportProp of passportProps) {
    if (OptionalPassportKeys.includes(passportProp)) {
      continue;
    }

    if (!RequiredPassportKeys.includes(passportProp)) {
      return false;
    }
  }

  return true;
};

let count = 0;

for (const passport of passports) {
  count += +isValid(passport);
}

console.log(count);

export {};
