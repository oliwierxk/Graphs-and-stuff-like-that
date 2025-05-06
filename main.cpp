#include <iostream>
#include "MyString.h"
#include "MyVector.h"
using namespace std;
//zaimplementowana klasa Graph
class Graph {
    long long d;
    MyVector<long long>* list;

    void DFS(long long v, bool* visited) {
        visited[v] = true;
        for (long long i = 0; i < list[v].size(); ++i) {
            long long adj = list[v][i];
            if (!visited[adj]) {
                DFS(adj, visited);
            }
        }
    }



public:
   Graph(long long d) : d(d) {
       list = new MyVector<long long>[d];
   }
    void addEdge(long long x, long long y) {
            list[x].push_back(y);
    }

    long long countComponents() {
        bool* visited = new bool[d];
        for (long long i = 0; i < d; ++i) {
            visited[i] = false;
        }
        long long count = 0;
        for (long long i = 0; i < d; i++) {
            if (!visited[i]) {
                DFS(i, visited);
                count++;
            }
        }
        delete[] visited;
        return count;
    }

    ~Graph() {}
};

using Sign = MyString;
using Characters = MyVector<Sign>;

//oddzielamy "tokeny" w linii pobranej z getline
Characters separateCharacters(const char* infixNotation,long long x, Graph g, long long tablica[], long long& edge)
{
    Characters infix;
    bool firstToken = true;

    do {
        const char* FirstPos = infixNotation;
        while (*infixNotation && *infixNotation != ' ') {
            ++infixNotation;
        }
        size_t size = (infixNotation - FirstPos);
        if (size) {
            MyString sign(FirstPos, size);
            if (firstToken) {
                tablica[x] = MyString::toLongLong(sign);
                firstToken = false;
            } else {
                g.addEdge(x, MyString::toLongLong(sign) - 1);
                edge++;
            }
        }

    } while (*infixNotation++ != '\0');
    return infix;
}

void merge(long long arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    auto* L = new long long[n1];
    auto* R = new long long[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

//merge sort
void mergeSort(long long arr[], int left, long long right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

}
//printowanie posortowanuych degrees merge sortem
void printSortedDegreesArray(long long tablica[], long long size) {
    mergeSort(tablica, 0, size - 1);

    for (int i = 0; i < size; ++i) {
        cout << tablica[i] << " ";
    }
    cout << endl;
}
// printowanie liczby dopełniania edgeow
void printComplementEdges(long long NrofVer, long long edge) {
    long long ComplementEdges;

    ComplementEdges = NrofVer * (NrofVer - 1) - edge;
    ComplementEdges = ComplementEdges / 2;
    cout << ComplementEdges << endl;
}
//funkcja getline zaimplememntowana
std::istream& getline(std::istream& is, MyString& str) {
    char ch;
    int striSize = 250;
    int size = 0;
    char* stri = new char[striSize];
    while (is.get(ch) && ch != '\n') {
        if (size >= striSize - 1) {
            char* newBuffer = new char[2 * striSize];
            std::memcpy(newBuffer, stri, size);
            delete[] stri;
            stri = newBuffer;
            striSize *= 2;
        }
        stri[size++] = ch;
    }
    stri[size] = '\0';
    str.data = stri;
    str.length = size;
    return is;
}

int main() {
    long long nrofGraphs;
    MyString nrGr;
    getline(cin, nrGr);
    nrofGraphs = MyString::toLongLong(nrGr);

    for (long long i = 0; i < nrofGraphs; i++) {
        long long EdgeCount = 0;
        long long NrOfVer;
        MyString NrVer;
        getline(cin, NrVer);
        NrOfVer = MyString::toLongLong(NrVer);
        Graph g(NrOfVer);
        auto* tablica = new long long[NrOfVer];

        for (long long j = 0; j < NrOfVer; j++) {
            MyString line;
            getline(cin, line);
            separateCharacters(line.c_str(), j, g, tablica,EdgeCount);
        }
        printSortedDegreesArray(tablica,NrOfVer); // 1
        cout << g.countComponents() << endl; // 2
        cout << "?" << endl; // 3
        cout << "?" << endl; // 4
        cout << "?" << endl; // 5
        cout << "?" << endl; // 6
        cout << "?" << endl; // 7
        cout << "?" << endl; // 8
        cout << "?" << endl; // 9
        printComplementEdges(NrOfVer,EdgeCount); // 10
        delete[] tablica;

    }

    return 0;
}
