#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


// źródło: stackoverflow.com
static string do_padding (unsigned index, unsigned mlength){
    string padding;
    if (int((index-1)/2) != 0){
        return (int((index-1)/2) % 2 == 0) ?
               (do_padding(int((index-1)/2),mlength) + string(mlength+4,' ') + " ")  :
               (do_padding(int((index-1)/2),mlength) + string(mlength+3,' ') + " |") ;
    }
    return padding;
}

// źródło: stackoverflow.com
static void printer (vector<int> const & tree, unsigned index, unsigned mlength){
    auto last = tree.size() - 1 ;
    auto  left = 2 * index + 1 ;
    auto  right = 2 * index + 2 ;
    cout << " " << tree[index] << " ";
    if (left <= last){
        auto llength = to_string(tree[left]).size();
        cout << "---" << string(mlength - llength,'-');
        printer(tree,left,mlength);
        if (right <= last) {
            auto rlength = to_string(tree[right]).size();
            cout << "\n" << do_padding(right,mlength) << string(mlength+ 3,' ') << " | ";
            cout << "\n" << do_padding(right,mlength) << string(mlength+ 3,' ') << " └" <<
                      string(mlength - rlength,'-');
            printer(tree,right,mlength);
        }
    }
}

// źródło: stackoverflow.com
static void print_tree (vector<int> & tree){
    unsigned mlength = 0;
    for (int & element : tree){
        auto clength = to_string(element).size();
        if (clength > mlength) {
            mlength = to_string(element).size();
        }
    }
    cout <<  string(mlength- to_string(tree[0]).size(),' ');
    printer(tree,0,mlength);
}

class MyHeap
{
private:
    int length;

    int *array;

public:
    int getLength()
    {
        return this->length;
    }

    void add(int n)
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

        this->fixHeapUp(this->length-1);
    }


    /**
     * @brief Funkcja usuwa korzeń
     *
     * @param n
     */
    void removeRoot()
    {
        if(this->length==0){
            return;
        }
        if(this->length==1){
            delete this->array;
            this->array = nullptr;
            return;
        }

        this->array[0] = this->array[this->length-1];

        int *tmp = new int[this->length - 1];
        for (int i = 0; i < this->length - 1; i++)
        {
            tmp[i] = this->array[i];
        }
        this->length--;
        delete this->array;
        this->array = tmp;
        this->fixHeapDown(0);
    }

    void fixHeapDown(int index){
        int leftChild = 2*index+1;
        int rightChild = 2*index+2;

        if(rightChild < this->length && leftChild >= this->length){
            // istnieje tylko prawy
            if(this->array[rightChild] > this->array[index]){
                // prawy jest wiekszy
                int tmp = this->array[rightChild];
                this->array[rightChild] = this->array[index];
                this->array[index] = tmp;
                this->fixHeapDown(rightChild);
            }
        }
        else if(leftChild < this->length && rightChild >= this->length){
            // istnieje tylko lewy
            if(this->array[leftChild] > this->array[index]){
                // lewy jest wiekszy
                int tmp = this->array[leftChild];
                this->array[leftChild] = this->array[index];
                this->array[index] = tmp;
                this->fixHeapDown(leftChild);
            }
        }
        else if(rightChild < this->length && leftChild < this->length) {
            // oba istnieją

            if(this->array[rightChild] > this->array[leftChild] && this->array[rightChild] > this->array[index]){
                // prawy jest wiekszy
                int tmp = this->array[rightChild];
                this->array[rightChild] = this->array[index];
                this->array[index] = tmp;
                this->fixHeapDown(rightChild);
            }
            else if(this->array[leftChild] > this->array[rightChild] && this->array[leftChild] > this->array[index]){
                // lewy jest wiekszy
                int tmp = this->array[leftChild];
                this->array[leftChild] = this->array[index];
                this->array[index] = tmp;
                this->fixHeapDown(leftChild);
            }
        }
    }

    void fixHeapUp(int index){
        if(index==0){
            return;
        }

        int parentIndex = floor((index-1)/2);
        if(this->array[parentIndex] < this->array[index]){
            int tmp = this->array[parentIndex];
            this->array[parentIndex] = this->array[index];
            this->array[index] = tmp;
            this->fixHeapUp(parentIndex);
        }
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

    void printHeap()
    {
        if(this->length == 0){
            std::printf("%s","Kopiec jest pusty\n\n");
            return;
        }
        vector<int> heapVector;
        for(auto i =0; i<this->length; i++){
            heapVector.push_back(this->array[i]);
        }
        cout << "\n";
        print_tree(heapVector);
        std::printf("%s","\n\n");
    }

    MyHeap(){
        this->length = 0;
        this->array = nullptr;
    };
};