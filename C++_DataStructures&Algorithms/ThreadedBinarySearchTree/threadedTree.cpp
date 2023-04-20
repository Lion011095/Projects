#include <iostream>

using namespace std;

template <class T>
class ThreadedTree
{
	struct Node
	{
		T data_;
		Node* left_;
		Node* right_;
		bool hasLeftThread;
		bool hasRightThread;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
			hasLeftThread = true;
			hasRightThread = true;
		}
	};

	int treeSize;
	Node* root_;

	void destroy(Node* subtree) {
		if (subtree != nullptr) {
			if (!subtree->hasLeftThread && !subtree->hasRightThread) {
				destroy(subtree->left_);
				destroy(subtree->right_);
			}
			delete subtree;
		}
	}

public:
	class const_iterator
	{
		friend class ThreadedTree;
	protected:
		const ThreadedTree* myTree_;
		Node* curr_;
		const_iterator(Node* curr, const ThreadedTree* theTree) {
			curr_ = curr;
			myTree_ = theTree;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			myTree_ = nullptr;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			if (this->curr_->hasRightThread) {
				this->curr_ = this->curr_->right_;
				return old;
			}
			this->curr_ = this->curr_->right_;
			while (!this->curr_->hasLeftThread) {
				this->curr_ = this->curr_->left_;

			}
			return old;
			
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			if (this->curr_) {
				if (this->curr_->hasLeftThread) {
					this->curr_ = this->curr_->left_;
					return old;
				}
				this->curr_ = this->curr_->left_;
				while (!this->curr_->hasRightThread) {
					this->curr_ = this->curr_->right_;
				}
			}
			else {
				this->curr_ = this->myTree_->root_;
				while (this->curr_->right_) {
					this->curr_ = this->curr_->right_;
				}
			}
			return old;
		}
		const_iterator operator++() {
			if (this->curr_->hasRightThread) {
				this->curr_ = this->curr_->right_;
				return *this;
			}
			this->curr_ = this->curr_->right_;
			while (!this->curr_->hasLeftThread) {
				this->curr_ = this->curr_->left_;

			}
			return *this;
		}
		const_iterator operator--() {
			if (this->curr_) {
				if (this->curr_->hasLeftThread) {
					this->curr_ = this->curr_->left_;
					return *this;
				}
				this->curr_ = this->curr_->left_;
				while (!this->curr_->hasRightThread) {
					this->curr_ = this->curr_->right_;
				}
			}
			else {
				this->curr_ = this->myTree_->root_;
				while (this->curr_->right_) {
					this->curr_ = this->curr_->right_;
				}
			}
			return *this;
		}
		const T& operator*() const {
			return this->curr_->data_;
		}
		bool operator==(const const_iterator& rhs) const {
			if (curr_ && rhs.curr_) {
				if (this->curr_->data_ == rhs.curr_->data_ && this->myTree_ == rhs.myTree_) {
					return true;
				}
			}
			return false;
			
		}
		bool operator!=(const const_iterator& rhs) const {
			if (curr_) {
				if (this->curr_->data_ != rhs.curr_->data_ || this->myTree_ != rhs.myTree_) {
					return true;
				}
			}
			return false;
		}
	};
	class iterator :public const_iterator
	{
		friend class ThreadedTree;
		iterator(Node* curr, ThreadedTree* theTree) : const_iterator(curr, theTree) {}
	public:
		iterator() :const_iterator() {}
		const T& operator*() const {
			return this->curr_->data_;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		iterator operator++(int) {
			iterator old = *this;
			if (this->curr_->hasRightThread) {
				this->curr_ = this->curr_->right_;
				return old;
			}
			this->curr_ = this->curr_->right_;
			while (!this->curr_->hasLeftThread) {
				this->curr_ = this->curr_->left_;
				
			}
			return old;
		}
		iterator operator--(int) {
			iterator old = *this;
			if (this->curr_) {
				if (this->curr_->hasLeftThread) {
					this->curr_ = this->curr_->left_;
					return old;
				}
				this->curr_ = this->curr_->left_;
				while (!this->curr_->hasRightThread) {
					this->curr_ = this->curr_->right_;
				}
			}
			else {
				this->curr_ = this->myTree_->root_;
				while (this->curr_->right_) {
					this->curr_ = this->curr_->right_;
				}
			}
			return old;
		}
		iterator operator++() {
			if (this->curr_->hasRightThread) {
				this->curr_ = this->curr_->right_;
				return *this;
			}
			this->curr_ = this->curr_->right_;
			while (!this->curr_->hasLeftThread) {
				this->curr_ = this->curr_->left_;

			}
			return *this;
		}
		iterator operator--() {
			if (this->curr_) {
				if (this->curr_->hasLeftThread) {
					this->curr_ = this->curr_->left_;
					return *this;
				}
				this->curr_ = this->curr_->left_;
				while (!this->curr_->hasRightThread) {
					this->curr_ = this->curr_->right_;
				}
			}
			else {
				this->curr_ = this->myTree_->root_;
				while (this->curr_->right_) {
					this->curr_ = this->curr_->right_;
				}
			}
			return *this;
		}
	};

	ThreadedTree() {
		root_ = nullptr;
		treeSize = 0;
	}
	void insert(const T& data) {
		if (!root_) {
			root_ = new Node(data);
			treeSize++;
		}
		else {
			bool inserted = false;
			Node* curr = root_;
			Node* parent = root_;
			while (!inserted) {
				parent = curr;
				if (data < curr->data_) {
					if (curr->left_ && !curr->hasLeftThread) {
						curr = curr->left_;
					}
					else {
						curr->left_ = new Node(data,parent->left_,parent);
						parent->hasLeftThread = false;
						inserted = true;
						treeSize++;
					}
				}
				else {
					if (curr->right_ && !curr->hasRightThread) {
						curr = curr->right_;
					}
					else {
						curr->right_ = new Node(data,parent,parent->right_);
						parent->hasRightThread = false;
						inserted = true;
						treeSize++;
					}
				}
			}
		}
	}

	iterator find(const T& key) {
		iterator* it = new iterator (root_, this);
		bool found = false;
		while (!found && it->curr_) {
			if (it->curr_->data_ == key) {
				return *it;
			}
			else if (it->curr_->data_ < key) {
				if (!it->curr_->hasRightThread) {
					it->curr_ = it->curr_->right_;
				}
				else {
					return this->end();
				}
			}
			else {
				if (!it->curr_->hasLeftThread) {
					it->curr_ = it->curr_->left_;
				}
				else {
					return this->end();
				}
			}
		}

		return *it;
	}

	const_iterator find(const T& key) const {
		const_iterator* it = new iterator(root_, this);
		bool found = false;
		while (!found && it->curr_) {
			if (it->curr_->data_ == key) {
				return *it;
			}
			else if (it->curr_->data_ < key) {
				if (!it->curr_->hasRightThread) {
					it->curr_ = it->curr_->right_;
				}
				else {
					return this->cend();
				}
			}
			else {
				if (!it->curr_->hasLeftThread) {
					it->curr_ = it->curr_->left_;
				}
				else {
					return this->cend();
				}
			}
		}

		return *it;
	}

	iterator begin() {
		Node* current = this->root_;
		if (current) {
			while (current->left_) {
				current = current->left_;
			}
		}

		return iterator(current, this);
	}

	iterator end() {
		return iterator(nullptr, this);
	}

	const_iterator cbegin()const {
		Node* current = this->root_;
		if (current) {
			while (current->left_) {
				current = current->left_;
			}
		}

		return const_iterator(current, this);
	}

	const_iterator cend() const {
		
		return const_iterator(nullptr, this);
	}

	int size() const {
		return treeSize;
	}

	bool empty() const {
		return treeSize == 0;
	}

	~ThreadedTree() {
		destroy(root_);
	}
};
