#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Structure to represent a node in the Huffman tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Custom comparison for priority queue (min heap)
struct Compare {
    bool operator()(Node* const& a, Node* const& b) const {
        return a->freq > b->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes for each character
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build the tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* internal = new Node('\0', left->freq + right->freq);
        internal->left = left;
        internal->right = right;

        pq.push(internal);
    }

    return pq.top();
}

// Function to generate Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) return;

    if (root->ch != '\0') {
        codes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    string text;
    cout<<"Enter Text: ";
    cin>>text;

    // Calculate frequencies
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Build Huffman tree
    Node* root = buildHuffmanTree(freq);

    // Generate Huffman codes
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    // Print the codes
    cout << "Huffman Codes:" << endl;
    for (auto pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Encode the text
    string encodedText = "";
    for (char ch : text) {
        encodedText += codes[ch];
    }
    cout << "Encoded text: " << encodedText << endl;

    return 0;
}