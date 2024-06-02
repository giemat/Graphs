#include <iostream>
#include "myQueue.h"
#include "myVector.h"
#include "arrQueue.h"

#define left 'l'
#define right 'r'
#define true 1
#define false 0

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

void bfs(myVector graph[], int *visited, int size, int start, char* side, int& result, int* component){
    arrQueue q(size);
    q.push(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if (!visited[v]){;
            component[start]++;
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

void coloring(myVector graph[], int* colored, int *neighborColors, int size, const int old[], bool lf){
    int count = size;
    int color = 1;
    int highest = 0;
    int l = 1;
    for (int i = 0; i < size; ++i) {
        neighborColors[i] = false;
        colored[i] = 0;
    }

    for (int i = 1; i < size; ++i) {
        if(lf){
            l = old[i];
        } else{
            l = i;
        }
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

void eccentricity(myVector graph[], int i, int size, int *distance, int *tempArr, const int* component){
    if(graph[i].empty()){
        tempArr[i] = 0;
        return;
    }else if(component[i] == 2){
        tempArr[i] = 1;
        return;
    }
    for (int l = 1; l < size; ++l) {
        distance[l] = -1;
    }
    arrQueue q(size);
    q.push(i);
    distance[i] = 0;

    int vertices = 1;
    while (!q.empty()){
        int vertex = q.front();
        if (component[i] <= vertices && component[i] != 0){
            break;
        }
        q.pop();
        for (auto neighbor : graph[vertex]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[vertex] + 1;
                tempArr[i] = (tempArr[i] > distance[neighbor]) ? tempArr[i] : distance[neighbor];
                q.push(neighbor);
                vertices++;
            }
        }
    }
}

int main() {
    int k, n, x, y;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &n);
        int size = n+1;
        long long int temp = n;
        long long int total = temp*(temp-1)/2;
        long long int edgesPresent = 0;
        int count = 0;
        int partiteResult = true;

        int* arr = new int[size];
        char* side = new char[size];
        int * old = new int[size];
        int *visited = new int[size];
        auto *graph = new myVector[size];
        int *tempArr = new int[size];
        int *component = new int[size];

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
            tempArr[j] = 0;
            component[j] = 0;
        }
        mergeSort(arr, 1, n, old);
        for (int j = 1; j < size; ++j) {
            printf("%d ", arr[j]);//ex1
            edgesPresent += arr[j];
        }
        printf("\n");

        for (int l = 1; l < size; ++l) {
            if (!visited[l]){
                count++;
                side[l] = left;
                bfs(graph, visited, size, l, side, partiteResult, component);
            }
            for (auto w : graph[l]){
                if (component[l] >= component[w]){
                    component[w] = component[l];
                } else {
                    component[l] = component[w];
                }
            }
        }
        printf("%d\n", count);//ex2

        partiteResult ? printf("T\n") : printf("F\n");//ex3

        for (int j = 0; j < size; ++j) {
            eccentricity(graph, j, size, visited, tempArr, component);
        }
        for (int j = 1; j < size; ++j) {
            printf("%d ", tempArr[j]);//ex4
        }
        printf("\n");

        //printf("?\n");//ex4
        printf("?\n");//ex5

        coloring(graph, arr, visited, size, old, false);
        for (int j = 1; j < size; ++j) {
            printf("%d ", arr[j]);//ex6a
        }
        printf("\n");

        coloring(graph, arr, visited, size, old, true);
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
        delete[] tempArr;
        delete[] component;
    }
    return 0;
}