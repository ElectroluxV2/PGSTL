//
// Created by mate on 14.03.2021.
//

#ifndef PGSTL_RICHLIST_H
#define PGSTL_RICHLIST_H

#include <stdexcept>
#include <functional>

using namespace std;

template <class T>
class RichList {
    struct RichNode {
        RichNode* previous = nullptr;
        RichNode* next = nullptr;
        RichList<T>* list = nullptr;
        T value = nullptr;

        // https://stackoverflow.com/a/121216/7132461
        explicit RichNode(RichList<T>* list, T value): value(value), list(list) {};

        ~RichNode() {
            this->previous = nullptr;
            this->next = nullptr;
        }

        [[nodiscard]] bool HasNext() {
            return this->next != nullptr;
        }

        [[nodiscard]] bool HasPrevious() {
            return this->previous != nullptr;
        }

        [[nodiscard]] RichNode* Next() {
            if (!this->HasNext()) {
                throw std::invalid_argument("Accessing null Next() element");
            }

            return this->next;
        }

        [[nodiscard]] RichNode* Previous() {
            return this->previous;
        }

        RichList<T>* Remove() {
            return this->list->Remove(this);
        }

        RichNode* Add(T item) {
            return this->list->Add(item);
        }
    };

    RichNode* first = nullptr;
    RichNode* last = nullptr;
    unsigned long length = 0;


public:
    RichList() = default;

    ~RichList() {
        if (this->length == 0) return;

        auto currentNode = this->first;
        while (currentNode->HasNext()) {
            auto next = currentNode->Next();
            delete currentNode;
            currentNode = next;
        }
    }

    RichNode* Add(T item) {
        auto newNode = new RichNode(this, item);

        if (++length == 1) {
            this->last = this->first = newNode;
        } else {
            newNode->previous = this->last;
            this->last->next = newNode;
            this->last = newNode;
        }

        return newNode;
    }

    RichList<T>* Remove(T item) {
        auto currentNode = this->first;

        while (currentNode->value != item && currentNode->HasNext()) {
            currentNode = currentNode->Next();
        }

        this->Remove(currentNode);
        return this;
    }

    RichList<T>* Remove(RichNode* node) {

        if (node->HasNext() && node->HasPrevious()) {
            node->Previous()->next = node->Next();
            node->Next()->previous = node->Previous();
        } else if (node->HasNext()) {
            node->Next()->previous = nullptr;
        } else if (node->HasPrevious()) {
            node->Previous()->next = nullptr;
        } else {
            // Nothing
        }

        if (node->list->Last() == node) {
            if (node->HasPrevious()) {
                node->list->last = node->Previous();
            } else {
                node->list->last = nullptr;
            }
        }

        if (node->list->First() == node) {
            if (node->HasNext()) {
                node->list->first = node->Next();
            } else {
                node->list->first = nullptr;
            }
        }

        node->list->length--;

        delete node;
        return this;
    }

    void ForEach(function<void(T& item)>lambda) {
        auto currentNode = this->first;
        for (unsigned long currentIndex = 0; currentIndex < this->length; currentIndex++) {

            lambda(currentNode->value);
            currentNode = currentNode->next;
        }
    }

    [[nodiscard]] RichNode* Get(unsigned long index) {
        if (index >= this->length) {
            throw std::invalid_argument(&"Index out of bound: " [ index]);
        }

        auto currentNode = this->first;
        for (unsigned long currentIndex = 0; currentIndex < index; currentIndex++) {
            currentNode = currentNode->next;
        }

        return currentNode;
    }

    [[nodiscard]] RichNode* First() {
        return this->first;
    }

    [[nodiscard]] RichNode* Last() {
        return this->last;
    }

    [[nodiscard]] unsigned long Length() {
        return this->length;
    }
};

#endif //PGSTL_RICHLIST_H
