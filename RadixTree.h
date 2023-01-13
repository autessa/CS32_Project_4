//dummy radix tree
//#ifndef RadixTree_h
//#define RadixTree_h
//#include <string>
//#include <map>
//using namespace std;
//
//template <typename ValueType>
//class RadixTree {
//public:
//    RadixTree() {};
//    ~RadixTree() {};
//    void insert(string key, const ValueType& value) {radixMap[key] = value;}
//    ValueType* search(string key) const {
//        auto vt = radixMap.find(key);
//        if (vt != radixMap.end())
//            return const_cast<ValueType*>(&(vt->second));
//        else
//            return nullptr; }
//private:
//    map<string, ValueType> radixMap;
//};
//
//#endif /* RadixTree_hpp */


#ifndef RadixTree_h
#define RadixTree_h
#include <string>
#include <vector>
#include <iostream>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() {}
    ~RadixTree() {
        for (auto p : delPtrs) {
            delete p->val;
            delete p;
        }
        delPtrs.clear();
    }
    
    void insert(string key, const ValueType& value) {
        ValueType* valuecpy = new ValueType(value);
        insertHelper(key, valuecpy, &root);
    }

    ValueType* search(string key) const {
        return searchHelper(key, &root);
    }

private:
    struct treeNode {
        ValueType* val;
        treeNode* edges[128];
        string partial_string;

        treeNode(string word, ValueType* value = nullptr) {
            partial_string = word;
            val = value;
            for (int i = 0; i < 128; i++)
                edges[i] = nullptr;
        }
    };
    treeNode root{""};
    vector<treeNode*> delPtrs;

    ValueType* searchHelper(string key, const treeNode* p) const{
        //base case, means the key was found in the tree
        if (key.length() == 0)
            return p->val;
        //check for location of first character in key
        
        int loc = key[0] - '0';
        
        //caveat mentioned in report
        if (key[0] == '-')
            loc = 45;
        //if that spot in the edges array is null, word not found, return false
        if (p->edges[loc] == nullptr)
            return nullptr;
        //there is a pointer in that slot
        else {
            //set the node pointer to the pointer in that array slot
            p = p->edges[loc];
            //set the minimum length for a for loop to either the partial string or key length
            auto len = p->partial_string.length();
            if (key.length() < len)
                return nullptr;

            for (int i = 0; i < len; i++) {
                if (key[i] != p->partial_string[i])
                    return nullptr;
            }
            //set key to be substring
            string subKey = key.substr(len);
            //recursively call function
            return searchHelper(subKey, p);
        }
    }

    void insertHelper(string key, ValueType* value, treeNode* p) {
        auto len = p->partial_string.length();
        int i;
        string key1, key2, key3;
        int loc2, loc3;

        if (key == p->partial_string) {
            p->val = value;
            return;
        }

        if (key.length() < len) {
            for (i = 0; i < key.length(); i++)
                if (key[i] != p->partial_string[i]) {
                    //split the partial string into two nodes (matching prefix and non matching prefix)
                    key1 = p->partial_string.substr(0, i);
                    key2 = p->partial_string.substr(i);
                    treeNode* n = new treeNode(key2, p->val);
                    for (int j = 0; j < 128; j++)
                        //make sure to copy edges to new node
                        n->edges[j] = p->edges[j];
                    p->partial_string = key1;
                    p->val = nullptr;
                    //create new node which is left over of nonmatching prefix of the word
                    key3 = key.substr(i);
                    treeNode* t = new treeNode(key3, value);
                    //make sure add nodes to vector for deletion
                    delPtrs.push_back(n);
                    delPtrs.push_back(t);
                    for (int j = 0; j < 128; j++)
                        p->edges[j] = nullptr;
                    loc2 = key2[0] - '0';
                    loc3 = key3[0] - '0';
                    //for caveat described in report
                    if (key2[0] == '-')
                        loc2 = 45;
                    if (key3[0] == '-')
                        loc3 = 45;
                    p->edges[loc2] = n;
                    p->edges[loc3] = t;
                    return;
                }
            //if here means no mismatch and key is less than partial_string so only have to split partial_string using same idea as above
            key1 = p->partial_string.substr(0, i);
            key2 = p->partial_string.substr(i);
            treeNode* n = new treeNode(key2, p->val);
            for (int j = 0; j < 128; j++)
                n->edges[j] = p->edges[i];
            p->partial_string = key1;
            p->val = value;
            delPtrs.push_back(n);
            for (int j = 0; j < 128; j++)
                p->edges[j] = nullptr;
            int loc = key2[0] - '0';
            if (key2[0] == '-')
                loc = 45;
            p->edges[loc] = n;
            return;
            //for code above^^ set val ptr to value, create new node with rest of partial string (make sure to move its value) - I did this in the for loop
            //if (key.length == len) just insert value
        }
        else if (key.length() >= len) {
            for (i = 0; i < len; i++)
                if (key[i] != p->partial_string[i]) {
                    //split partial string, and create 2 new nodes, same as above if statement
                    key1 = p->partial_string.substr(0, i);
                    key2 = p->partial_string.substr(i);
                    treeNode* n = new treeNode(key2, p->val);
                    for (int j = 0; j < 128; j++)
                        n->edges[j] = p->edges[j];
                    p->partial_string = key1;
                    p->val = nullptr;
                    key3 = key.substr(i);
                    treeNode* t = new treeNode(key3, value);
                    delPtrs.push_back(n);
                    delPtrs.push_back(t);
                    for (int j = 0; j < 128; j++)
                        p->edges[j] = nullptr;
                    loc2 = key2[0] - '0';
                    loc3 = key3[0] - '0';
                    if (key2[0] == '-')
                        loc2 = 45;
                    if (key3[0] == '-')
                        loc3 = 45;
                    p->edges[loc2] = n;
                    p->edges[loc3] = t;
                    return;
                }
            //check array of pointers for null ptr, if so create new node else
            key3 = key.substr(i);
            int loc = key3[0] - '0';
            if (key3[0] == '-')
                loc = 45;
            if (p->edges[loc] == nullptr) {
                treeNode* n = new treeNode(key3, value);
                delPtrs.push_back(n);
                p->edges[loc] = n;
                return;
            }
            else {
                //recursive call on next node
                return insertHelper(key3, value, p->edges[loc]);
            }
        }
    }
};


#endif /* RadixTree_hpp */
