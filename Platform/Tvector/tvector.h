enum State{empty, busy, deleted};

template <class T>
class TVector {
	T* _data;
	size_t _capacity;
	size_t _size;
public:
	TVector(size_t _size = 0);
	TVector(const TVector<T>&);
	~TVector();

	inline bool is_empty() const noexcept;

private:
	size_t _deleted;
	State* _states;

};

template <class T>
TVector<T>::TVector(size_t _size) {
	_size(0);
	_data = nullptr;
}

template <class T>
TVector<T>::TVector(const TVector<T>& data) {
	for (int i = 0; i < size; i++) {
		_data[i] = data[i];
	}
}

template <class T>
TVector<T>::~TVector() {
	delete[] _data;
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
	if (_data != nullptr)
		return true;
	return false;
}