#include <iostream>
#include <vector>
#include <string>

template<class T, class H>
class HashTable {
public:
    HashTable(int initialSize, const H& hasher);
    ~HashTable() = default;

    bool Has(const T& key);

    bool Add(const T& key);

    bool Delete(const T& key);

private:
    H hasher;
    enum CellState {Empty, Key, Deleted};
    struct HashTableCell {
        T Key;
        unsigned int Hash;
        CellState State;
        HashTableCell() : Hash(0), State(Empty) {}
    };
    std::vector<HashTableCell> table;
    unsigned int keysCount;
    unsigned int deletedCount;

    void growTable();
    void rebuildTable();
};

template<class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H& _hasher) :
        hasher(_hasher),
        keysCount(0),
        deletedCount(0)
{
    std::vector<HashTableCell> newTable(initialSize);
    for (int i = 0; i < initialSize; ++i) {
        HashTableCell cell;
        newTable[i] = cell;
    }
    table = std::move(newTable);
}

template<class T, class H>
bool HashTable<T, H>::Has(const T &key) {
    if(3 * deletedCount >= table.size()) {
        if (4 * keysCount >= 3 * table.size()) {
            growTable();
        } else {
            rebuildTable();
        }
    }

    unsigned int ListIndex = hasher(key) % table.size();
    HashTableCell cell = table[ListIndex];
    for (int i = 1; cell.State != Empty && !(cell.Key == key && cell.State == Key); ++i) {
        ListIndex = (ListIndex + i) % table.size();
        cell = table[ListIndex];
    }

    if (cell.State != Key) {
        return false;
    }
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Add(const T &key) {
    if (4 * (keysCount + 1) >= 3 * table.size()) {
        growTable();
    }
    unsigned int hash = hasher(key);
    unsigned int listIndex = hash % table.size();
    HashTableCell cell = table[listIndex];
    unsigned int firstDeleted = -1;
    for (int i = 1; cell.State != Empty && !(cell.Key == key && cell.State == Key); ++i) {
        if (cell.State == Deleted && firstDeleted == -1) {
            firstDeleted = listIndex;
        }
        listIndex = (listIndex + i) % table.size();
        cell = table[listIndex];
    }

    if (cell.State == Key) {
        return false;
    }
    if (firstDeleted != -1) {
        listIndex = firstDeleted;
    }
    cell.Key = key;
    cell.State = Key;
    cell.Hash = hash;
    table[listIndex] = cell;
    ++keysCount;
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T &key) {
    if (4 * (deletedCount + 1) > table.size()) {
        rebuildTable();
    }
    unsigned int ListIndex = hasher(key) % table.size();
    HashTableCell cell = table[ListIndex];
    for (int i = 1; cell.State != Empty && !(cell.Key == key && cell.State == Key); ++i) {
        ListIndex = (ListIndex + i) % table.size();
        cell = table[ListIndex];
    }

    if (cell.State != Key) {
        return false;
    }
    cell.State = Deleted;
    table[ListIndex] = cell;
    --keysCount;
    ++deletedCount;
    return true;
}

template<class T, class H>
void HashTable<T, H>::growTable() {
    std::vector<HashTableCell> newTable(table.size() * 2);
    for (int i = 0; i < table.size(); ++i) {
        HashTableCell cell = table[i];
        if (cell.State == Key) {
            unsigned int hash = cell.Hash;
            unsigned int listIndex = hash % newTable.size();
            HashTableCell tempCell = newTable[listIndex];
            for (int j = 1; tempCell.State != Empty; ++j) {
                listIndex = (listIndex + j) % newTable.size();
                tempCell = newTable[listIndex];
            }
            newTable[listIndex] = cell;
        }
    }
    deletedCount = 0;
    table = std::move(newTable);
}

template<class T, class H>
void HashTable<T, H>::rebuildTable() {
    std::vector<HashTableCell> newTable(table.size());
    for (int i = 0; i < table.size(); ++i) {
        HashTableCell cell = table[i];
        if (cell.State == Key) {
            unsigned int hash = cell.Hash;
            unsigned int listIndex = hash % newTable.size();
            HashTableCell tempCell = newTable[listIndex];
            for (int j = 1; tempCell.State != Empty; ++j) {
                listIndex = (listIndex + j) % newTable.size();
                tempCell = newTable[listIndex];
            }
            newTable[listIndex] = cell;
        }
    }
    deletedCount = 0;
    table = std::move(newTable);
}

struct StringHasher {
    unsigned int operator()(const std::string& key) const {
        unsigned int hash = 0;
        for (int i = 0; i < key.size(); ++i) {
            hash = hash * 137 + key[i];
        }
        return hash;
    }
};

int main() {
    StringHasher hasher;
    HashTable<std::string, StringHasher> table(8, hasher);
    char operation = 0;
    std::string word;
    while(std::cin >> operation >> word) {
        switch (operation) {
            case '+':
                std::cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}