#include <iostream>
#include <string>

int main() {
  //Variables
  double earthWeight;
  int planetNumber;
  double planetWeight;
  std::string planetName;

  //Weight Earth Input from user
  std::cout << "What is your car's weight on Earth in Kg.\n";
  std::cin >> earthWeight;
  //Planet Number Input from user
  std::cout << "What Planet would you like to have a long drive on, 1. Mercury, 2. Venus, 3. Mars, 4. Jupiter, 5. Saturn, 6. Uranus, 7. Neptune.\n";
  std::cin >> planetNumber;
  
  //Switch statement for calculation
  switch (planetNumber) {
    case 1:
      planetWeight = earthWeight * 0.378;
      planetName = "Mercury";
      break;
    case 2:
      planetWeight = earthWeight * 0.907;
      planetName = "Venus";
      break;
    case 3:
      planetWeight = earthWeight * 0.377;
      planetName = "Mars";
      break;
    case 4:
      planetWeight = earthWeight * 2.36;
      planetName = "Jupiter";
      break;
    case 5:
      planetWeight = earthWeight * 0.916;
      planetName = "Saturn";
      break;
    case 6:
      planetWeight = earthWeight * 0.889;
      planetName = "Uranus";
      break;
    case 7:
      planetWeight = earthWeight * 1.12;
      planetName = "Neptune";
      break;
    default:
      throw new Error(`Unsupported planetNumber: ${planetNumber}`);
  }
  
  //Output
  std::cout << "Your planet is " << planetName << ". Your car's weight on this planet will be " << planetWeight << "kg\n";
   
   return 0;
}
