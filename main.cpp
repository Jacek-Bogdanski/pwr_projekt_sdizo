#include <cstdio>
#include <ctime>
#include <algorithm>
#include "source/MyArray.cpp"
#include "source/MyList.cpp"
#include "source/MyHeap.cpp"

using namespace std;

void menuArray();
void menuList();
void menuHeap();
void menuRedBlackTree();

void handleArray();
void handleList();
void handleHeap();
void handleRedBlackTree();

void testArray();
void testList();
void testHeap();
void testRedBlackTree();

char menu_1[] = "\n\n\n\n\n### Projekt SDiZO, PWR 2023 ###\n### Autor:  Jacek Bogdański ###\n\n# MENU PROGRAMU:\n#   1. Tablica\n#   2. Lista\n#   3. Kopiec binarny\n#   4. Drzewo czerwono-czarne\n#   0. Koniec\n\nWybierz z listy: ";
char menu_2[] = "# CZYNNOSC:\n#   1. Sprawdzenie struktury\n#   2. Pomiar czasu\n#   0. Powrot\n\nWybierz z listy: ";
char menu_array[] = "# OPERACJE:\n#   1. Dodaj na poczatku\n#   2. Dodaj na koncu\n#   3. Dodaj na dowolnej pozycji\n#   4. Usuń z poczatku\n#   5. Usuń z konca\n#   6. Usuń z dowolnej pozycji\n#   0. Powrot\n\nWybierz z listy: ";
char menu_heap[] = "# OPERACJE:\n#   1. Dodaj\n#   2. Usun korzen\n#   0. Powrot\n\nWybierz z listy: ";

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
                menuArray();
                break;
            case 2:
                menuList();
                break;
            case 3:
                menuHeap();
                break;
            case 4:
                menuRedBlackTree();
                break;
        }
    }

    return 0;
}

void menuArray()
{
    printf("%s", "\n\n\n\n\n# Tablica\n\n");
    // pokazanie menu 2
    printf("%s", menu_2);
    int input;
    scanf("%d", &input);
    fflush(stdin);

    switch (input)
    {
        case 0:
            return;
        case 1:
            handleArray();
            break;
        case 2:
            testArray();
            break;
    }
}

// Wyświetlanie menu

void menuList()
{
    while (true)
    {
        printf("%s", "\n\n\n\n\n# Lista\n\n");
        // pokazanie menu 2
        printf("%s", menu_2);
        int input;
        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                return;
            case 1:
                handleList();
                break;
            case 2:
                testList();
                break;
        }
    }
}

void menuHeap()
{
    while (true)
    {
        printf("%s", "\n\n\n\n\n# Kopiec binarny\n\n");
        // pokazanie menu 2
        printf("%s", menu_2);
        int input;
        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                return;
            case 1:
                handleHeap();
                break;
            case 2:
                testHeap();
                break;
        }
    }
}

void menuRedBlackTree()
{
    while (true)
    {
        printf("%s", "\n\n\n\n\n# Drzewo czerwono-czarne\n\n");
        // pokazanie menu 2
        printf("%s", menu_2);
        int input;
        scanf("%d", &input);
        fflush(stdin);

        switch (input)
        {
            case 0:
                return;
            case 1:
                handleRedBlackTree();
                break;
            case 2:
                testRedBlackTree();
                break;
        }
    }
}

// Sprawdzenie struktury

void handleArray()
{
    MyArray array;
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
                array.prepend(value);
                break;
            case 2:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);
                array.append(value);
                break;
            case 3:
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);
                array.put(value, index);
                break;
            case 4:
                array.shift();
                break;
            case 5:
                array.pop();
                break;
            case 6:
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);
                array.remove(index);
                break;
        }
    }
};

void handleList()
{
    MyList list;
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Lista\n\n");
        printf("%s\n\n", list.toString().c_str());
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
                list.prepend(value);
                break;
            case 2:
                printf("%s", "\nPodaj wartosc: ");
                scanf("%d", &value);
                fflush(stdin);
                list.append(value);
                break;
            case 3:
                printf("%s", "\nPodaj wartosc i indeks: ");
                scanf("%d", &value);
                scanf("%d", &index);
                fflush(stdin);
                list.put(value, index);
                break;
            case 4:
                list.shift();
                break;
            case 5:
                list.pop();
                break;
            case 6:
                printf("%s", "\nPodaj indeks: ");
                scanf("%d", &index);
                fflush(stdin);
                list.remove(index);
                break;
        }
    }
};

void handleHeap(){
    MyHeap heap;
    int input;
    int value;
    int index;

    while (true)
    {
        printf("%s", "\n\n\n\n\n# Kopiec binarny\n\n");
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
                heap.add(value);
                break;
            case 2:
                heap.removeRoot();
                break;
        }
    }
};
void handleRedBlackTree(){

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
void testList(){

};
void testHeap(){

};
void testRedBlackTree(){

};
