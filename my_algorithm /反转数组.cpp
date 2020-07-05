#include <iostream>
#include <vector>

using namespace std;

void reverse(int array[], int size) {
    for (int i = 0; i <= (size - 1)/2; i++) {
        int temp = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = temp;
    }
}

void reverseString(vector<char>& s) {
    int size = s.size();
    
    for (int i = 0; i <= (size - 1)/2; i++) {
        char temp = s[i];
        s[i] = s[size - 1 - i];
        s[size - 1 - i] = temp;
    }
}

int main() {
    int array[5] = {0, 1, 2, 3, 4};
    reverse(array, 5);

    for (const auto& i : array) {
        cout<<i<<",";
    }
    cout<<endl;
}