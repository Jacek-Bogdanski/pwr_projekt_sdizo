#include <stdio.h>
#include <string>

using namespace std;

class MyArray
{
private:
    int length;

    int *array;

public:
    int getLength()
    {
        return this->length;
    }

    void append(int n)
    {
        int *tmp = new int[this->length + 1];
        for (int i = 0; i < this->length; i++)
        {
            tmp[i] = this->array[i];
        }
        tmp[this->length] = n;
        this->length++;

        delete this->array;
        this->array = tmp;
    }

    void prepend(int n)
    {
        int *tmp = new int[this->length + 1];
        for (int i = 0; i < this->length; i++)
        {
            tmp[i + 1] = this->array[i];
        }
        tmp[0] = n;
        this->length++;
        delete this->array;
        this->array = tmp;
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
        // indeks zawiera  się w tablicy
        int *tmp = new int[this->length + 1];
        int offset = 0;
        for (int i = 0; i <= this->length; i++)
        {
            if (i == index)
            {
                offset = 1;
                tmp[i] = n;
            }
            else
            {
                tmp[i + offset] = this->array[i];
            }
        }
        delete this->array;
        this->length++;
        this->array = tmp;
    }

    /**
     * @brief Funkcja usuwa element z końca tablicy
     *
     * @param n
     */
    void pop()
    {
        if(this->length==0){
            return;
        }
        int *tmp = new int[this->length - 1];
        for (int i = 0; i < this->length - 1; i++)
        {
            tmp[i] = this->array[i];
        }
        this->length--;
        delete this->array;
        this->array = tmp;
    }

    /**
     * @brief Funkcja usuwa element z początku tablicy
     *
     * @param n
     */
    void shift()
    {
        if(this->length==0){
            return;
        }
        int *tmp = new int[this->length - 1];
        for (int i = 0; i < this->length - 1; i++)
        {
            tmp[i] = this->array[i + 1];
        }
        this->length--;
        delete this->array;
        this->array = tmp;
    }

    void remove(int index)
    {
        if(this->length==0){
            return;
        }
        if (index >= this->length)
        {
            this->pop();
            return;
        }
        if (index == 0)
        {
            this->shift();
            return;
        }
        // indeks zawiera się w tablicy
        int *tmp = new int[this->length - 1];
        int offset = 0;
        for (int i = 0; i < this->length; i++)
        {
            if (i == index)
            {
                offset = -1;
            }
            else
            {
                tmp[i + offset] = this->array[i];
            }
        }
        delete this->array;
        this->length--;
        this->array = tmp;
    }

    void destroy()
    {
        delete this->array;
        this->array = nullptr;
    }

    void restart()
    {
        delete this->array;
        this->length = 0;
        this->array = nullptr;
    }

    string toString()
    {
        string output = "[ ";
        for (int i = 0; i < this->length; i++)
        {
            output.append(to_string(this->array[i]));
            output.append(", ");
        }

        if (this->length > 0)
        {
            output.pop_back();
        }
        output.pop_back();

        output.append(" ]");
        return output;
    }

    MyArray(){
        this->length = 0;
        this->array = nullptr;
    };
};