#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Animal {
    string name;
    string species;
    int birthYear;
    int rarityScore;
    Animal* next;

    Animal(const string& name, const string& species, int birthYear, int rarityScore)
        : name(name), species(species), birthYear(birthYear), rarityScore(rarityScore), next(nullptr) {}
};

class AnimalList {
private:
    Animal* head;

public:
    AnimalList() : head(nullptr) {}

    ~AnimalList() {
        while (head != nullptr) {
            Animal* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addAnimal(const string& name, const string& species, int birthYear, int rarityScore) {
        Animal* newAnimal = new Animal(name, species, birthYear, rarityScore);
        if (head == nullptr) {
            head = newAnimal;
        } else {
            Animal* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newAnimal;
        }
    }

    static bool compareByRarity(const Animal* a, const Animal* b) {
        return a->rarityScore > b->rarityScore;
    }

    void organizeByRarity() {
        vector<Animal*> animals;
        Animal* current = head;
        while (current != nullptr) {
            animals.push_back(current);
            current = current->next;
        }

        sort(animals.begin(), animals.end(), compareByRarity);

        head = animals[0];
        current = head;
        for (size_t i = 1; i < animals.size(); i++) {
            current->next = animals[i];
            current = current->next;
        }

        current->next = nullptr;
    }

    void printAnimals() {
        Animal* current = head;
        while (current != nullptr) {
            cout << "Name: " << current->name << ", Species: " << current->species 
                 << ", Birth Year: " << current->birthYear << ", Rarity Score: " << current->rarityScore << endl;
            current = current->next;
        }
    }

    string getMostCommonAnimal() {
        string mostCommonAnimal;
        int maxCount = 0;
        Animal* current = head;
        while (current != nullptr) {
            string animalName = current->name;
            int count = 0;
            Animal* temp = head;
            while (temp != nullptr) {
                if (temp->name == animalName) {
                    count++;
                }
                temp = temp->next;
            }
            if (count > maxCount) {
                maxCount = count;
                mostCommonAnimal = animalName;
            }
            current = current->next;
        }
        return mostCommonAnimal;
    }

    string getLeastCommonAnimal() {
        string leastCommonAnimal;
        int minCount = numeric_limits<int>::max();
        Animal* current = head;
        while (current != nullptr) {
            string animalName = current->name;
            int count = 0;
            Animal* temp = head;
            while (temp != nullptr) {
                if (temp->name == animalName) {
                    count++;
                }
                temp = temp->next;
            }
            if (count < minCount) {
                minCount = count;
                leastCommonAnimal = animalName;
            }
            current = current->next;
        }
        return leastCommonAnimal;
    }
};

int main() {
    AnimalList animals;

    animals.addAnimal("Simba", "Lion", 1994, 10);
    animals.addAnimal("Nala", "Lioness", 1994, 8);
    animals.addAnimal("Timon", "Meerkat", 1994, 7);
    animals.addAnimal("Pumbaa", "Warthog", 1994, 6);
    animals.addAnimal("Zazu", "Hornbill", 1994, 5);
    animals.addAnimal("Scar", "Lion", 1994, 4);

    animals.organizeByRarity();

    animals.printAnimals();

    string mostCommonAnimal = animals.getMostCommonAnimal();
    string leastCommonAnimal = animals.getLeastCommonAnimal();

    cout << "Most Common Animal: " << mostCommonAnimal << endl;
    cout << "Least Common Animal: " << leastCommonAnimal << endl;

    return 0;
}




