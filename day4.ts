class Passport {
  [key: string]: any;

  private byr: string = "";
  private iyr: string = "";
  private eyr: string = "";
  private hgt: string = "";
  private hcl: string = "";
  private ecl: string = "";
  private pid: string = "";
  private cid: string = "";

  constructor(passportString: string) {
    const keyValueStrings = passportString.split(" ");

    for (const keyValueString of keyValueStrings) {
      const keyValue = keyValueString.split(":");
      const key = keyValue[0];

      if (this.hasOwnProperty(key)) {
        const value = keyValue[1];

        this[key] = value;
      }
    }
  }

  public isValid(): boolean {
    for (const key of Object.keys(this)) {
      switch (key) {
        case "byr": {
          const value = +this[key];

          if (isNaN(value) || value < 1920 || value > 2002) {
            return false;
          }

          break;
        }
        case "iyr": {
          const value = +this[key];

          if (isNaN(value) || value < 2010 || value > 2020) {
            return false;
          }

          break;
        }
        case "eyr": {
          const value = +this[key];

          if (isNaN(value) || value < 2020 || value > 2030) {
            return false;
          }

          break;
        }
        case "hgt": {
          const value = this[key];
          const unit = value.substring(value.length - 2);
          const measure = +value.substring(0, value.length - 2);

          if (isNaN(measure)) {
            return false;
          }

          switch (unit) {
            case "cm": {
              if (measure < 150 || measure > 193) {
                return false;
              }

              break;
            }
            case "in": {
              if (measure < 59 || measure > 76) {
                return false;
              }

              break;
            }
            default:
              return false;
          }

          break;
        }
        case "hcl": {
          const value = this[key];
          const hexMatches = value.match(/^#[0-9a-f]{6}$/gi);

          if (hexMatches?.length !== 1) {
            return false;
          }

          break;
        }
        case "ecl": {
          const value = this[key];
          const colorMatches = value.match(/^amb|blu|brn|gry|grn|hzl|oth$/g);

          if (colorMatches?.length !== 1) {
            return false;
          }

          break;
        }
        case "pid": {
          const value = this[key];
          const matches = value.match(/^[0-9]{9}$/g);

          if (matches?.length !== 1) {
            return false;
          }

          break;
        }
        case "cid":
          break;
        default:
          return false;
      }
    }

    return true;
  }
}

const input: string[] = (await Deno.readTextFile("./data/day4.txt")).split(
  "\n"
);

const passportStrings: string[] = [];

// parse input into passport strings
{
  let currentIndex = 0;

  for (const _line of input) {
    const line = _line.trim();

    if (line) {
      if (passportStrings[currentIndex]) {
        passportStrings[currentIndex] += " " + line;
      } else {
        passportStrings[currentIndex] = line;
      }
    } else {
      currentIndex++;
    }
  }
}

let count = 0;

for (const passportString of passportStrings) {
  const passport = new Passport(passportString);

  if (passport.isValid()) {
    count++;
  }
}

console.log(count);

export {};
