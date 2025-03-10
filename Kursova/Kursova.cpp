#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Car {
    string brand;
    string model;
    int year;
    string registration_number;
    int power;
    string status;
    Car* next;
};

Car* head = nullptr;
Car* p = nullptr;

void addCars(int& carCount, int numCarsToAdd) {
    for (int i = 0; i < numCarsToAdd; i++) {
        Car* newCar = new Car();

        cout << "Car: " << i + 1 << ":" << endl;

        cout << "Brand: ";
        cin >> newCar->brand;

        cout << "Model: ";
        cin >> newCar->model;

        cout << "Year: ";
        cin >> newCar->year;

        cout << "Registration number: ";
        cin >> newCar->registration_number;

        cout << "Power: ";
        cin >> newCar->power;

        cout << "Status: ";
        cin >> newCar->status;

        newCar->next = nullptr;

        if (!head) {
            head = newCar;
        }
        else {
            Car* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newCar;
        }
        carCount++;
    }
}

void deleteFromEnd() {
    if (!head) {
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    p = head;
    while (p->next->next) {
        p = p->next;
    }
    delete p->next;
    p->next = nullptr;
}

void deleteFromBeginning() {
    if (!head) {
        return;
    }
    p = head;
    head = head->next;
    delete p;
}

void displayList() {
    p = head;
    while (p) {
        cout << "Marka: " << p->brand << "\nModel: " << p->model << "\nGodina: " << p->year
            << "\nRegistracionen nomer: " << p->registration_number << "\nMoshtnost: " << p->power
            << "\nStatus: " << p->status  << endl;
        p = p->next;
    }
}

void sortLinkedListByPower(Car* head) {
    if (head == NULL) {
        return;
    }

    Car* current = head;
    Car* index = NULL;

    while (current != NULL) {
        index = current->next;

        while (index != NULL) {
            if (current->power < index->power) {
                
                swap(current->brand, index->brand);
                swap(current->model, index->model);
                swap(current->year, index->year);
                swap(current->registration_number, index->registration_number);
                swap(current->power, index->power);
                swap(current->status, index->status);
               
            }
            index = index->next;
        }
        current = current->next;
    }
}

Car* binarySearchByYear(Car arr[], int size, int year) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].year == year) {
            return &arr[mid];
        }
        else if (arr[mid].year < year) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return nullptr;
}

void sortArrayByYear(Car arr[], int size) {
    for (int i = 1; i < size; i++) {
        Car key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].year > key.year) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void findAndDisplayByYear(int year) {
    Car arr[10]; 
    int size = 0;
    Car* p = head;

    
    while (p && size < 10) {
        arr[size++] = *p;
        p = p->next;
    }

    
    sortArrayByYear(arr, size);

    
    Car* result = binarySearchByYear(arr, size, year);
    if (result) {
        cout << "Namerena kola ot " << year << " godina: " << result->brand << " " << result->model << endl;
    }
    else {
        cout << "Nqma namerena kola ot " << year << " godina." << endl;
    }
}

void findAndDisplayMostPowerful() {
    if (!head) return;

    Car* mostPowerful = head;
    p = head->next;

    while (p) {
        if (p->power > mostPowerful->power) {
            mostPowerful = p;
        }
        p = p->next;
    }

    cout << "Nai-moshtnata kola e: " << mostPowerful->brand << " " << mostPowerful->model
        << " s moshtnost " << mostPowerful->power << " hp." << endl;
}

void sortFirst10ByOddEven() { 
    Car* current = head;
    int count = 0;
    Car arr[10];

    while (current && count < 10) {
        arr[count] = *current;
        current = current->next;
        count++;
    }

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 1; i <= count - 2; i += 2) {
            if (arr[i].power > arr[i + 1].power) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
        for (int i = 0; i <= count - 2; i += 2) {
            if (arr[i].power > arr[i + 1].power) {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }

    cout << "Purvite 10 koli podredeni po odd-even sort: ";
    for (int i = 0; i < count; i++) {
        cout << "Marka: " << arr[i].brand << "\nModel: " << arr[i].model << "\nGodina : " << arr[i].year
            << "\nRegistracionen nomer: " << arr[i].registration_number << "\nMoshtnost: " << arr[i].power
            << "\nStatus: " << arr[i].status << endl;
    }
    cout << endl;
}

void SelectionSortByRegistrationNumber() { 
    int count = 0;
    p = head;
    while (p) {
        if (p->status == "free") {
            count++;
        }
        p = p->next;
    }

    
    Car freeCars[10]; 
    int index = 0;
    p = head;
    while (p && index < 10) {
        if (p->status == "free") {
            freeCars[index++] = *p; 
        }
        p = p->next;
    }

  
    for (int i = 0; i < index - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < index; j++) {
            if (freeCars[j].registration_number < freeCars[min_idx].registration_number) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(freeCars[i], freeCars[min_idx]);
        }
    }

    cout << "Svobodni koli, podredeni po reg. nomer:\n";
    for (int i = 0; i < index; ++i) {
        cout << freeCars[i].brand << " " << freeCars[i].model << " - " << freeCars[i].registration_number << endl;
    }
}

void insertionSort(Car arr[], int size) {
    for (int i = 1; i < size; ++i) {
        Car key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].power < key.power) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void InsertionByBrandAndModel() { //insertion
    string brand, model;
    cout << "Vuvedi marka: ";
    cin >> brand;
    cout << "Vuvedi model: ";
    cin >> model;

    int count = 0;
    Car* p = head;
    while (p) {
        if (p->brand == brand && p->model == model) {
            count++;
        }
        p = p->next;
    }

    if (count > 10) {
        cout << "Namerenite koli nadvishavat maksimalniq broi ot 10." << endl;
        return;
    }

    Car carsByBrandAndModel[10]; 
    int index = 0;
    p = head;
    while (p && index < count) {
        if (p->brand == brand && p->model == model) {
            carsByBrandAndModel[index++] = *p;
        }
        p = p->next;
    }

    insertionSort(carsByBrandAndModel, count);

    cout << "Koli s marka " << brand << " i model " << model << ":\n";
    for (int i = 0; i < count; ++i) {
        cout << "Marka: " << carsByBrandAndModel[i].brand << "\nModel: " << carsByBrandAndModel[i].model
            << "\nGodina: " << carsByBrandAndModel[i].year << "\nRegistracionen nomer: " << carsByBrandAndModel[i].registration_number
            << "\nMoshtnost: " << carsByBrandAndModel[i].power << "\nStatus: " << carsByBrandAndModel[i].status
            << endl;
    }
}

void showSubMenu() {
    int choice;
      do {
            cout << "Podmenyu:\n";
            cout << "1. Izvejdane na svobodni koli podredeni po registracionen nomer\n";
            cout << "2. Izvejdane na koli po marka i model\n";
            cout << "3. Izhod\n";
            cout << "Izberi: ";
            cin >> choice;

            switch (choice) {
            case 1:
                SelectionSortByRegistrationNumber();
                break;
            case 2:
                InsertionByBrandAndModel();
                break;
            case 3:
                cout << "Izlizaneto e izvursheno.\n";
                break;
            default:
                cout << "Nevaliden izbor! Molya, opitai otnovo.\n";
            }
      } while (choice != 3);
}

int main() {
    int choice;
    int carCount;

    do {
        cout << "1. Dobavi kola v nachaloto\n";
        cout << "2. Iztrii kola ot kraq\n";
        cout << "3. Iztrii kola ot nachaloto\n";
        cout << "4. Pokaji spisuk\n";
        cout << "5. Sortirai spisuka po moshtnost\n";
        cout << "6. Tursi kola po godina i sortira\n";
        cout << "7. Pokaji nai-moshtnata kola\n";
        cout << "8. Sortirai purvite 10 koli po odd-even sort(bez izvejdane)\n";
        cout << "9. PodMenu\n";
        cout << "0. Izhod\n";
        cout << "Izberi opciq: ";
        cin >> choice;

        switch (choice) {
        case 1:
            int numCarsToAdd;
            cout << "Enter the number of cars to add: ";
            cin >> numCarsToAdd;
            addCars(carCount, numCarsToAdd);
            break;
        case 2:
            deleteFromEnd();
            break;
        case 3:
            deleteFromBeginning();
            break;
        case 4:
            displayList();
            break;
        case 5:
            sortLinkedListByPower(head);
            cout << "=== Spisukut e sortirani po moshtnost. ===\n";
            displayList();
            break;
        case 6:
            int year;
            cout << "Vuvedi godina: ";
            cin >> year;
            cout << "...Izvejdane: (binary search algorithm)...\n";
            findAndDisplayByYear(year);
            break;
        case 7:
            findAndDisplayMostPowerful();
            break;
        case 8:
            cout << ".....Sortirane......"<<endl;
            sortFirst10ByOddEven();
            break;
        case 9:
            showSubMenu();
            break;
        case 0:
            break;
        default:
            cout << "Nevalidna opciq. Opitai pak.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
