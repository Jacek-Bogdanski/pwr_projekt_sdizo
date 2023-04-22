#include <cstdio>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "source/MyArray.cpp"
#include "source/MyList.cpp"
#include "source/MyHeap.cpp"
#include "source/MyBST.cpp"

using namespace std;

void menuData();

void handleArray();
void handleList();
void handleHeap();
void handleBST();

clock_t start_time;
clock_t stop_time;
double operation_time;
string input_s;

bool fileExists(std::string filename){
    std::ifstream file(filename.c_str());

    if (file) {
        return true;
    }
    return false;
}

char menu_header[] = "\n\n\n\n\n### Projekt SDiZO, PWR 2023 ###\n### Autor:  Jacek Bogdański ###\n\n";
char menu_1[] = "# MENU PROGRAMU:\n#   1. Tablica\n#   2. Lista\n#   3. Kopiec binarny\n#   4. Drzewo BST\n#   9. Dane wejściowe\n#   0. Koniec\n\nWybierz z listy: ";
char menu_array[] = "# OPERACJE:\n#   1. Dodaj na poczatku\n#   2. Dodaj na koncu\n#   3. Dodaj na dowolnej pozycji\n#   4. Usuń z poczatku\n#   5. Usuń z końca\n#   6. Usuń z dowolnej pozycji\n#   7. Szukaj\n#   0. Powrot\n\nWybierz z listy: ";
char menu_heap[] = "# OPERACJE:\n#   1. Dodaj\n#   2. Usun korzen\n#   3. Wyszukaj\n#   0. Powrot\n\nWybierz z listy: ";
char menu_bst[] = "\n# OPERACJE:\n#   1. Dodaj\n#   2. Usun \n#   3. Szukaj \n#   4. Usuń element \n#   0. Powrot\n\nWybierz z listy: ";
char menu_data[] = "# OPERACJE:\n#   1. Wybierz plik\n#   2. Wygeneruj plik \n#   3. Wczytaj dane z wybranego pliku \n#   4. Wyczyść załadowane dane \n#   0. Powrot\n\nWybierz z listy: ";

string file_name = "input.txt";

int *test_data = nullptr;
int test_data_size = 0;
int val = 0;

void readTestData(){
    std::ifstream file(file_name.c_str());
    test_data_size=0;
    if(file.is_open())
    {
        file >> test_data_size;
        if(file.fail())
        {
            cout << "Błąd odczytu danych" << endl;
            test_data_size=0;
        }
        else{
            test_data = new int[test_data_size];
            for(int i = 0; i < test_data_size; i++)
            {
                file >> val;
                if(file.fail())
                {
                    cout << "Błąd odczytu danych" << endl;
                    break;
                }
                else
                {
                    test_data[i] = val;
                }
            }
        }
        file.close();
    }
    else {
        cout << "File error - OPEN" << endl;
    }
}

int main()
{
    // Autor: Jacek Bogdański, 263895

    // Menu
    // 1. tablica
    // 2. lista
    // 3. kopiec binarny
    // 4. drzewo czerwono-czarne
    // 0. exit

    int input;

    while (true)
    {
        printf("%s", menu_header);

        printf("Plik: %s\n", file_name.c_str());
        printf("Rozmiar wczytanych danych: %d\n\n", test_data_size);

        // pokazanie menu 1
        printf("%s", menu_1);

        // pobranie 1
        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                printf("%s", "\nProgram zakonczony.\n");
                return 0;
            case 1:
                handleArray();
                break;
            case 2:
                handleList();
                break;
            case 3:
                handleHeap();
                break;
            case 4:
                handleBST();
                break;
            case 9:
                menuData();
                break;
        }
    }

    return 0;
}

void menuData()
{
    while (true)
    {
        printf("%s", "\n\n\n\n\n# Dane wejściowe\n\n");
        printf("Plik: %s\n", file_name.c_str());
        printf("Rozmiar wczytanych danych: %d\n\n", test_data_size);
        // pokazanie menu danych wejsciowych
        printf("%s", menu_data);
        int input;
        scanf("%d", &input);
        fflush(stdin);

        char tmp[] = "";
        int n;

        switch (input)
        {
            case 0:
                return;
            case 1:
                printf("%s", "\nPodaj nazwę pliku: ");
                scanf("%s", tmp);
                fflush(stdin);

                if(!fileExists(tmp)){
                    printf("%s", "\nPlik nie istnieje!\n\n");
                }
                else{
                    file_name = tmp;
                    readTestData();

                    printf("%s", "\nPlik został załadowany. \n\n");
                }
                return;

            case 3:
                readTestData();
                printf("%s", "\nPlik został załadowany. \n\n");
                return;

            case 4:
                delete test_data;
                test_data = nullptr;
                test_data_size = 0;
                printf("%s", "\nDane zostały wyczyszczone. \n\n");
                return;

            case 2:
                printf("%s", "\nPodaj ilość liczb: ");
                scanf("%d", &n);
                fflush(stdin);

                ofstream file;
                file.open (file_name);
                file << n << "\n";

                for(int i=0;i<n;i++){
                    file << rand() << "\n";
                }

                file.close();
                readTestData();
                printf("%s", "\nPlik został utworzony i załadowany. \n\n");
                return;
        }
    }
}

// Sprawdzenie struktury

void handleArray()
{
    MyArray array(test_data,test_data_size);
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Tablica\n\n");
        printf("%s\n\n", array.toString().c_str());
        // pokazanie menu tablicy
        printf("%s", menu_array);

        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                array.destroy();
                return;
            case 1:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                array.prepend(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 2:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                array.append(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 3:
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);

                start_time = clock();
                array.put(value, index);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 4:
                start_time = clock();
                array.shift();
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 5:
                start_time = clock();
                array.pop();
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 6:
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);

                start_time = clock();
                array.remove(index);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;

            case 7:
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                index = array.search(value);
                stop_time = clock();


                if(index==-1){
                    printf("%s", "\nNie odnaleziono.");
                }
                else{
                    printf("%s %d", "\nOdnaleziono pod indeksem:",index);
                }
                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);

                break;
        }
    }
};

void handleList()
{
    MyList list(test_data,test_data_size);
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Lista\n\n");
        printf("%s\n", list.toString().c_str());
        // pokazanie menu listy
        printf("%s", menu_array);

        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                list.destroy();
                return;
            case 1:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                list.prepend(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 2:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                list.append(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 3:
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);

                start_time = clock();
                list.put(value, index);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 4:
                start_time = clock();
                list.shift();
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 5:
                start_time = clock();
                list.pop();
                break;
            case 6:
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);

                start_time = clock();
                list.remove(index);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 7:
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                index = list.search(value);
                stop_time = clock();

                if(index==-1){
                    printf("%s", "\nNie odnaleziono.");
                }
                else{
                    printf("%s %d", "\nOdnaleziono pod indeksem:",index);
                }
                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
        }
    }
};

void handleHeap(){
    MyHeap heap(test_data,test_data_size);
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Kopiec binarny\n");
        heap.printHeap();

        // pokazanie menu kopca
        printf("%s", menu_heap);

        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                heap.destroy();
                return;
            case 1:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                heap.add(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 2:
                start_time = clock();
                heap.removeRoot();
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 3:
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                index = heap.search(value);
                stop_time = clock();

                if(index==-1){
                    printf("%s", "\nNie odnaleziono.");
                }
                else{
                    printf("%s %d", "\nOdnaleziono pod indeksem:",index);
                }

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
        }
    }
};

void handleBST(){
    MyBST bst(test_data,test_data_size);
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Drzewo BST\n");
        bst.printBST();

        // pokazanie menu kopca
        printf("%s", menu_bst);

        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                bst.destroy();
                return;
            case 1:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                bst.add(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 2:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                bst.remove(value);
                stop_time = clock();

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 3:
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);

                start_time = clock();
                index = bst.search(value);
                stop_time = clock();

                if(index==-1){
                    printf("%s", "\nNie odnaleziono.");
                }
                else{
                    printf("%s", "\nOdnaleziono.");
                }

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
            case 4:
                printf("%s", "\nPodaj liczbę: ");
                scanf("%d", &value);
                fflush(stdin);
                index = bst.remove(value);
                stop_time = clock();

                if(index==-1){
                    printf("%s", "\nNie usunięto.");
                }
                else{
                    printf("%s", "\nUsunięto.");
                }

                printf("\nCzas operacji: %.4f ms \n", double(stop_time*1000 - start_time*1000) / CLOCKS_PER_SEC);
                getline(cin, input_s);
                break;
        }
    }
};





// Testy i pomiar czasu

void testArray()
{
    MyArray array;
    int number;
    srand(time(0));
    bool print = false;

    // tablica z danymi testowymi, jej tworzenie i wypełnienie nie jest uwzględniane w pomiarze czasu
    int *dataArray;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Tablica\n\n");
        if (print)
        {
            printf("%s\n\n", array.toString().c_str());
        }
        printf("%s", "Zostanie wykonana podana liczba powtorzen wszystkich operacji.\n");
        printf("%s", "Podaj wartość niedodatnią, aby wrocić do menu.\n");

        printf("%s", "\nPodaj liczbę operacji: ");
        scanf("%d", &number);
        fflush(stdin);
        printf("\n\nNr ; Liczba   ; Identyfikator ; Czas [ms] \n");

        if (number <= 0)
        {
            array.destroy();
            return;
        }

        // przygotowanie danych testowych
        dataArray = new int[number];
        for (int i = 0; i < number; i++)
        {
            dataArray[i] = rand();
        }
        clock_t start;
        clock_t stop;
        double operationTime;

        // Pomiar dodawania na końcu tablicy
        array.restart();
        start = clock();
        for (int i = 0; i < number; i++)
        {
            array.append(dataArray[i]);
        }
        stop = clock();
        operationTime = double(stop - start) / CLOCKS_PER_SEC;
        printf("1  ; %8d ; array_append  ; %.3f \n", number, operationTime * 1000);

        printf("%s\n\n", array.toString().c_str());

        // Pomiar usuwania z końca tablicy
        start = clock();
        for (int i = 0; i < number; i++)
        {
            array.pop();
        }

        stop = clock();

        operationTime = double(stop - start) / CLOCKS_PER_SEC;
        printf("2  ; %8d ; array_pop     ; %.3f \n", number, operationTime * 1000);

        // Pomiar dodawania na początku tablicy
        array.restart();
        start = clock();
        for (int i = 0; i < number; i++)
        {
            array.prepend(dataArray[i]);
        }
        stop = clock();
        operationTime = double(stop - start) / CLOCKS_PER_SEC;
        printf("3  ; %8d ; array_prepend ; %.3f \n", number, operationTime * 1000);


        // Pomiar usuwania z początku tablicy
        start = clock();
        for (int i = 0; i < number; i++)
        {
            array.shift();
        }
        stop = clock();
        operationTime = double(stop - start) / CLOCKS_PER_SEC;
        printf("4  ; %8d ; array_shift   ; %.3f \n", number, operationTime * 1000);


        // Pomiar dodawania na losowym miejscu w tablicy
        array.restart();
        start = clock();
        for (int i = 0; i < number; i++)
        {
            array.put(dataArray[i], (int)i/2);
        }
        stop = clock();
        operationTime = double(stop - start) / CLOCKS_PER_SEC;
        printf("5  ; %8d ; array_put     ; %.3f \n", number, operationTime * 1000);
    }
};
