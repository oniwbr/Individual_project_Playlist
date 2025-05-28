// Copyright 2025 Kanukova Margarita

#include <iostream>
#include <random>

#define STEP_OF_CAPACITY 15

enum State{ empty, busy, deleted };
template <class T>
class TVector {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;
public:
    TVector(size_t size = 0);
    TVector(size_t, const T*);
    TVector(size_t, std::initializer_list<T>);
    TVector(std::initializer_list<T>);
    TVector(const TVector<T>&);
    TVector(size_t, const T&);

    ~TVector();

    inline bool is_empty() const noexcept;

    T& operator[](size_t) noexcept;
    const T& operator[](size_t) const noexcept;

    bool operator ==(const TVector<T>&) const noexcept;
    bool operator !=(const TVector<T>&) const noexcept;

    TVector<T>& operator = (const TVector<T>&) noexcept;

    inline T* data() noexcept;
    inline T& front();
    inline T& back();
    inline T* begin() noexcept;
    inline T* end() noexcept;

    inline const T* data() const noexcept;
    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;
    inline const T* begin() const noexcept;
    inline const T* end() const noexcept;
    inline const T& front() const;
    inline const T& back() const;


    void push_front(const T&) noexcept;
    void push_back(const T&) noexcept;
    void insert(size_t, const T&);
    void insert(size_t, size_t, const T&);
    void insert(size_t, std::initializer_list<T>);

    void pop_back();
    void pop_front();
    void erase(size_t index);
    void erase(size_t first, size_t last);

    void replace(size_t, const T&);
    void replace(T*, const T&);


    void assign(size_t, const T&) noexcept;
    void assign(std::initializer_list<T>) noexcept;
    T& at(size_t index);
    const T& at(size_t index) const;
    void clear();

    void reserve(size_t) noexcept;
    void shrink_to_fit() noexcept;
    void resize(size_t,const T&) noexcept;
    void resize(size_t) noexcept;


    void print();
    
    template <class T>
    friend void hoara_sort(TVector<T>&) noexcept;
    template <class T>
    friend void hoara_sort_rec(TVector<T>&, size_t, size_t);
    template <class T>
    friend void shuffle(TVector<T>&);
    template <class T>
    friend size_t find_first_elem(const TVector<T>&, T);
    template <class T>
    friend size_t find_last_elem(const TVector<T>&, T);
    template <class T>
    friend TVector<T> find_all(const TVector<T>&, T);
    template <class T>
    friend T* find_first_ptr(const TVector<T>&, T);
    template <class T>
    friend T* find_last_ptr(const TVector<T>&, T);
    template <class T>
    friend TVector<T*> find_all_ptrs(const TVector<T>&, T);

private:
    size_t recalc_index(size_t) const noexcept;
    void swap_pos(size_t, size_t) const noexcept;
    size_t rand_generation(size_t, size_t) const noexcept;
    void set_memory(size_t) noexcept;
    void reset_memory() noexcept;
    void reset_memory_for_delete() noexcept;
    inline bool is_full() const noexcept;
};

template <class T>
void TVector<T>::print() {
    if (_data == nullptr) return;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == deleted) continue;
        std::cout << _data[i] << " ";
    }
}

template <class T>
void TVector<T>::set_memory(size_t size) noexcept {
    _deleted = 0;
    if (_size != size) _size = size;
    _capacity = ((_size + _deleted) / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
}

template <class T>
void TVector<T>::reset_memory() noexcept {
    _capacity = ((_size + _deleted) / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];

    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    } 
    for (; j < _capacity; j++) {
        new_states[j] = empty;
    }

    delete[] _data;
    delete[] _states;
    _deleted = 0;
    _data = new_data;
    _states = new_states;
}

template <class T>
void TVector<T>::reset_memory_for_delete() noexcept {
    if (_deleted>=0.15*_size) {
        reset_memory();
    }
}

template <class T>
TVector<T>::TVector(size_t size) {
    set_memory(size);

    size_t i = 0;
    for (; i < _size; i++) {
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T>
TVector<T>::TVector(size_t size, const T* data){
    if (data == nullptr) throw std::logic_error("Data doesnt`t recieve!\n");
    set_memory(size);
    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T>
TVector<T>::TVector(size_t size, std::initializer_list<T> data) {
    if (&data == NULL) throw std::logic_error("Data doesn`t recieve!\n");
    set_memory(size);
    
    size_t i = 0;
    auto it = data.begin();
    for (; i < _size; i++) { 
        _data[i] = *it;
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
    if (&data == NULL) throw std::logic_error("The object doesn`t recieve\n");
    set_memory(data.size());

    size_t i = 0;
    auto it = data.begin();
    for (; i < _size; i++, it++) {
        _data[i] = *it;
        _states[i] = busy;
    }
    for(; i < _capacity;i++){
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(const TVector<T>& other) {
    if (&other == NULL) throw std::logic_error("Object doesn`t recieve\n");
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new State[_capacity];
    size_t i = 0;
    for (; i < _size+ _deleted; i++) { 
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T& value) {
    set_memory(size);
    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = value;
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
    return _size == 0;
}

template <class T>
void TVector<T>::reserve(size_t new_cap) noexcept {
    if (new_cap <= _capacity) {
        return;
    }
    _capacity = new_cap;
    T* new_data = new T[_capacity];
    State* new_states = new State[_capacity];

    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    for (; j < _capacity; j++) {
        new_states[j] = empty;
    }
    
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
}

template <class T>
void TVector<T>::shrink_to_fit() noexcept {
    if (_size == _capacity) {
        return;
    }

    if (_size  < _capacity || _deleted > 0) {
        _capacity = _size;
        T* new_data = new T[_capacity];
        State* new_state = new State[_capacity];
        int j = 0;
        for (int i = 0; i < _size + _deleted; i++) {
            if (_states[i] == deleted) continue;
            else if (_states[i] == busy) {
                new_data[j] = _data[i];
                new_state[j] = busy;
                j++;
            }
        }
        for (; j < _capacity; j++) {
            new_state[j] = empty;
        }
        
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_state;
        _deleted = 0;
    }
}

template <class T>
void TVector<T>::resize(size_t size) noexcept {
    if (_size != size) {
        size_t old_size = _size;
        _size = size;
        reset_memory();
        if (_size > old_size) {
            for (size_t i = old_size + _deleted; i < _size; i++) {
                _states[i] = busy;
            }
        }
    }
}

template <class T>
void TVector<T>::resize(size_t size,const T& value) noexcept {
    if (_size != size) {
        size_t old_size = _size;
        resize(size);
        if (_size > old_size) {
            for (size_t i = old_size + _deleted; i < _size; i++) {
                _data[i] = value;
            }
        }
    }
}

template <class T>
inline T* TVector<T>::data() noexcept {
    return _data;
}

template <class T>
inline T& TVector<T>::front() {
    if (is_empty()) throw std::logic_error("Vector is empty!\n");
    size_t index = recalc_index(0);
    return _data[index];
}

template <class T>
inline T& TVector<T>::back() {
    if (is_empty()) throw  std::logic_error("Vector is empty!\n");
    size_t index = recalc_index(_size - 1);
    return _data[index];
}

template <class T>
inline T* TVector<T>::begin() noexcept {
    return _data;
}

template <class T>
inline T* TVector<T>::end() noexcept {
    return _data + _size + _deleted;
}

template <class T>
inline const T* TVector<T>::data() const noexcept {
    return _data;
}

template <class T>
inline  size_t TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
inline  size_t TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <class T>
inline const T& TVector<T>::front() const {
    if (is_empty()) throw std::logic_error("Vector is empty!\n");
    size_t index = recalc_index(0);
    return _data[index];
}

template <class T>
inline const T& TVector<T>::back() const {
    if (is_empty()) throw  std::logic_error("Vector is empty!\n");
    size_t index = recalc_index(_size - 1);
    return _data[index];
}

template <class T>
inline const T* TVector<T>::begin() const noexcept {
    _data;
}

template <class T>
inline const T* TVector<T>::end() const noexcept {
    _data + _size + _deleted;
}

template <class T>
inline bool TVector<T>::is_full() const noexcept {
    return (_size + _deleted) >= _capacity;
}

template <class T>
void TVector<T>::push_front(const T& value) noexcept {
    _size++;
    if (is_full()) reset_memory();

    for (int i = _size + _deleted - 1; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = busy;
}

template <class T>
void TVector<T>::push_back(const T& value) noexcept {
    _size++;
    if (is_full()) reset_memory();
    _data[_size + _deleted - 1] = value;
    _states[_size + _deleted - 1] = busy;
}

template <class T>
void TVector<T>::insert(size_t index, const T& value) {
    if (index > _size + _deleted) throw std::logic_error("Index out of range!\n");

    if (index == 0) {
        push_front(value);
        return;
    }

    if (index == _size + _deleted) {
        push_back(value);
        return;
    }

    _size++;
    if (is_full()) reset_memory();
    index = recalc_index(index);
    for (size_t i = _size + _deleted; i > index; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[index] = value;
    _states[index] = busy;
}

template <class T>
void TVector<T>::insert(size_t index, size_t count, const T& value) {
    if (index > _size + _deleted || index < 0) throw std::logic_error("Index out of range!\n");

    _size += count;
    if (is_full()) reset_memory();
    for (size_t i = _size + _deleted; i > index + count; i--) {
        _data[i] = _data[i - 1 - count];
        _states[i] = _states[i - 1 - count];
    }

    for (size_t i = index, count_insrtd = 0; count_insrtd < count; i++, count_insrtd++) {
        _data[i] = value;
        _states[i] = busy;
    }
}

template <class T>
void TVector<T>::insert(size_t index, std::initializer_list<T> data) {
    if (index > _size + _deleted || index < 0) throw std::logic_error("Index out of range!\n");
    _size += data.size();
    if (is_full()) reset_memory();
    index = recalc_index(index);
    for (size_t i = _size + _deleted; i > index; i--) {
        _data[i] = _data[i - data.size()];
        _states[i] = _states[i  - data.size()];
    }

    auto it = data.begin();
    for (size_t i = index, count_insrtd = 0; count_insrtd < data.size(); i++, count_insrtd++) {
        _data[i] = *it;
        _states[i] = busy;
        it++;
    }
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty()) throw std::logic_error("Vector is empty!\n");
    _size--;
    _deleted++;
    size_t index = recalc_index(0);
    _states[index] = deleted;
    reset_memory_for_delete();
}

template <class T>
void TVector<T>::pop_back() {
    if (is_empty()) throw std::logic_error("Vector is empty!\n");
    _size--;
    _states[_size + _deleted] = empty;
}

template <class T>
void TVector<T>::erase(size_t index) {
    if (index<0 || index >= _size+_deleted)throw std::logic_error("Index out of range!\n");
    if (index == 0) {
        pop_front();
        return;
    }
    if (index == _size + _deleted - 1) {
        pop_back();
        return;
    }
    size_t calc_pos = recalc_index(index);
    _states[calc_pos] = deleted;
    _deleted++;
    _size--;
    reset_memory_for_delete();
}

template <class T>
void TVector<T>::erase(size_t index, size_t count) {
    if (index + count >= _size + _deleted) throw std::logic_error("Index out of range!");
    if (index == _size + _deleted - 1 && count == 1) pop_back();
    else {
        _size -= count;
        size_t pos = recalc_index(index);
        _deleted += count;
        for (size_t i = pos, j = 0; j < count; i++, j++) {
            while (_states[i] == deleted) i++;
            _states[i] = deleted;
        }
    }
    reset_memory_for_delete();
}

template<class T>
void TVector<T>::replace(size_t index, const T& value) {
    if (index >= _size + _deleted || index < 0) throw std::logic_error("Index out of range!\n");
    size_t pos = recalc_index(index);
    _data[pos] = value;
}

template<class T>
void TVector<T>::replace(T* index, const T& value) {
    if (index < begin() || index >= end()) throw std::logic_error("Index out of range!\n");
    if (_states[index - data()] == deleted) throw std::logic_error("Doesn`t exist");
    *index = value;

}

template <class T>
void TVector<T>::clear() {
    if (_size == 0) return;
    set_memory(0);
    for (int i = 0; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) noexcept {
    if (this != &other) {
        set_memory(other._size);

        size_t j = 0;
        for (size_t i = 0; i < other._size + other._deleted; i++) {
            if (other._states[i] == busy) {
                _data[j] = other._data[i];
                _states[j] = busy;
                j++;
            }
        }
        for (; j < _capacity; j++) {
            _states[j] = empty;
        }
    }
    return *this;
}

template <class T>
bool TVector<T>::operator==(const TVector<T>& other) const noexcept {
    if (_size != other._size) return false;
    for (size_t i = 0, j = 0; i < _size + _deleted; i++, j++) {
        while (_states[i] != busy) i++;
        while (other._states[j] != busy) j++;
        if (_data[i] != other._data[j]) return false;
    }
    return true;
}

template <class T>
bool TVector<T>::operator!=(const TVector<T>& other) const noexcept {
    return !(*this == other);
}

template <class T>
T& TVector<T>::operator[](size_t index) noexcept {
    size_t pos = recalc_index(index);
    return _data[pos];
}

template <class T>
const T& TVector<T>::operator[](size_t index) const noexcept {
    size_t pos = recalc_index(index);
    return _data[pos];
}

template<class T>
void TVector<T>::assign(size_t size, const T& value) noexcept {
    _deleted = 0;
    _size = size;
    if (is_full()) {
        set_memory(size);
    }
    size_t i = 0;
    for (; i < _size; i++) {
        _data[i] = value;
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T>
void TVector<T>::assign(std::initializer_list<T> data) noexcept {
    _deleted = 0;
    _size = data.size();
    if (is_full()) set_memory(_size);
    auto it = data.begin();
    size_t i = 0;
    for (; i < _size; i++, it++) {
        _data[i] = *it;
        _states[i] = busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template <class T>
T& TVector<T>::at(size_t index) {
    if (index >= _size  || index < 0) throw std::logic_error("Index out of range");
    size_t pos = recalc_index(index);
    return _data[pos];
}

template<class T>
const T& TVector<T>::at(size_t index) const {
    if (index >= _size || index < 0) throw std::logic_error("Index out of range");
    size_t pos = recalc_index(index);
    return _data[pos];
}

template <class T>
void TVector<T>::swap_pos(size_t ft, size_t sd)const  noexcept {
    T tmp = _data[ft];
    _data[ft] = _data[sd];
    _data[sd] = tmp;
}

template <class T>
size_t TVector<T>::rand_generation(size_t min, size_t max) const noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(gen);
}

template <class T>
void shuffle(TVector<T>& data) {
    if (data._size <= 1) return;
    size_t i = 0,  rand_i;
    for (; i < data._size + data._deleted; i++) {
        if (data._states[i] == busy) {
            do {
                rand_i = data.rand_generation(0, data._size + data._deleted);
            } while (data._states[rand_i] != busy);
            data.swap_pos(i, rand_i);
        }
    }
}

template <class T>
void hoara_sort(TVector<T>& data) noexcept {
    if (data._size <= 1) return;
    hoara_sort_rec(data, 0, data._size + data._deleted - 1);
}

template <class T>
void hoara_sort_rec(TVector<T>& data, size_t left, size_t right) {
    while (data._states[left] != busy) left++;
    if (left < right) {
        size_t l = left, r = right;
        size_t base_pos = (left + right) * 0.5;
        while (data._states[left] != busy) base_pos++;
        T base_value = data._data[base_pos];
        while (l <= r) {
            while (data._data[l] < base_value || data._states[l] != busy) l++;
            while (data._data[r] > base_value || data._states[r] != busy) r--;

            if (l < r) {
                data.swap_pos(l, r);
                l++; r--;
            }
            else { break; }
        }
        hoara_sort_rec(data, left, r);
        hoara_sort_rec(data, r + 1, right);
    }
}

template <class T>
size_t find_first_elem(const TVector<T>& data,T value) {
    if (data._size != 0) {
        size_t index = 0;
        for (size_t i = 0; i < data._size + data._deleted; i++) {
            if (data._data[i] == value && data._states[i] == busy) {
                index = data.recalc_index(i);
                return index;
            }
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
size_t find_last_elem(const TVector<T>& data, T value){
    if (data.size() != 0) {
        size_t index = 0;
        for (size_t i = data._size + data._deleted - 1; i > 0; i--) {
            if (data._data[i] == value && data._states[i] == busy) {
                index = data.recalc_index(i);
                return index;
            }
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
TVector<T> find_all(const TVector<T>& data, T value) {
    if (data._size != 0) {
        size_t size = 0;
        for (size_t i = 0; i < data._size + data._deleted; i++) {
            if (data._data[i] == value && data._states[i] == busy) size++;
        }
        if (size != 0) {
            TVector<T> result(size);
            for (size_t i = 0, j = 0; j < size; i++) {
                if (data._data[i] == value && data._states[i] == busy) {
                    result[j] = data.recalc_index(i);
                    j++;
                }
            }
            return result;
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
T* find_first_ptr(const TVector<T>& data, T value) {
    if(data._size != 0) {
        for (size_t i = 0; i < data._size + data._deleted; i++) {
            if (data._data[i] == value && data._states[i] == busy) {
                return data._data + i;
            }
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
T* find_last_ptr(const TVector<T>& data, T value) {
    if (data._size != 0) {
        for (int i = data._size + data._deleted - 1; i > 0; i--) {
            if (data._data[i] == value && data._states[i] == busy) {
                return data._data + i;
            }
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
TVector<T*> find_all_ptrs(const TVector<T>& data, T value) {
    if (data._size != 0) {
        size_t size = 0;
        for (size_t i = 0; i < data._size + data._deleted; i++) {
            if (data._data[i] == value && data._states[i] == busy) size++;
        }
        if (size != 0) {
            TVector<T*> result(size);
            for (size_t i = 0, j = 0; i < data._size + data._deleted; i++) {
                if (data._data[i] == value && data._states[i] == busy) {
                    result[j] = data._data + i;
                    j++;
                }
            }
            return result;
        }
    }
    throw std::logic_error("Element wasn`t found!\n");
}

template <class T>
size_t TVector<T>::recalc_index(size_t index) const noexcept{
    if (_deleted == 0) return index;
    size_t busy_pos = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (busy_pos == index) return i;
            busy_pos++;
        }
    }
}

template <class T>
TVector<T>::~TVector() {
    if (_data != nullptr) delete[] _data;
    if (_states != nullptr) delete[] _states;
}