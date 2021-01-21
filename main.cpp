#include <iostream>

//----------------------------------------------Линейный список----------------------------------------------------------------------------------------
template <class T>
struct QQ{
    T* arr;// начало выделенной памяти
    int max;
    int start;
    int end;
    int cur;
};

template <class T>
void constructor (QQ<T>* my_q, int max){
    my_q->max = max;
    my_q->start = 0; // искать и удалять и все вс5 все куда вставить относительно старта
    my_q->end = 0;
    my_q->arr = new T[my_q->max];
    my_q->cur = 0;

}

template  <class T>
void destructor (QQ<T>* my_q){
    delete[] my_q->arr;
}

template <class T>
void realloc_qq (QQ<T>* my_q){
    my_q->max *= 2;
    T* tmp = my_q->arr;
    my_q->arr = new T [my_q->max];
    for (int i = 0; i < my_q->max/2; ++i) {
       my_q->arr[i] = tmp[i];
    }
}

template <class T>
void push_back (QQ<T>* my_q, T data) {
    if (my_q->cur - 1 == my_q->max){
        realloc_qq(my_q);
    }
    if (my_q->cur == 0){
        my_q->arr[my_q->start] = data;
    }
    else {
        my_q->end++;
        if (my_q->end > my_q->max - 1) {
            my_q->end = 0;
        }
        my_q->arr[my_q->end] = data;
    }
    my_q->cur++;
}

template <class T>
void push_front (QQ<T>* my_q, T data){
    if (my_q->cur - 1 == my_q->max){
        realloc_qq(my_q);
    }
    if (my_q->cur == 0){
        my_q->arr[my_q->start] = data;
    }
    else{
        my_q->start--;
        if (my_q->start < 0) {
            my_q->start = my_q->max - 1;
        }
        my_q->arr[my_q->start] = data;
    }
    my_q->cur++;
}

template <class T>
void push_index (QQ<T>* my_q, int index, T data){

}

template <class T>
T pop_index ( QQ<T>* my_q, int index){
    assert(my_q->cur != 0);
    T result = my_q->arr[index];
    my_q->arr[index] = 0;
    return result;
}

template <class T>
T pop_front (QQ<T>* my_q) {
    assert (my_q->cur != 0);
    T result = my_q->arr[my_q->start];
    my_q->arr[my_q->start] = 0;
    my_q->start++;
    if (my_q->start > my_q->max - 1) my_q->start = 0;
    my_q->cur--;
    return result;
}

template <class T>
T pop_back (QQ<T>* my_q){
   assert (my_q->cur != 0);
   T result = my_q->arr[my_q->end];
   my_q->arr[my_q->end] = 0;
   my_q->end--;
   if (my_q->end < 0) my_q->end = my_q->max;
   my_q->cur--;
   return result;
}

template <class T>
T show_value (const QQ<T>* my_q, int index){
    assert (my_q->cur != 0);
    T result = my_q->arr[index];
    return result;
}

template <class T>
int counter (QQ<T>* my_q){
    return my_q->cur;
}

template <class T>
void print (const QQ<T>* my_q){
    int start = my_q->start;
    int end = my_q->end;
    while (start != end){
        std::cout << my_q->arr[start] << std::endl;
        start++;
        if (start >  my_q->max - 1) start = 0;
    }

}
template <class T>
    int search_by_argument(const QQ <T>* my_q, T argument){
    int start = my_q->start;
    int end = my_q->end;
    int result = 0;
    while (start != end){
        if (start > end - 1) start = 0;
        if (my_q->arr[start] == argument) {
            result = argument;
        }
        start++;
    }
    return result;
}
//-------------------------------------------------Кольцевой двусвязный список-------------------------------------
template <class R>
struct node {
    R data;
    node<R>* next;
    node<R>* prev;
};

template <class R>
struct list_round{
    node<R>* start;
    int emptiness_flag;
};

template <class R>
void constructor (list_round<R>* my_round){
    my_round->start = new node<R>;
    my_round->start->data = 0;
    my_round->start->next = nullptr;
    my_round->start->prev = nullptr;
    my_round->emptiness_flag = 1;
}

template <class R>
void destructor (list_round<R>* my_round) {
    if (my_round->emptiness_flag == 1) delete my_round->start;
    my_round->start->prev->next = nullptr;
    do {
        node<R>* to_delete = my_round->start;
        if (my_round->start->next != nullptr) my_round->start->next->prev = nullptr;
        my_round->start = my_round->start->next;
        delete to_delete;
    } while (my_round->start != nullptr);
    delete my_round->start;
}

template <class R>
void push_back (list_round<R>* my_round, R data){
    if (my_round->emptiness_flag == 1) {
        my_round->start->data = data;
        my_round->emptiness_flag = 0;
        my_round->start->next = my_round->start;
        my_round->start->prev = my_round->start;
    }
    else{
        node<R>* New_node = new node<R>;
        New_node->data = data;
        node<R>* tmp = my_round->start->prev;
        my_round->start->prev = New_node;
        New_node->prev = tmp;
        New_node->next = my_round->start;
        tmp->next = New_node;
    }

}

template <class R>
void push_front (list_round<R>* my_round, R data){
    if (my_round->emptiness_flag == 1) {
        my_round->start->data = data;
        my_round->emptiness_flag = 0;
        my_round->start->next = my_round->start;
        my_round->start->prev = my_round->start;
    }
    else{
        node<R>* New_node = new node<R>;
        New_node->data = data;
//        my_round->start->prev->next = New_node;
//        New_node->prev = my_round->start->prev;
//        my_round->start->prev = New_node;
//        my_round->start = New_node;


        my_round->start->prev->next = New_node;
        New_node->next = my_round->start;
        New_node->prev = my_round->start->prev;
        my_round->start->prev = New_node;
        my_round->start = New_node;
    }

}

template <class R>
R pop_front (list_round<R>* my_round){
    node<R>* to_delete = my_round->start;
    R result = to_delete->data;
    my_round->start->next->prev = my_round->start->prev;
    my_round->start->prev->next = my_round->start->next;
    delete to_delete;
    return result;
}

template <class R>
R pop_back (list_round<R>* my_round){
    node<R>* to_delete = my_round->start->prev;
    R result = to_delete->data;
    my_round->start->prev = my_round->start->prev->prev;
    my_round->start->prev->prev->next = my_round->start;
    delete to_delete;
    return result;
}

template <class R>
void push_pointer (list_round<R>* my_round, node<R>* pointer, R data){
    node<R>* New_node = new node<R>;
    New_node->data = data;
    New_node->prev = pointer;
    New_node->next = pointer->next->next;
    pointer->next->prev = New_node;
    pointer->next = New_node;
}

template <class R>
node<R>* search (const list_round<R>* my_round, int index){
    int runner = 0;
    node <R>* tmp = my_round->start;
    while (runner != index){
        tmp = tmp->next;
        runner++;
    }
    return tmp;
};

template <class R>
void push_index (list_round<R>* my_round, int index, R data){
    push_pointer(my_round, search(my_round, index), data);
}

template <class R>
R pop_index (list_round<R>* my_round, int index){
    node<R>* to_delete = search(my_round, index);
    R result = to_delete->data;
    to_delete->prev->next = to_delete->next;
    to_delete->next->prev = to_delete->prev;
    delete to_delete;
    return result;
}

template <class R>
R pop_pointer (list_round<R>* my_round, node<R>* pointer){
    R result = pointer->data;
    pointer->prev->next = pointer->next;
    pointer->next->prev = pointer->prev;
    delete pointer;
    return result;
}

template <class R>
R get_value (list_round<R>* my_round, int index){
    node<R>* pointer = search(my_round, index);
    R result = pointer->data;
    return result;
}

template <class R>
int counter (list_round<R>* my_round){
    assert(my_round->emptiness_flag != 1);
    int result = 1;
    node<R>* runner = my_round->start;
    while (runner->next != my_round->start){
        runner = runner->next;
        result++;
    }
    return result;
}

template <class R>
void print (const list_round<R>* my_round){
    assert(my_round->emptiness_flag != 1);
    node<R>* runner = my_round->start;
    int index = 0;
    do {
        std::cout << "index : " << index << " value : " << runner->data << std::endl;
        runner = runner->next;
        index++;
    } while (runner->next != my_round->start->next);
}

int main() {
    list_round<int>* my_round;
    constructor(my_round);
    push_back(my_round,1);
    push_back(my_round,2);
    push_back(my_round,3);
    push_back(my_round,4);
    push_front(my_round, 5);
    destructor(my_round);
//    std::cout << pop_index(my_round,0);
//    std::cout << pop_front(my_round);
//    push_index(my_round, 1, 0);
//    push_index(my_round, 1, -1);
    return 0;
}
