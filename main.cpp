#include <iostream>
#include "src/RichList.h"

using namespace std;

int main() {
    RichList<int> richList;
    richList.Add(10)->Add(11)->Add(12)->Add(13)->Add(14)->Add(15)->Add(16)->Add(17)->Previous()->Remove()->Remove(14)->Add(18);

    cout << "Item 0: " << richList.Get(0)->value << endl;
    cout << "Item 1: " << richList.Get(1)->value << endl;
    cout << "Item 2: " << richList.Get(2)->value << endl;
    cout << "First: " << richList.First()->value << endl;
    cout << "Last: " << richList.Last()->value << endl;
    cout << "Mid -1: " << richList.Get(1)->Previous()->value << endl;
    cout << "Mid +1: " << richList.Get(1)->Next()->value << endl;

    cout << "All items before:" << endl;

    richList.ForEach([](auto& item) {
        cout << "Item value: " << item << endl;
        item++;
    });

    cout << "All items after:" << endl;

    richList.ForEach([](auto item) {
        cout << "Item value: " << item << endl;
    });

    return 0;
}
