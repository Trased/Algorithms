#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

// Structura pentru un nod în arborele Huffman
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
};

// Functie pentru a elibera memoria ocupata de arborele Huffman
void deleteHuffmanTree(HuffmanNode* root) {
    if (root == nullptr)
        return;

    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

// Comparator pentru coada de prioritati
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Functie pentru a construi arborele Huffman
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Crearea nodurilor pentru fiecare caracter si adaugarea lor in coada de prioritati
    for (const auto& pair : frequencies) {
        char data = pair.first;
        int frequency = pair.second;
        pq.push(new HuffmanNode(data, frequency));
    }

    // Construirea arborelui Huffman
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();

        HuffmanNode* right = pq.top();
        pq.pop();

        int sumFrequency = left->frequency + right->frequency;
        HuffmanNode* newNode = new HuffmanNode('\0', sumFrequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Functie pentru a construi tabela de codificare Huffman
void buildHuffmanCodes(HuffmanNode* root, string currentCode, unordered_map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->data != '\0')
        codes[root->data] = currentCode;

    buildHuffmanCodes(root->left, currentCode + '0', codes);
    buildHuffmanCodes(root->right, currentCode + '1', codes);
}

// Functie pentru a codifica un text folosind tabela de coduri Huffman
string encodeText(const string& text, const unordered_map<char, string>& codes) {
    string encodedText = "";

    for (char c : text)
        encodedText += codes.at(c);

    return encodedText;
}

// Functie pentru a decodifica un text codificat folosind arborele Huffman
string decodeText(const string& encodedText, HuffmanNode* root) {
    string decodedText = "";
    HuffmanNode* currentNode = root;

    for (char c : encodedText) {
        if (c == '0')
            currentNode = currentNode->left;
        else if (c == '1')
            currentNode = currentNode->right;

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decodedText += currentNode->data;
            currentNode = root;
        }
    }

    return decodedText;
}

int main() {
    string text = "Ana are mere!";
    unordered_map<char, int> frequencies;

    // Calcularea frecventei fiecarui caracter din text
    for (char c : text)
        frequencies[c]++;

    // Construirea arborelui Huffman
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Construirea tabela de coduri Huffman
    unordered_map<char, string> codes;
    buildHuffmanCodes(root, "", codes);

    // Codificarea textului
    string encodedText = encodeText(text, codes);
    cout << "Textul codificat: " << encodedText << endl;

    // Decodificarea textului
    string decodedText = decodeText(encodedText, root);
    cout << "Textul decodificat: " << decodedText << endl;

    // Eliberarea memoriei ocupate de arborele Huffman
    deleteHuffmanTree(root);

    return 0;
}
