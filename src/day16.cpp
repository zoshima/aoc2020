#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <array>

using namespace std;

struct Range {
  int start;
  int end;
};

const regex kRangePattern("^(.+):\\ (\\d+)-(\\d+) or (\\d+)-(\\d+)");
const int kNumNumbers = 20;

using Ticket = vector<int>;
using RangePair = pair<Range, Range>;
using NumbersArray = array<int, kNumNumbers>;

Ticket my_ticket;
vector<Ticket> nearby_tickets;
vector<RangePair> ranges;
vector<string> range_names;

Ticket GetTicket(const string &s) {
  istringstream ss(s);
  string st;
  Ticket t;

  while (getline(ss, st, ',')) {
    t.push_back(stoi(st));
  }

  return t;
}

void LoadInput() {
  ifstream file("../input/day16.txt");
  string line;
  smatch sm;

  while (getline(file, line) && line.size()) {
    regex_search(line, sm, kRangePattern);

    range_names.push_back(sm[1]);
    ranges.push_back({{stoi(sm[2]), stoi(sm[3])}, {stoi(sm[4]), stoi(sm[5])}});
  }

  getline(file, line); // "your ticket:"
  getline(file, line);

  my_ticket = GetTicket(line);

  getline(file, line);
  getline(file, line); // "nearby tickets:"

  while (getline(file, line)) {
    nearby_tickets.push_back(GetTicket(line));
  }
}

inline const bool Includes(const Range &range, const int &num) {
  for (int i = range.start; i <= range.end; ++i) {
    if (i == num) {
      return true;
    }
  }

  return false;
}

const vector<int> GetRangeIndices(const int &num) {
  vector<int> indices;

  for (int i = 0; i < ranges.size(); ++i) {
    if (Includes(ranges[i].first, num) || Includes(ranges[i].second, num)) {
      indices.push_back(i);
    }
  }

  return indices;
}

const unordered_map<int, vector<vector<int>>> GetValidTickets() {
  unordered_map<int, vector<vector<int>>> valid_tickets;

  for (int i = 0; i < nearby_tickets.size(); ++i) {
    vector<vector<int>> property_indices_map;
    bool is_valid = true;

    for (const auto &ticket_property : nearby_tickets[i]) {
      vector<int> range_indices = GetRangeIndices(ticket_property);

      if (range_indices.size() == 0) {
        // invalid ticket
        is_valid = false;
        break;
      }

      property_indices_map.push_back(range_indices);
    }

    if (is_valid) {
      valid_tickets.insert({i, property_indices_map});
    }
  }

  return valid_tickets;
}

void PopulateIndices(NumbersArray &ordered_indices,
               const array<NumbersArray, kNumNumbers> &range_count_map,
               const int &num_elements, const int target = 1) {
  if (target > kNumNumbers) {
    return;
  }

  for (int i = 0; i < kNumNumbers; ++i) {
    auto range_counts = range_count_map[i];
    auto c = count(range_counts.begin(), range_counts.end(), num_elements);

    if (c == target) {
      for (int j = 0; j < kNumNumbers; ++j) {
        if (range_counts[j] == num_elements) {
          auto it = find(ordered_indices.begin(), ordered_indices.end(), j);

          if (it == ordered_indices.end()) {
            ordered_indices[i] = j;
            break;
          } 
        }
      }
    }
  }

  PopulateIndices(ordered_indices, range_count_map, num_elements, target + 1);
}

int main() {
  LoadInput();

  const auto valid_tickets = GetValidTickets();
  const int num_valid_tickets = valid_tickets.size();

  NumbersArray ordered_indices;
  ordered_indices.fill(-1);

  array<NumbersArray, kNumNumbers> range_count_map; // index: property pos

  for (int i = 0; i < kNumNumbers; ++i) {
    NumbersArray range_counts;
    range_counts.fill(0);

    // populate map
    for (const auto &ticket : valid_tickets) {
      for (const int &range_index : ticket.second[i]) {
        range_counts[range_index] += 1;
      }
    }

    range_count_map[i] = range_counts;
  }

  PopulateIndices(ordered_indices, range_count_map, num_valid_tickets);

  long result = 1;

  for (int i = 0; i < kNumNumbers; ++i) {
    if (range_names[ordered_indices[i]].rfind("departure", 0) == 0) {
      result *= my_ticket[i];
    }
  }

  cout << result << endl;
}
