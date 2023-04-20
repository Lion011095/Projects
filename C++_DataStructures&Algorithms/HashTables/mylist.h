#include <utility>

using namespace std;

template <typename T>
class DList
{
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	class const_iterator
	{
		friend class DList;
		const DList* sDList_;
		Node* curr_;
		const_iterator(Node* n, const DList* list) {
			curr_ = n;
			sDList_ = list;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			sDList_ = nullptr;
		}
		const_iterator& operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator& operator--() {
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (sDList_) {
					curr_ = sDList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (sDList_) {
					curr_ = sDList_->back_;
				}
			}
			return old;
		}
		bool operator==(const_iterator rhs) {
			bool isEqual = false;
			if (sDList_ == rhs.sDList_ && curr_ == rhs.curr_) {
				isEqual = true;
			}
			return isEqual;
		}
		bool operator!=(const_iterator rhs) {
			return !(*this == rhs);
		}
		const T& operator*()const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator
	{
		friend class DList;
		iterator(Node* curr, DList* theList) :const_iterator(curr, theList) {}
	public:
		iterator() : const_iterator() {}
		iterator& operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator& operator--() {
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->sDList_) {
					this->curr_ = this->sDList_->back_;
				}
			}
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->sDList_) {
					this->curr_ = this->sDList_->back_;
				}
			}
			return old;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	DList();
	~DList();
	DList(const DList& rhs);
	DList& operator=(const DList& rhs);
	DList(DList&& rhs);
	DList& operator=(DList&& rhs);
	iterator insert(iterator it, const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	void swap(iterator lhs, iterator rhs);
	void sort(iterator first, iterator last);
	bool empty() const;
	int size() const;

	iterator begin() {
		return iterator(front_->next_, this);
	}
	iterator end() {
		return iterator(back_, this);
	}
	const_iterator cbegin() const {
		return const_iterator(front_->next_, this);
	}
	const_iterator cend() const {
		return const_iterator(back_, this);
	}
};

template <typename T>
DList<T>::DList() {
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
}
template <typename T>
DList<T>::~DList() {
	while (front_ != nullptr && front_->next_ != back_)
	{
		Node* rm = front_->next_;
		front_->next_ = front_->next_->next_;
		delete rm;
	}
	delete front_;
	delete back_;
	front_ = nullptr;
	back_ = nullptr;
}

template <typename T>
DList<T>::DList(const DList& rhs) {
	operator=(rhs);
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs) {
	if (this != &rhs) {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
		if (rhs.front_->next_ != rhs.back_) {
			Node* addNode = rhs.front_;
			iterator it = this->begin();
			while (addNode->next_ != rhs.back_) {
				addNode = addNode->next_;
				it = insert(it, addNode->data_);
				it++;
			}
		}
	}

	return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs) {
	front_ = nullptr;
	back_ = nullptr;
	*this = std::move(rhs);
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) {
	if (this != &rhs) {
		front_ = rhs.front_;
		back_ = rhs.back_;
		rhs.front_ = nullptr;
		rhs.back_ = nullptr;
	}
	return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data) {
	Node* newNode = new Node(data, it.curr_, it.curr_->prev_);
	it.curr_->prev_->next_ = newNode;
	it.curr_->prev_ = newNode;
	it--;
	return it;
}

template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) {
	DList<T>::iterator it;
	for (it = this->begin(); it != this->end(); it++)
	{
		if (*it == data)
		{
			return it;
		}
	}
	return it;
}

template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it) {
	it.curr_->next_->prev_ = it.curr_->prev_;
	it.curr_->prev_->next_ = it.curr_->next_;
	it++;

	return it;
}

template <typename T>
void DList<T>::swap(iterator lhs, iterator rhs) {

	Node* temp = rhs.curr_->next_;
	rhs.curr_->next_ = lhs.curr_->next_;
	lhs.curr_->next_ = temp;
	rhs.curr_->next_->prev_ = rhs.curr_;
	lhs.curr_->next_->prev_ = lhs.curr_;

	temp = rhs.curr_->prev_;
	rhs.curr_->prev_ = lhs.curr_->prev_;
	lhs.curr_->prev_ = temp;
	rhs.curr_->prev_->next_ = rhs.curr_;
	lhs.curr_->prev_->next_ = lhs.curr_;
}

template <typename T>
void DList<T>::sort(iterator first, iterator last) {
	iterator min;
	iterator current = first;
	iterator temp;

	for (iterator i = first; i != last; i++) {
		min = i;
		for (iterator j = i; j != last; ++j) {
			if (*j < *min) {
				min = j;
			}
		}
		if (min != i) {
			swap(i, min);
		}
		i = min;
	}
}

template <typename T>
bool DList<T>::empty() const {
	return back_->prev_ == front_;
}

template <typename T>
int DList<T>::size() const {
	Node* thisNode = front_->next_;
	int size = 0;
	while (thisNode != back_) {
		size++;
		thisNode = thisNode->next_;
	}
	return size;
}
