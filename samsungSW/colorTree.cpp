#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;


class Node {
public:
    int mid;
    int pid;
    int color;
    int max_depth;

    int cur_depth = 0;
    Node* parent = nullptr;
    vector<Node*> child;
    int value;
};

vector<Node*> tree;
vector<Node*> rootNodes;

bool update_depth(Node* node, int depth, int value) {
    bool inMaxDepth = true;

    if (depth <= node->max_depth) {
        inMaxDepth = true;
    }
    else {
        return false;
    }

    if (node->pid == -1) {
        if (depth > node->cur_depth) {
            node->cur_depth = depth;
        }
        node->value = node->value | value;

        return true;
    }

    bool res = update_depth(node->parent, depth + 1, value | node->value);
    if (res) {
        if (depth > node->cur_depth) {
            node->cur_depth = depth;
        }
        node->value = node->value | value;
    }
    else {
        return false;
    }

    return true;
}

Node* get_parent(Node* node) {
    Node* parent = nullptr;
    if (node->pid == -1) return nullptr;

    for (Node* tnode : tree) {
        if (tnode->mid == node->pid) {
            parent = tnode;
            break;
        }
    }

    return parent;
}

void add_node(int mid, int pid, int color, int max_depth) {
    Node* node = new Node{ mid, pid, 1 << (color - 1), max_depth };
    Node* parent = get_parent(node);
    node->parent = parent;

    bool res = update_depth(node, 1, 1 << (color - 1));
    if (res) {
        if (node->pid == -1) rootNodes.push_back(node);
        else {
            parent->child.push_back(node);
        }
        tree.push_back(node);
    }
}

Node* get_node_by_mid(int mid) {
    for (Node* node : tree) {
        if (node->mid == mid) return node;
    }

    return nullptr;
}

int change_color_internal(Node* node, int color) {
    node->color = color;
    int res = 0;
    for (Node* child : node->child) {
        res |= change_color_internal(child, color);
    }

    node->value = res | node->color;

    return node->value;
}

void change_upper_value(Node* node, int value) {
    if (node->pid == -1) return;

    Node* parent = node->parent;
    int childValue = 0;
    for (Node* child : parent->child) {
        if (child == node) continue;
        childValue |= child->value;
    }
    parent->value = parent->color | value | childValue;

    change_upper_value(parent, parent->value);
}

void change_color(int mid, int color) {
    Node* node = get_node_by_mid(mid);
    if (node == nullptr) return;
    int sValue = node->value;
    int nValue = change_color_internal(node, 1 << (color - 1));

    if (sValue != nValue) {
        change_upper_value(node, nValue);
    }
}

int get_color(int mid) {
    int res = -1;
    for (Node* node : tree) {
        if (node->mid == mid) {
            switch(node->color) {
            case 1:
                res = 1;
                break;
            case 2:
                res = 2;
                break;
            case 4:
                res = 3;
                break;
            case 8:
                res = 4;
                break;
            case 16:
                res = 5;
                break;
            }
            return res;
        }
    }

    return res;
}

int get_value() {
    int res = 0;
    for (Node* node : tree) {
        int value = node->value;
        int decodeValue = 0;
        while (value > 0) {
            if (value & 1) decodeValue += 1;
            value = value >> 1;
        }

        res += decodeValue * decodeValue;
    }

    return res;
}

int main() {
    int n;
    cin >> n;
    int resColor, res;

    while (n--) {
        int cmd, mid, pid, color, max_depth;
        cin >> cmd;
        switch (cmd) {
        case 100:
            cin >> mid >> pid >> color >> max_depth;
            add_node(mid, pid, color, max_depth);
            break;
        case 200:
            cin >> mid >> color;
            change_color(mid, color);
            break;
        case 300:
            cin >> mid;
            resColor = get_color(mid);
            cout << resColor << endl;
            break;
        case 400:
            res = get_value();
            cout << res << endl;
            break;
        }
    }

    return 0;
}
