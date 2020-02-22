//Nama : Muhammad Zunan Alfikri
//NIM  : 16518019
//Kelas : K-01

#include<iostream>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<time.h>
using namespace std;

//type bentukan point
struct Point {
    int x;
    int y;
};

// fungsi untuk membuat point
Point MakePoint(int x, int y){
    Point P;
    P.x = x;
    P.y = y;
    return P;
}

//type bentukan pair point
struct PairPoint{
    Point P1;
    Point P2;
};

//fungsi untuk membuat pair point
PairPoint MakePairPoint(Point P1, Point P2){
    PairPoint P;
    P.P1 = P1;
    P.P2 = P2;
    return P;
}

//fungsi mengembalikan true jika point P ada di arr
bool IsMember (vector<Point> arr, Point P){
    bool found = false;
    int i = 0;
    while (!found && i<arr.size()){
        if (arr[i].x == P.x && arr[i].y == P.y){
            found = true;
        } else {
            i++;
        }
    }
    return found;
}

//fungsi mengembalikan index tempat point P ditemukan, asumsi point P selalu ada
int SearchPair (vector<PairPoint> arr, Point P){
    for (int i = 0 ; i < arr.size() ; i++){
        if ((arr[i].P1.x == P.x && arr[i].P1.y == P.y) || (arr[i].P2.x == P.x && arr[i].P2.y == P.y)){
            return i;
        }
    }
}

int main(){
    vector<Point> arr;                          // array untuk menampung point random
    vector<Point> result;                       // array hasil
    vector<PairPoint> pair;                     // array yang menampung pasangan titik yang membentuk convex hull
    int max_point;
    int i, j,k, a, b, c, count_pos, count_neg, x, y, max_range;
    max_range = 1000;
    
    
    cout << "Masukkan banyaknya titik : ";

    cin >> max_point;                       //Meminta masukan berapa titik yang akan di random
    srand(time(0));
    for (i = 1 ; i <= max_point ; i++){     // loop untuk menginisiasi titik secara random
        x = rand() % max_range;          
        y = rand() % max_range;             
        Point temp;
        temp = MakePoint(x, y);
        arr.push_back(temp);
    }
    

    cout << endl << "Daftar Point : " << endl ;      // Menampilkan seluruh point mula mula
    for (i = 0 ; i < max_point ; i++){
        cout << arr[i].x << " , " << arr[i].y << endl;
    }

    const clock_t begin_time = clock();
    // Mencari Pasangan titik yang membentuk convex hull dan di masukkan ke array pair
    for (i = 0 ; i < max_point-1 ; i++){
        for ( j = i+1 ; j < max_point ; j++){
            a = arr[j].y - arr[i].y;
            b = arr[i].x - arr[j].x;
            c = arr[i].x * arr[j].y - arr[i].y * arr[j].x;
            count_pos = 0;
            count_neg = 0;
            for (k = 0 ; k < max_point ; k++){
                if (a*arr[k].x + b*arr[k].y >= c){
                    count_pos++;
                }
                if (a*arr[k].x + b*arr[k].y <= c ){
                    count_neg++;
                }
            }
            if (count_pos == max_point || count_neg == max_point){
                pair.push_back(MakePairPoint(arr[i], arr[j]));
            }
        }
    }
    
    // Dari Pair , diurutkan agar convex hull terbentuk secara melingkar dan di hasilkan array result yang berisi jawaban
    Point current;
    int idx;
    result.push_back(pair[0].P1);
    result.push_back(pair[0].P2);
    current = MakePoint(pair[0].P2.x, pair[0].P2.y);
    pair.erase(pair.begin() + 0);
    while (pair.size() != 0){
        idx = SearchPair(pair, current);
        if (pair[idx].P1.x == current.x && pair[idx].P1.y == current.y){
            result.push_back(pair[idx].P2);
            current = MakePoint(pair[idx].P2.x, pair[idx].P2.y);
        } else {
            result.push_back(pair[idx].P1);
            current = MakePoint(pair[idx].P1.x, pair[idx].P1.y);
        }
        pair.erase(pair.begin() + idx);
    }

    cout << endl << "Waktu yang diperlukan algoritma tersebut : ";
    cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

    // Menampilkan titik titik hasil dari convex hull
    cout << endl << "Hasil convex hull :";
    cout << "[";
    for (i = 0 ; i < result.size() ; i++){
        cout << " (" << result[i].x << "," << result[i].y << ")";
    }
    cout << " ]";

    return 0;
}