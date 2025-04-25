#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP


template <typename T>
class dyn_array {
    T* pData;
    int occupied;
    int capacity;
public:
    dyn_array(int c = 1): pData(new T[c]), occupied(0), capacity(c) {};
    void append(T element) {

    }
    void arr_delete(int idx)  {

    }
    T operator[](int idx) {

    }
    ~dyn_array() {
        delete[] pData;
    };
};


#endif