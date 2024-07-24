#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int cross(char crosswalk, char side) {
  switch (crosswalk) {
  case 'N':
    // There is a crosswalk on the north side
    return side == 'N' ? 1 : 0;
  case 'S':
    // There is a crosswalk on the south side
    return side == 'N' ? 0 : 1;
  case 'B':
    // There is a crosswalk on both the north and the south side
    return side == 'N' ? 1 : 1;
  default:
    return 0;
  }
}

int main() {
  std::string crosswalks;
  std::cin >> crosswalks;

  // These arrays indicate the minimum number of streets crossed so far...
  std::vector<int> north(crosswalks.size() + 1); // ending on the north side
  std::vector<int> south(crosswalks.size() + 1); // ending on the south side

  north[0] = 0;
  south[0] = 1; // This starts with 1 because Cissi would have to cross the
                // street if she were to start from the south side

  for (size_t i = 0; i < crosswalks.size(); i++) {
    // Either coming from the north side, or the south side
    north[i + 1] = std::min(north[i] + cross(crosswalks[i], 'N'),
                            south[i] + cross(crosswalks[i], 'S') + 1);
    // Similarly...
    south[i + 1] = std::min(south[i] + cross(crosswalks[i], 'S'),
                            north[i] + cross(crosswalks[i], 'N') + 1);
  }

  std::cout << north[crosswalks.size()] << "\n";
}
