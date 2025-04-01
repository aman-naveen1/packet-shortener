#include <iostream>
#include <cstring>
using namespace std;

// Structure to represent a network packet
struct Packet {
    int id;
    char data[50];
    Packet* next; // Pointer for linked list
};

// Linked List to store incoming packets
class PacketQueue {
public:
    Packet* head;
    
    PacketQueue() { head = nullptr; }

    void addPacket(int id, const char* data) {
        Packet* newPacket = new Packet();
        newPacket->id = id;
        strcpy(newPacket->data, data);
        newPacket->next = head;
        head = newPacket;
    }

    void processPackets() {
        Packet* temp = head;
        while (temp) {
            cout << "Processing Packet ID: " << temp->id << ", Data: " << temp->data << endl;
            temp = temp->next;
        }
    }
};

// Binary Tree for packet categorization
struct TreeNode {
    int packetID;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int id) : packetID(id), left(nullptr), right(nullptr) {}
};

// Binary Search Tree (BST) for fast packet retrieval
class PacketTree {
public:
    TreeNode* root;
    
    PacketTree() { root = nullptr; }

    void insert(TreeNode*& root, int packetID) {
        if (!root) {
            root = new TreeNode(packetID);
            return;
        }
        if (packetID < root->packetID)
            insert(root->left, packetID);
        else
            insert(root->right, packetID);
    }

    void addPacket(int packetID) {
        insert(root, packetID);
    }
};

int main() {
    PacketQueue pq;
    pq.addPacket(1, "Hello World");
    pq.addPacket(2, "Satellite Data");
    pq.processPackets();

    PacketTree pt;
    pt.addPacket(5);
    pt.addPacket(2);
    pt.addPacket(8);

    cout << "Packet Tree created successfully!" << endl;
    
    return 0;
}
