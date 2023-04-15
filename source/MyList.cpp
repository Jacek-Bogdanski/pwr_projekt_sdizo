#include <stdio.h>
#include <string>

using namespace std;

struct ListElement{
    int number;
    ListElement *next;
    ListElement *prev;
};

class MyList
{
private:
    int length;

    ListElement *head=nullptr;

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
            return;
        }

        ListElement *last = this->head;
        while (last->next != nullptr){
            last = last->next;
        }

        newElement->prev = last;
        last->next = newElement;

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

        if(this->head->next == nullptr){
            delete this->head;
            this->head = nullptr;
            return;
        }

        ListElement *last = this->head;
        while (last->next != nullptr){
            last = last->next;
        }

        last->prev->next = nullptr;
        delete last;
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

        if (index >= this->length)
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
    }

    void restart()
    {
        this->destroy();
    }

    string toString()
    {
        string output = "[ ";
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

        output.append(" ]");
        return output;
    }

    MyList(){
        this->length = 0;
        this->head = nullptr;
    };
};