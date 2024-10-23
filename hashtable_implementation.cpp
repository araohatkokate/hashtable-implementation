#include <iostream>
#include <cmath>

const float LOAD_FACTOR_THRESHOLD = 0.75;
const float SHRINK_THRESHOLD = 0.25;

// Doubly Linked List Node for chaining
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

// Hash Table class
class HashTable {
private:
    Node** table;
    int capacity;
    int size;

    // Hash function (Multiplication and Division Method)
    int hash(int key) {
        float A = 0.618033; // Constant fraction (A) used for multiplication
        float fracPart = key * A - (int)(key * A); // Fractional part
        return (int)(capacity * fracPart); // Multiplication method
    }

    // Resize hash table to a new capacity
    void resize(int newCapacity) {
        Node** oldTable = table;
        int oldCapacity = capacity;
        
        table = new Node*[newCapacity];
        capacity = newCapacity;
        size = 0;

        for (int i = 0; i < newCapacity; i++) {
            table[i] = nullptr;
        }

        // Rehash all elements
        for (int i = 0; i < oldCapacity; i++) {
            Node* current = oldTable[i];
            while (current != nullptr) {
                insert(current->key, current->value); // Rehash to new table
                current = current->next;
            }
        }
        delete[] oldTable; // Free the old table
    }

public:
    // Constructor
    HashTable(int initialCapacity = 8) : capacity(initialCapacity), size(0) {
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }

    // Insert key-value pair
    void insert(int key, int value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr && current->key != key) {
                current = current->next;
            }
            if (current->key == key) {
                current->value = value; // Update value if key already exists
                delete newNode;
            } else {
                current->next = newNode;
                newNode->prev = current;
            }
        }

        size++;

        // Check if resizing is needed
        if ((float)size / capacity > LOAD_FACTOR_THRESHOLD) {
            resize(capacity * 2);
        }
    }

    // Remove a key
    void remove(int key) {
        int index = hash(key);
        Node* current = table[index];

        while (current != nullptr && current->key != key) {
            current = current->next;
        }

        if (current != nullptr) { // Key found
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            delete current;
            size--;

            // Check if shrinking is needed
            if (size > 0 && (float)size / capacity < SHRINK_THRESHOLD) {
                resize(capacity / 2);
            }
        }
    }

    // Find value by key
    int find(int key) {
        int index = hash(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return -1; // Key not found
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < capacity; i++) {
            std::cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << "(" << current->key << ", " << current->value << ") <-> ";
                current = current->next;
            }
            std::cout << "NULL" << std::endl;
        }
    }
};

// Testing the hash table
int main() {
    HashTable ht;

    ht.insert(10, 100);
    ht.insert(20, 200);
    ht.insert(30, 300);
    ht.insert(40, 400);
    ht.insert(50, 500);

    std::cout << "Hash table after insertions:" << std::endl;
    ht.display();

    ht.remove(30);
    std::cout << "\nHash table after removing key 30:" << std::endl;
    ht.display();

    std::cout << "\nValue for key 40: " << ht.find(40) << std::endl;

    return 0;
}
