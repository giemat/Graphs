#include <iostream>
#include "myQueue.h"
#include "myVector.h"

using namespace std;

void merge(int arr[], int start, int middle, int end){
    int div = middle - start + 1;
    int div2 = end - middle;

    int *arrL = new int[div], *arrR = new int[div2];

    for (int i = 0; i < div; ++i) {
        arrL[i] = arr[start + i];
    }
    for (int i = 0; i < div2; ++i) {
        arrR[i] = arr[middle + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < div && j < div2){
        if (arrL[i] >= arrR[j]){
            arr[k] = arrL[i];
            i++;
        } else {
            arr[k] = arrR[j];
            j++;
        }
        k++;
    }

    while (i < div){
        arr[k] = arrL[i];
        i++;
        k++;
    }

    while (j < div2){
        arr[k] = arrR[j];
        j++;
        k++;
    }
    delete[] arrL;
    delete[] arrR;
}

void mergeSort(int arr[], int start, int end){
    if(start < end){
        int m = start + (end - start) / 2;
        mergeSort(arr, start, m);
        mergeSort(arr, m + 1, end);
        merge(arr, start, m, end);
    }
}

void bfs(myVector graph[], bool *visited, int start){
    myQueue q;
    q.push(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if (!visited[v]){
            visited[v] = true;
            for(auto w : graph[v]){
                if (!visited[w]){
                    q.push(w);
                }
            }
        }
    }
}

bool isBiPartite(myVector graph[], char* side, int size){
    for (int i = 1; i < size; ++i) {
        myQueue q;
        q.push(i);
        if (side[i] != 'n'){
            continue;
        }
        side[i] = 'l';
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto w : graph[v]){
                if (side[w] == 'n'){
                    side[w] = (side[v] == 'l') ? 'r' : 'l';
                    q.push(w);
                } else if (side[w] == side[v]){
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int k, n, x, y;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> n;
        int size = n+1;
        int* arr = new int[size];
        char* side = new char[size];
        for (int j = 0; j < size; ++j) {
            side[j] = 'n';
        }
        int total = n*(n-1)/2;
        int edgesPresent = 0;
        auto *graph = new myVector[size];
        for (int j = 1; j <= n; ++j) {
            cin >> x;
            arr[j] = x;
            for (int l = 0; l < x; ++l) {
                cin >> y;
                graph[j].push_back(y);
            }
        }
        mergeSort(arr, 1, n);
        for (int j = 1; j <= n; ++j) {
            cout << arr[j] << " ";//ex1
            edgesPresent += arr[j];
            arr[j] = 0;
        }
        cout << endl;
        int count = 0;
        bool *visited = new bool[size];
        for (int i = 1; i <= n; ++i) {
            visited[i] = false;
        }

        for (int i = 1; i <= n; ++i) {
            if (!visited[i]){
                count++;
                bfs(graph, visited, i);
            }
        }
        cout << count << endl;//ex2
        if (!isBiPartite(graph, side, size)){
            cout << "F" << endl;
        } else {
            cout << "T" << endl;
        }
        //cout << "?" << endl;//ex1
        //cout << "?" << endl;//ex2
        //cout << "?" << endl;//ex3
        cout << "?" << endl;//ex4
        cout << "?" << endl;//ex5
        cout << "?" << endl;//ex6a
        cout << "?" << endl;//ex6b
        cout << "?" << endl;//ex6c
        cout << "?" << endl;//ex7
        //cout << "?" << endl;//ex8

        if(edgesPresent % 2 == 1){
            edgesPresent++;
        }
        int edgesNeeded = total - (edgesPresent/2);
        cout << edgesNeeded << endl;//ex8
        delete[] graph;
        delete[] arr;
        delete[] visited;
    }
    return 0;
}