#include <cstdio>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "source/MyArray.cpp"
#include "source/MyList.cpp"
#include "source/MyHeap.cpp"
#include "source/MyBST.cpp"

using namespace std;

// funkcje sterujące
void handleData();
void handleArray();
void handleList();
void handleHeap();
void handleBST();

// Zmienne wykorzystywane w całym programie
long long int frequency, start, elapsed;
string file_name = "input.txt";
int *test_data = nullptr;
int test_data_size = 0;
int val = 0;

bool printStructures = true;

/**
 * Sprawdzenie, czy plik istnieje
 */
bool fileExists(std::string filename) {
    std::ifstream file(filename.c_str());
    if (file) {
        return true;
    }
    return false;
}

/**
 * Pobranie czasu systemowego, źródło: antoni.sterna.staff.iiar.pwr.edu.pl
 */
//-------------------------------------------------------------------------
long long int read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}
//-------------------------------------------------------------------------

char menu_header[] = "\n### Projekt SDiZO, PWR 2023 ###    \n### Autor:  Jacek Bogdański ###\n\n";
char menu_1[] = "# MENU PROGRAMU:\n#   1. Tablica          \n#   2. Lista          \n#   3. Kopiec binarny           \n#   4. Drzewo BST     \n#   9. Dane wejściowe\n#   0. Koniec                 \n\nWybierz z listy: ";
char menu_array[] = "# OPERACJE: \n#   1. Dodaj na poczatku\n#   2. Dodaj na koncu \n#   3. Dodaj na dowolnej pozycji\n#   4. Usuń z poczatku\n#   5. Usuń z końca  \n#   6. Usuń z dowolnej pozycji\n#   7. Szukaj\n#   0. Powrot\n\nWybierz z listy: ";
char menu_heap[] = "# OPERACJE:  \n#   1. Dodaj element    \n#   2. Usun korzen    \n#   3. Wyszukaj element         \n#   0. Powrot         \n\nWybierz z listy: ";
char menu_bst[] = "\n# OPERACJE: \n#   1. Dodaj element    \n#   2. Szukaj elementu\n#   3. Usuń element             \n#   0. Powrot         \n\nWybierz z listy: ";
char menu_data[] = "# OPERACJE:  \n#   1. Wybierz plik     \n#   2. Wygeneruj plik \n#   3. Wczytaj dane z pliku     \n#   4. Wyczyść dane   \n#   0. Powrot        \n\nWybierz z listy: ";

/**
 * Ładowanie danych z pliku do tablicy test_data
 */
void readTestData() {
    std::ifstream file(file_name.c_str());
    test_data_size = 0;
    if (file.is_open()) {
        file >> test_data_size;
        if (file.fail()) {
            cout << "Błąd odczytu danych" << endl;
            test_data_size = 0;
        } else {
            test_data = new int[test_data_size];
            for (int i = 0; i < test_data_size; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "Błąd odczytu danych" << endl;
                    break;
                } else {
                    test_data[i] = val;
                }
            }
        }
        file.close();
    } else {
        cout << "File error - OPEN" << endl;
    }
}

/**
 * Główna funkcja
 * @return
 */
int main() {
    // Autor: Jacek Bogdański, 263895

    // Menu
    // 1. tablica
    // 2. lista
    // 3. kopiec binarny
    // 4. drzewo BST
    // 0. exit

    SetConsoleOutputCP(CP_UTF8);
    int input;

    // pętla menu głównego
    while (true) {
        system("cls");
        printf("%s", menu_header);

        printf("Plik: %s\n", file_name.c_str());
        printf("Rozmiar wczytanych danych: %d\n\n", test_data_size);

        // pokazanie menu 1
        printf("%s", menu_1);

        // pobranie 1
        scanf("%d", &input);
        fflush(stdin);

        switch (input) {
            case 0:
                printf("%s", "\nProgram zakonczony.\n");
                return 0;
            case 1:
                // tablica
                handleArray();
                break;
            case 2:
                // lista
                handleList();
                break;
            case 3:
                // kopiec
                handleHeap();
                break;
            case 4:
                // drzewo bst
                handleBST();
                break;
            case 9:
                // wczytywanie, generowanie danych
                handleData();
                break;
        }
    }

    return 0;
}

/**
 *
 */
void handleData() {
    // pętla menu
    while (true) {
        system("cls");
        printf("%s", "\n# Dane wejściowe\n\n");
        printf("Plik: %s\n", file_name.c_str());
        printf("Rozmiar wczytanych danych: %d\n\n", test_data_size);
        // pokazanie menu danych wejsciowych
        printf("%s", menu_data);
        int input;
        scanf("%d", &input);
        fflush(stdin);

        char tmp[] = "";
        int n;

        switch (input) {
            case 0:
                return;
            case 1:
                // ładowanie pliku o innej nazwie
                printf("%s", "\nPodaj nazwę pliku: ");
                scanf("%s", tmp);
                fflush(stdin);

                if (!fileExists(tmp)) {
                    printf("%s", "\nPlik nie istnieje!\n\n");
                } else {
                    file_name = tmp;
                    readTestData();

                    printf("%s", "\nPlik został załadowany. \n\n");
                }
                return;

            case 3:
                // ładowanie danych z ustawionego pliku
                readTestData();
                printf("%s", "\nPlik został załadowany. \n\n");
                return;

            case 4:
                // czyszczenie zapamietanych danych
                delete test_data;
                test_data = nullptr;
                test_data_size = 0;
                printf("%s", "\nDane zostały wyczyszczone. \n\n");
                return;

            case 2:
                // generowanie danych
                printf("%s", "\nPodaj ilość liczb: ");
                scanf("%d", &n);
                fflush(stdin);

                ofstream file;
                file.open(file_name);
                file << n << "\n";

                for (int i = 0; i < n; i++) {
                    file << (rand() * rand()) % INT_MAX << "\n";
                }

                file.close();
                readTestData();
                printf("%s", "\nPlik został utworzony i załadowany. \n\n");
                return;
        }
    }
}

// Sprawdzenie struktury

void handleArray() {
    MyArray array(test_data, test_data_size);
    int input;
    int value;
    int index;
    QueryPerformanceFrequency((LARGE_INTEGER * ) & frequency);

    // pętla menu
    while (true) {
        system("cls");
        printf("%s", "\n# Tablica\n\n");
        if(printStructures)
            printf("%s\n\n", array.toString().c_str());
        // pokazanie menu tablicy
        printf("%s", menu_array);

        scanf("%d", &input);
        fflush(stdin);

        switch (input) {
            case 0:
                array.destroy();
                return;

            case 1:
                // dodanie na poczatku
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                array.prepend(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 2:
                // dodanie na koncu
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                array.append(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 3:
                // dodanie na dowolnej pozycji
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);

                start = read_QPC();
                array.put(value, index);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 4:
                // usuniecie z poczatku
                start = read_QPC();
                array.shift();
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 5:
                // usuniecie z konca
                start = read_QPC();
                array.pop();
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 6:
                // usuniecie z dowolnej pozycji
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);

                start = read_QPC();
                array.remove(index);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 7:
                // wyszukiwanie
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                index = array.search(value);
                elapsed = read_QPC() - start;

                if (index == -1) {
                    printf("%s\n", "\nNie odnaleziono.");
                } else {
                    printf("%s %d\n", "\nOdnaleziono pod indeksem:", index);
                }

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;
        }
    }
};

void handleList() {
    MyList list(test_data, test_data_size);
    int input;
    int value;
    int index;
    QueryPerformanceFrequency((LARGE_INTEGER * ) & frequency);

    // pętla menu
    while (true) {
        system("cls");
        printf("%s", "\n# Lista\n\n");
        if(printStructures)
            printf("%s\n", list.toString().c_str());
        // pokazanie menu listy
        printf("%s", menu_array);

        scanf("%d", &input);
        fflush(stdin);

        switch (input) {
            case 0:
                list.destroy();
                return;

            case 1:
                // dodanie na poczatku
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                list.prepend(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 2:
                // dodanie na koncu
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                list.append(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 3:
                // dodanie na dowolnej pozycji
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);

                start = read_QPC();
                list.put(value, index);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 4:
                // usuniecie z poczatku
                start = read_QPC();
                list.shift();
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 5:
                // usuniecie z konca
                start = read_QPC();
                list.pop();
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 6:
                // usuniecie z dowolnej pozycji
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);

                start = read_QPC();
                list.remove(index);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 7:
                // wyszukiwanie
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                index = list.search(value);
                elapsed = read_QPC() - start;

                if (index == -1) {
                    printf("%s\n", "\nNie odnaleziono.");
                } else {
                    printf("%s %d\n", "\nOdnaleziono pod indeksem:", index);
                }

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;
        }
    }
};

void handleHeap() {
    MyHeap heap(test_data, test_data_size);
    int input;
    int value;
    int index;
    QueryPerformanceFrequency((LARGE_INTEGER * ) & frequency);

    // pętla menu
    while (true) {
        system("cls");
        printf("%s", "\n# Kopiec binarny\n");
        if(printStructures)
            heap.printHeap();

        // pokazanie menu kopca
        printf("%s", menu_heap);

        scanf("%d", &input);
        fflush(stdin);

        switch (input) {
            case 0:
                heap.destroy();
                return;

            case 1:
                // dodanie elementu
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                heap.add(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 2:
                // usuniecie korzenia
                start = read_QPC();
                heap.removeRoot();
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 3:
                // wyszukiwanie
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                index = heap.search(value);
                elapsed = read_QPC() - start;

                if (index == -1) {
                    printf("%s\n", "\nNie odnaleziono.");
                } else {
                    printf("%s %d\n", "\nOdnaleziono pod indeksem:", index);
                }

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;
        }
    }
};

void handleBST() {
    MyBST bst(test_data, test_data_size);
    int input;
    int value;
    int index;
    QueryPerformanceFrequency((LARGE_INTEGER * ) & frequency);

    // pętla menu
    while (true) {
        system("cls");
        printf("%s", "\n# Drzewo BST\n");
        if(printStructures)
            bst.printBST();

        // pokazanie menu kopca
        printf("%s", menu_bst);

        scanf("%d", &input);
        fflush(stdin);

        switch (input) {
            case 0:
                bst.destroy();
                return;

            case 1:
                // dodanie elementu
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                bst.add(value);
                elapsed = read_QPC() - start;

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 2:
                // wyszukiwanie elementu
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                index = bst.search(value);
                elapsed = read_QPC() - start;

                if (index == -1) {
                    printf("%s\n", "\nNie odnaleziono.");
                } else {
                    printf("%s\n", "\nOdnaleziono.");
                }

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;

            case 3:
                // usuniecie elementu
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start = read_QPC();
                index = bst.remove(value);
                elapsed = read_QPC() - start;

                if (index == -1) {
                    printf("%s\n", "\nNie usunięto.");
                } else {
                    printf("%s\n", "\nUsunięto.");
                }

                cout << "Time [ms] = " << fixed << showpoint<< setprecision(3) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << fixed << showpoint<< setprecision(3) << (1000000.0 * elapsed) / frequency << endl << endl;
                system("pause");
                break;
        }
    }
};
