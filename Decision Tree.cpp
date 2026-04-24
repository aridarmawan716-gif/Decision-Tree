#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Struktur untuk merepresentasikan data (Fitur1, Fitur2, Label)
struct DataPoint {
    int fitur1; // Misal: 1 = Punya sayap, 0 = Tidak
    int fitur2; // Misal: 1 = Bisa terbang, 0 = Tidak
    string label; // Klasifikasi: "Burung" atau "Mamalia"
};

// Struktur Node untuk Pohon Keputusan
struct Node {
    string criteria;   // Nama fitur yang digunakan untuk membagi
    int threshold;     // Nilai ambang batas pembagi
    Node* left;        // Jalur jika kondisi salah (0)
    Node* right;       // Jalur jika kondisi benar (1)
    string leafValue;  // Jika node adalah daun, simpan label hasil akhir

    Node() : left(nullptr), right(nullptr), threshold(0) {}
};

// Fungsi sederhana untuk membangun pohon secara manual (Mockup Training)
Node* buildDecisionTree() {
    Node* root = new Node();
    root->criteria = "Punya Sayap?";
    root->threshold = 1;

    // Jalur Kiri: Tidak punya sayap
    root->left = new Node();
    root->left->leafValue = "Mamalia";

    // Jalur Kanan: Punya sayap
    root->right = new Node();
    root->right->criteria = "Bisa Terbang?";
    root->right->threshold = 1;

    // Jalur Kanan dari Punya Sayap
    root->right->right = new Node();
    root->right->right->leafValue = "Burung";

    // Jalur Kiri dari Punya Sayap (Misal: Penguin)
    root->right->left = new Node();
    root->right->left->leafValue = "Burung (Pinguin)";

    return root;
}

// Fungsi untuk melakukan prediksi berdasarkan data input
string predict(Node* node, int f1, int f2) {
    // Jika sudah sampai di daun (leaf), kembalikan hasilnya
    if (!node->leafValue.empty()) {
        return node->leafValue;
    }

    // Logika percabangan
    if (node->criteria == "Punya Sayap?") {
        if (f1 >= node->threshold) return predict(node->right, f1, f2);
        else return predict(node->left, f1, f2);
    } else if (node->criteria == "Bisa Terbang?") {
        if (f2 >= node->threshold) return predict(node->right, f1, f2);
        else return predict(node->left, f1, f2);
    }

    return "Tidak Diketahui";
}

int main() {
    Node* myTree = buildDecisionTree();

    int inputSayap, inputTerbang;
    cout << "--- Prediksi Hewan ---\n";
    cout << "Punya sayap? (1:Ya, 0:Tidak): "; cin >> inputSayap;
    cout << "Bisa terbang? (1:Ya, 0:Tidak): "; cin >> inputTerbang;

    string hasil = predict(myTree, inputSayap, inputTerbang);
    cout << "\nHasil Klasifikasi: " << hasil << endl;

    return 0;
}
