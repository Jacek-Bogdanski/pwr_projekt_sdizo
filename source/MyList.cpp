#include <stdio.h>
#include <string>

using namespace std;

struct ListElement{
    int number;
    ListElement *next = nullptr;
    ListElement *prev = nullptr;
};

class MyList
{
private:
    int length;

    ListElement *head=nullptr;
    ListElement *tail=nullptr;

public:
    int getLength()
    {
        return this->length;
    }

    /**
     * Dodanie na końcu
     * @param n
     */
    void append(int n)
    {
        ListElement *newElement = new ListElement;
        newElement->number = n;
        if(this->head==nullptr){
            this->head = newElement;
            this->tail = newElement;
            return;
        }


        newElement->prev = this->tail;
        this->tail->next = newElement;
        this->tail = newElement;

        this->length++;
    }

    /**
     * Dodanie na początku
     * @param n
     */
    void prepend(int n)
    {
        ListElement *newElement = new ListElement;
        newElement->number = n;
        if(this->head==nullptr){
            this->head = newElement;
            this->tail = newElement;
            return;
        }

        newElement->next = this->head;
        this->head->prev = newElement;
        this->head = newElement;

        this->length++;
    }

    void put(int n, int index)
    {
        if (index >= this->length)
        {
            this->append(n);
            return;
        }
        if (index <= 0)
        {
            this->prepend(n);
            return;
        }

        ListElement *newElement = new ListElement;
        newElement->number = n;
        if(this->head==nullptr){
            this->head = newElement;
            this->tail = newElement;
            return;
        }

        int i=0;
        ListElement *element = this->head;
        while(i<index){
            element = element->next;
            i++;
        }

        // wstawiamy przed element
        newElement->prev = element->prev;
        newElement->next = element;
        element->prev->next = newElement;
        element->prev = newElement;

        this->length++;
    }

    /**
     * @brief Funkcja usuwa element z końca tablicy
     *
     * @param n
     */
    void pop()
    {
        if(this->head == nullptr){
            return;
        }

        // usunięcie jedynego elementu
        if(this->head->next == nullptr){
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            return;
        }

        ListElement *prev = this->tail->prev;
        prev->next = nullptr;
        delete this->tail;
        this->tail = prev;
    }

    /**
     * @brief Funkcja usuwa element z początku tablicy
     *
     * @param n
     */
    void shift()
    {
        if(this->head == nullptr){
            return;
        }
        if(this->head->next == nullptr){
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            return;
        }

        ListElement *tmp = this->head->next;
        tmp->prev = nullptr;
        delete this->head;
        this->head = tmp;
    }

    void remove(int index)
    {
        if(this->head == nullptr){
            return;
        }

        if (index >= this->length-1)
        {
            this->pop();
            return;
        }
        if (index <= 0)
        {
            this->shift();
            return;
        }

        if(this->head->next == nullptr){
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            return;
        }

        int i=0;
        ListElement *element = this->head;
        while(i<index){
            element = element->next;
            i++;
        }

        // usuwamy element
        element->next->prev = element->prev;
        element->prev->next = element->next;
        delete element;
    }

    void destroy()
    {
        ListElement *last = this->head;
        ListElement *tmp = nullptr;
        do{
            tmp = last;
            last = last->next;
            delete tmp;
        } while (last != nullptr);

        this->head = nullptr;
        this->tail = nullptr;
    }

    int search(int n){
        if(this->head == nullptr){
            return -1;
        }
        int i=0;
        ListElement *last = this->head;
        while(last != nullptr){
            if(last->number == n){
                return i;
            }
            last = last->next;
            i++;
        }
        return -1;
    }

    void restart()
    {
        this->destroy();
    }

    string toString()
    {
        string output = "FRONT [ ";
        ListElement *last = this->head;

        while (last != nullptr) {
            output.append(to_string(last->number));
            output.append(", ");
            last = last->next;
        }

        if (this->head != nullptr)
        {
            output.pop_back();
        }
        output.pop_back();

        output.append(" ]\n");

        output.append("BACK  [ ");
        last = this->tail;

        while (last != nullptr) {
            output.append(to_string(last->number));
            output.append(", ");
            last = last->prev;
        }

        if (this->tail != nullptr)
        {
            output.pop_back();
        }
        output.pop_back();

        output.append(" ]\n");

        return output;
    }

    MyList(){
        this->length = 0;
        this->head = nullptr;
        this->tail = nullptr;
    };

    MyList(int *data, int length){
        if(length==0){
            this->length = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }
        for(int i=0;i<length;i++){
            this->append(data[i]);
        }
    };
};