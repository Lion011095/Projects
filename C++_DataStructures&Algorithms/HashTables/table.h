#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table
{
public:
    Table() {}
    virtual bool update(const std::string& key, const TYPE& value) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual bool find(const std::string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE>
{

    struct Record
    {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }

    };

    Record** records_;   //the table
    int capacity_ = 0;       //capacity of the array


public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const {
        return numRecords() == 0;
    }
    virtual int numRecords() const;
    virtual int capacity() const {
        return capacity_;
    }

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
    int rc = 0;
    for (int i = 0; records_[i] != nullptr; i++) {
        rc++;
    }
    return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
    records_ = new Record * [capacity + 1];
    capacity_ = capacity;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
    records_ = new Record * [rhs.capacity_ + 1];
    capacity_ = rhs.capacity_;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++) {
        update(rhs.records_[i]->key_, rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
    capacity_ = rhs.capacity_;
    records_ = rhs.records_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
    int idx = -1;
    int sz = numRecords();
    bool rc = true;
    for (int i = 0; i < sz; i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1) {
        if (sz < capacity_) {
            records_[numRecords()] = new Record(key, value);
            for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) {
                Record* tmp = records_[i];
                records_[i] = records_[i - 1];
                records_[i - 1] = tmp;
            }
        }
        else {
            rc = false;
        }
    }
    else {
        records_[idx]->data_ = value;
    }
    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
    int idx = -1;
    for (int i = 0; records_[i] != nullptr; i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx != -1) {
        delete records_[idx];

        for (int i = idx; i < (numRecords() - 1); i++) {
            records_[i] = records_[i + 1];
        }
        records_[capacity_ - 1] = nullptr;
        return true;
    }
    else {
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
    int idx = -1;
    for (int i = 0; i < numRecords(); i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1)
        return false;
    else {
        value = records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs) {
    if (this != &rhs) {
        if (records_) {
            while (numRecords() != 0) {
                remove(records_[0]->key_);
            }
            delete[] records_;
        }
        records_ = new Record * [rhs.capacity_ + 1];
        capacity_ = rhs.capacity_;
        for (int i = 0; i < capacity_; i++) {
            records_[i] = nullptr;
        }
        for (int i = 0; i < rhs.numRecords(); i++) {
            update(rhs.records_[i]->key_, rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
    if (records_) {
        while (numRecords() != 0) {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
    records_ = rhs.records_;
    capacity_ = rhs.capacity_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
    if (records_) {
        int sz = numRecords();
        for (int i = 0; i < sz; i++) {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
}

template <class TYPE>
class ChainingTable :public Table<TYPE>
{
    struct RecordNode
    {
        TYPE data_;
        std::string key_;
        RecordNode* next;
        RecordNode* prev;
        RecordNode(const std::string& key, const TYPE& data, RecordNode* nextNode, RecordNode* prevNode){
            key_ = key;
            data_ = data;
            next = nextNode;
            prev = prevNode;
        }
    };

    std::hash<std::string> hashFunction;
    RecordNode** records_;
    int numOfRecords;
    int capacity_;

public:
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>() {
    records_ = new RecordNode* [capacity + 1];
    capacity_ = capacity;
    numOfRecords = 0;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
    records_ = new RecordNode * [other.capacity_ + 1];
    capacity_ = other.capacity_;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
    for (int i = 0; i < capacity_; i++) {
        if (other.records_[i] != nullptr) {
            RecordNode* node = other.records_[i];
            while (node != nullptr) {
                update(node->key_, node->data_);
                node = node->next;
            }
        }
    }
}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
    capacity_ = other.capacity_;
    records_ = other.records_;
    numOfRecords = other.numOfRecords;
    other.records_ = nullptr;
    other.capacity_ = 0;
}
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string& key, const TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    RecordNode* node = records_[idx];
    bool updated = false;
    if (node == nullptr) {
        node = new RecordNode(key,value, nullptr,nullptr);
        records_[idx] = node;
        numOfRecords++;
    }
    else {
        while (!updated) {
            if (node->key_ == key) {
                node->data_ = value;
                updated = true;
            }
            else if (node->key_ != key && node->next == nullptr) {
                node = new RecordNode(key, value, nullptr, node);
                node->prev->next = node;
                updated = true;
                numOfRecords++;
            }
            node = node->next;
        }
    }

    return true;
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    RecordNode* node = records_[idx];
    bool deleted = false;
    if (node == nullptr) {
        return deleted;
    }
    while (node != nullptr && !deleted) {
        if (node->next != nullptr && node->next->key_ == key) {
            RecordNode* del = node->next;
            node->next = node->next->next;
            if (node->next != nullptr) {
                node->next->prev = node;
            }
            delete del;
            deleted = true;
        }
        else if (node->key_ == key) {
            records_[idx] = node->next;
            delete node;
            node = nullptr;
            deleted = true;
        }
        if (!deleted) {
            node = node->next;
        }
        else {
            numOfRecords--;
        }
    }

    return deleted;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    RecordNode* node = records_[idx];
    if (node == nullptr) {
        return false;
    }
    else {
        while (node != nullptr) {
            if (node->key_ == key) {
                value = node->data_;
                return true;
            }
            node = node->next;
        }
    }
    return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
    if (this != &other) {
        if (records_) {
            for (int i = 0; i < capacity_; i++) {
                RecordNode* node = records_[i];
                while (node != nullptr) {
                    remove(node->key_);
                    node = records_[i];
                }
                records_[i] = nullptr;
            }
            delete[] records_;
        }
        records_ = new RecordNode * [other.capacity_ + 1];
        capacity_ = other.capacity_;
        for (int i = 0; i < capacity_; i++) {
            records_[i] = nullptr;
        }
        for (int i = 0; i < capacity_; i++) {
            if (other.records_[i] != nullptr) {
                RecordNode* node = other.records_[i];
                while (node != nullptr) {
                    update(node->key_, node->data_);
                    node = node->next;
                }
            }
        }
    }
    return *this;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
    if (this != &other)
    {
        if (records_) {
            for (int i = 0; i < capacity_; i++) {
                RecordNode* node = records_[i];
                while (node != nullptr) {
                    remove(node->key_);
                    node = records_[i];
                }
                records_[i] = nullptr;
            }
            delete[] records_;
        }
        capacity_ = other.capacity_;
        records_ = other.records_;
        numOfRecords = other.numOfRecords;
        other.records_ = nullptr;
        other.capacity_ = 0;
    }
    return *this;
}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
    if (numOfRecords > 0) {
        int sz = capacity_;
        for (int i = 0; i < sz; i++) {
            while (records_[i] != nullptr && records_[i]->next != nullptr) {
                remove(records_[i]->key_);
            }
            if(records_[i] != nullptr)
                remove(records_[i]->key_);
        }
    }
    delete[] records_;
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    if (numOfRecords > 0) {
        return false;
    }
    return true;
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return numOfRecords;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
    return numOfRecords / capacity_;
}



template <class TYPE>
class LPTable :public Table<TYPE>
{
    struct Record
    {
        TYPE data_;
        std::string key_;
        std::string tombstone;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
        Record(const std::string status) {
            tombstone = status;
        }
    };

    std::hash<std::string> hashFunction;
    int numOfRecords;
    Record** records_;   
    int capacity_;       

public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>() {
    records_ = new Record * [capacity + 1];
    capacity_ = capacity;
    numOfRecords = 0;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = new Record("empty");
    }
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
    records_ = new Record * [other.capacity_ + 1];
    capacity_ = other.capacity_;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = new Record("empty");
    }
    for (int i = 0; i < capacity_; i++) {
        if (other.records_[i]->tombstone == "filled")
            update(other.records_[i]->key_, other.records_[i]->data_);
        else if (other.records_[i]->tombstone == "deleted")
            records_[i]->tombstone = "deleted";
    }
}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
    capacity_ = other.capacity_;
    records_ = other.records_;
    numOfRecords = other.numOfRecords;
    other.records_ = nullptr;
    other.capacity_ = 0;
    other.numOfRecords = 0;
}
template <class TYPE>
bool LPTable<TYPE>::update(const std::string& key, const TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    bool updated = false;

    while (records_[idx]->tombstone == "filled" && records_[idx]->key_ != key) {
        idx++;
        idx %= capacity_;
    }
    if (records_[idx]->tombstone == "empty" || records_[idx]->tombstone == "deleted") {
        if ((capacity_ - 1) > numRecords()) {
            delete records_[idx];
            records_[idx] = new Record(key, value);
            records_[idx]->tombstone = "filled";
            updated = true;
            numOfRecords++;
        }
        else{
            return updated;
        }
    }
    else {
        records_[idx]->data_ = value;
        updated = true;
    }
    return updated;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    while (records_[idx]->tombstone == "filled" || records_[idx]->tombstone == "deleted") {
        if (records_[idx]->key_ == key) {
            delete records_[idx];
            records_[idx] = new Record("deleted");
            return true;
        }
        idx++;
        idx %= capacity_;
    }
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value) {

    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    
    while (records_[idx]->tombstone == "filled" || records_[idx]->tombstone == "deleted") {
        if (records_[idx]->key_ == key) {
            value = records_[idx]->data_;
            return true;
        }
        else {
            idx++;
            idx %= capacity_;
        }
    }
    return false;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
    if (this != &other) {
        if (records_) {
            for (int i = 0; i < capacity_; i++) {
                if (records_[i] != nullptr) {
                    delete records_[i];
                }
            }
            delete[] records_;
        }
        records_ = new Record * [other.capacity_ + 1];
        capacity_ = other.capacity_;
        numOfRecords = 0;
        for (int i = 0; i < capacity_ + 1; i++) {
            records_[i] = new Record("empty");
        }
        for (int i = 0; i < capacity_; i++) {
            if (other.records_[i]->tombstone == "filled")
                update(other.records_[i]->key_, other.records_[i]->data_);
            else if (other.records_[i]->tombstone == "deleted")
                records_[i]->tombstone = "deleted";
        }
    }
    return *this;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
    if (this != &other)
    {
        if (records_) {
            for (int i = 0; i < capacity_; i++) {
                if (records_[i] != nullptr) {
                    delete records_[i];
                }
            }
            delete[] records_;
        }
        records_ = other.records_;
        capacity_ = other.capacity_;
        numOfRecords = other.numOfRecords;
        other.records_ = nullptr;
        other.capacity_ = 0;
        other.numOfRecords = 0;
    }
    return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable() {
    for (int i = 0; i < capacity_; i++) {
        if (records_[i] != nullptr) {
            delete records_[i];
        }
    }
    delete[] records_;
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    if (numRecords() == 0) {
        return true;
    }
    return false;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return numOfRecords;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return capacity_;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return numRecords() / capacity_;
}
