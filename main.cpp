#include <iostream>
#include "myQueue.h"
#include "myVector.h"
#define left 'l'
#define right 'r'
#define none 'n'

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

bool isBiPartite(myVector graph[], char* side,int size){
    for (int i = 1; i < size; ++i) {
        myQueue q;
        q.push(i);
        if (side[i] != none){
            continue;
        }
        side[i] = left;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto w : graph[v]){
                if (side[w] == none){
                    side[w] = (side[v] == left) ? right : left;
                    q.push(w);
                } else if (side[w] == side[v]){
                    return false;
                }
            }
        }
    }
    return true;
}

void isColored(myVector graph[], int* colored, bool *neighborColors, int size){
    int count = size;
    for (int i = 1; i < size; ++i) {
        if (count <= 0){
            return;
        }
        if(colored[i] != 0){
            continue;
        }
        for (int j = 0; j < size; ++j) {
            neighborColors[j] = false;
        }
        for(auto w : graph[i]){
            if (colored[w] > 0) {
                neighborColors[colored[w]] = true;
            }
        }
        int color;
        for (color = 1; color < size; ++color) {
            if (!neighborColors[color]) {
                break;
            }
        }
        colored[i] = color;
        count--;
    }
}

int main() {
    int k, n, x, y;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &n);
        int size = n+1;
        int* arr = new int[size];
        char* side = new char[size];
        for (int j = 0; j < size; ++j) {
            side[j] = 'n';
        }
        long long int temp = n;
        long long int total = temp*(temp-1)/2;
        long long int edgesPresent = 0;
        auto *graph = new myVector[size];
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &x);
            arr[j] = x;
            for (int l = 0; l < x; ++l) {
                scanf("%d", &y);
                graph[j].push_back(y);
            }
        }
        mergeSort(arr, 1, n);
        for (int j = 1; j <= n; ++j) {
            printf("%d ", arr[j]);//ex1
            edgesPresent += arr[j];
            arr[j] = 0;
        }
        printf("\n");
        int count = 0;
        bool *visited = new bool[size];
        int *colored = new int[size];
        for (int l = 1; l <= n; ++l) {
            visited[l] = false;
            colored[l] = 0;
        }

        for (int l = 1; l <= n; ++l) {
            if (!visited[l]){
                count++;
                bfs(graph, visited, l);
            }
        }
        printf("%d\n", count);//ex2
        if (!isBiPartite(graph, side, size)){//ex3
            printf("F\n");
        } else {
            printf("T\n");
        }
//        printf("?\n");//ex1
//        printf("?\n");//ex2
//        printf("?\n");//ex3
        printf("?\n");//ex4
        printf("?\n");//ex5
//        printf("?\n");//ex6a
        isColored(graph, colored, visited, size);
        for (int j = 1; j < size; ++j) {
            printf("%d ", colored[j]);//ex6a
            colored[j] = 0;
        }
        printf("\n");

        printf("?\n");//ex6b
        printf("?\n");//ex6c
        printf("?\n");//ex7
//        printf("?\n");//ex8

        long long int edgesNeeded = total - (edgesPresent/2);
        printf("%lld\n", edgesNeeded);//ex8
        delete[] graph;
        delete[] arr;
        delete[] visited;
        delete[] colored;
        delete[] side;
    }
    return 0;
}