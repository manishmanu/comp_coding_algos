#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> & arr, int k) {
    int l = 0, r = arr.size() - 1;
    while(l<=r) {
        int mid = l + (r - l) / 2;
        if(k<arr[mid]) {
            r = mid - 1;
        } else if(k>arr[mid]) {
            l = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int upper_bound(vector<int>& arr, int k) {
    int l = 0, r = arr.size() - 1;
    while(l<=r) {
        int mid = l + (r - l) / 2;
        if(k<arr[mid]&&(mid<1||k>=arr[mid-1])) {
            return mid;
        } else if(k<arr[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return arr.size();
}



int main() {
    vector<int> arr = {1, 4, 5, 7, 9, 15, 15, 17, 20, 25};
    auto ind1 = binary_search(arr, 0);
    cout << ind1 << endl;
    auto ind2 = upper_bound(arr, 15);
    cout << ind2 << endl;
    // auto ind3 = lower_bound(arr, 15);
    // vector<int> rotatedArr = {20, 25, 30, 1, 3, 5, 7, 10, 15, 19};
    // auto ind4 = rotated_binary_search(arr, 15);
}