#include <iostream>
#include "myQueue.h"
#include "myVector.h"
#define left 'l'
#define right 'r'

void merge(int arr[], int start, int middle, int end, int old[]){
    int div = middle - start + 1;
    int div2 = end - middle;

    int *oldL = new int[div], *oldR = new int[div2];
    int *arrL = new int[div], *arrR = new int[div2];

    for (int i = 0; i < div; ++i) {
        arrL[i] = arr[start + i];
        oldL[i] = old[start + i];
    }
    for (int i = 0; i < div2; ++i) {
        arrR[i] = arr[middle + 1 + i];
        oldR[i] = old[middle + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < div && j < div2){
        if (arrL[i] >= arrR[j]){
            arr[k] = arrL[i];
            old[k] = oldL[i];
            i++;
        } else {
            arr[k] = arrR[j];
            old[k] = oldR[j];
            j++;
        }
        k++;
    }

    while (i < div){
        arr[k] = arrL[i];
        old[k] = oldL[i];
        i++;
        k++;
    }

    while (j < div2){
        arr[k] = arrR[j];
        old[k] = oldR[j];
        j++;
        k++;
    }
    delete[] arrL;
    delete[] arrR;
    delete[] oldL;
    delete[] oldR;
}

void mergeSort(int arr[], int start, int end, int old[]){
    if(start < end){
        int m = start + (end - start) / 2;
        mergeSort(arr, start, m, old);
        mergeSort(arr, m + 1, end, old);
        merge(arr, start, m, end, old);
    }
}

void bfs(myVector graph[], bool *visited, int start, char* side, bool& result){
    myQueue q;
    q.push(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if (!visited[v]){;
            visited[v] = true;
            for(auto w : graph[v]){
                if (!visited[w]){
                    side[w] = (side[v] == left) ? right : left;
                    q.push(w);
                } else if (side[w] == side[v]){
                    result = false;
                }
            }
        }
    }
}

void greedyColor(myVector graph[], int* colored, bool *neighborColors, int size){
    int count = size;
    int color = 1;
    int highest = 0;
    for (int i = 0; i < size; ++i) {
        neighborColors[i] = false;
        colored[i] = 0;
    }

    for (int i = 1; i < size; ++i) {
        if (count <= 0){
            return;
        }
        if(colored[i] != 0){
            continue;
        }
        for (int j = 0; j <= highest; ++j) {
            neighborColors[j] = false;
        }

        for(auto w : graph[i]){
            if (colored[w] > 0) {
                neighborColors[colored[w]] = true;
                highest = (highest > colored[w]) ? highest : colored[w];
            }
        }
        for (color = 1; color < size; ++color) {
            if (!neighborColors[color]) {
                break;
            }
        }
        colored[i] = color;
        count--;
    }
}

void LFColor(myVector graph[], int* colored, bool *neighborColors, int size, const int old[]){
    int count = size;
    int color = 1;
    int highest = 0;
    for (int i = 0; i < size; ++i) {
        neighborColors[i] = false;
        colored[i] = 0;
    }

    for (int i = 1; i < size; ++i) {
        int l = old[i];
        if (count <= 0){
            return;
        }
        if(colored[l] != 0){
            continue;
        }
        for (int j = 0; j <= highest; ++j) {
            neighborColors[j] = false;
        }

        for(auto w : graph[l]){
            if (colored[w] > 0) {
                neighborColors[colored[w]] = true;
                highest = (highest > colored[w]) ? highest : colored[w];
            }
        }
        for (color = 1; color < size; ++color) {
            if (!neighborColors[color]) {
                break;
            }
        }
        colored[l] = color;
        count--;
    }
}

int main() {
    int k, n, x, y, count;
    bool partiteResult;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &n);
        int size = n+1;
        long long int temp = n;
        long long int total = temp*(temp-1)/2;
        long long int edgesPresent = 0;
        count = 0;
        partiteResult = true;

        int* arr = new int[size];
        char* side = new char[size];
        int * old = new int[size];
        bool *visited = new bool[size];
        auto *graph = new myVector[size];

        for (int j = 1; j < size; ++j) {
            scanf("%d", &x);
            arr[j] = x;
            for (int l = 0; l < x; ++l) {
                scanf("%d", &y);
                graph[j].push_back(y);
            }
        }
        for (int j = 0; j < size; ++j) {
            old[j] = j;
            side[j] = 'n';
            visited[j] = false;
        }
        mergeSort(arr, 1, n, old);
        for (int j = 1; j <= n; ++j) {
            printf("%d ", arr[j]);//ex1
            edgesPresent += arr[j];
        }
        printf("\n");

        for (int l = 1; l <= n; ++l) {
            if (!visited[l]){
                count++;
                side[l] = left;
                bfs(graph, visited, l, side, partiteResult);
            }
        }
        printf("%d\n", count);//ex2

        partiteResult ? printf("T\n") : printf("F\n");

        printf("?\n");//ex4
        printf("?\n");//ex5

        greedyColor(graph, arr, visited, size);
        for (int j = 1; j < size; ++j) {
            printf("%d ", arr[j]);//ex6a
        }
        printf("\n");

        LFColor(graph, arr, visited, size, old);
        for (int j = 1; j < size; ++j) {
            printf("%d ", arr[j]);//ex6b
        }
        printf("\n");
        printf("?\n");//ex6c
        printf("?\n");//ex7

        long long int edgesNeeded = total - (edgesPresent/2);
        printf("%lld\n", edgesNeeded);//ex8

        delete[] graph;
        delete[] arr;
        delete[] visited;
        delete[] side;
        delete[] old;
    }
    return 0;
}