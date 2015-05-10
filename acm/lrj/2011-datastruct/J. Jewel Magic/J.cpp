#include <iostream>
#include <cstdio>
using namespace std;

typedef long long int64;

const int MAX_NODES = 400010;
const int64 MULTI = 2;
const int64 MODULE = 1346985251;
int64 power[MAX_NODES];

class Splay {

	struct Buffer {
		bool reversed;
		Buffer(bool rev = false) {
			reversed = rev;
		}
	};

	struct Node {
		int64 hash[2];
		int val;
		Buffer buffer;
		int size;
		Node *child[2];
		void clear(Node *null_node) {
            hash[0] = hash[1] = val = 0;
			buffer = Buffer();
			size = 0;
			child[0] = child[1] = null_node;
		}
		void clear_buffer() {
			if (child[0]->size > 0) child[0] -> set_buffer(buffer);
			if (child[1]->size > 0) child[1] -> set_buffer(buffer);
			buffer = Buffer();
		}
		void set_buffer(const Buffer &buf) {
			if (buf.reversed) {
				buffer.reversed = !buffer.reversed;
				swap(child[0], child[1]);
				swap(hash[0], hash[1]);
			}
		}
		void update() {
			size = child[0]->size + child[1]->size + 1;
			for (int i = 0; i <= 1; i ++) {
				int64 keyL = child[i]->hash[i], keyR = child[1-i]->hash[i];
				int sizeL = child[i]->size;
				hash[i] = (keyL + val * power[sizeL] + keyR * power[sizeL+1]) % MODULE;
			}
		}
		int get_child(int &index) {
			int tmp_index = index - child[0]->size - 1;
			if (tmp_index < 0) return 0;
			index = tmp_index;
			return (tmp_index == 0 ? -1 : 1);
		}
	} *root, *null_node;
	
	class MemoryManager {
		Node mem[MAX_NODES];
		int index;
	public:
		void initalize() {
			index = 0;
		}
		Node *new_node() {
			return &mem[index ++];
		}
	} memoryManager;
	
	class Stack {
		Node *nodes[MAX_NODES];
		int index[MAX_NODES];
		int top;
        Node *rotate(Node *node, int c) {
            Node *child = node->child[c];
            child -> clear_buffer();
            node->child[c] = child->child[1-c];
            child->child[1-c] = node;
            node -> update();
            return child;
        }
	public:
		void clear(Node *root_node) {
			nodes[top = 1] = root_node;
		}
		void push_child(int c) {
			index[top] = c;
			nodes[top + 1] = nodes[top]->child[c];
			top ++;
		}
		Node *splay_nodes() {
           	while (top >= 3) {
				top -= 2;
				if (index[top] == index[top + 1]) {
                    nodes[top] = rotate(nodes[top], index[top]);
                    nodes[top] = rotate(nodes[top], index[top]);
                } else {
    				nodes[top]->child[index[top]] = rotate(nodes[top]->child[index[top]], index[top + 1]);
	       			nodes[top] = rotate(nodes[top], index[top]);
                }
				nodes[top] -> update();
				if (top >= 2)
					nodes[top-1]->child[index[top-1]] = nodes[top];
			}
			if (top == 2) {
				nodes[1] = rotate(nodes[1], index[1]);
				nodes[1] -> update();
			}
			return nodes[1];
		}
		Node *top_node() {
			return nodes[top];
		}
		Node *popup_top() {
			return nodes[top --];
		}
	} stack;

	Node *splay(Node *root_node, int index) {
      	stack.clear(root_node);
		while (1) {
			stack.top_node() -> clear_buffer();
			int c = stack.top_node() -> get_child(index);
			if (c < 0) break;
			stack.push_child(c);
		}
		Node *result = stack.splay_nodes();
        return result;
	}
	
	Node *merge(Node *node_a, Node *node_b) {
		if (node_a->size == 0)
			return node_b;
		node_a = splay(node_a, node_a->size);
		node_a -> clear_buffer();
		node_a -> child[1] = node_b;
		node_a -> update();
		return node_a;
	}
	
	void split(Node *&node_a, int index, Node *&node_b) {
		if (index == 0) {
			node_b = node_a;
			node_a = null_node;
			return;
		}
		node_a = splay(node_a, index);
		node_a -> clear_buffer();
		node_b = node_a->child[1];
		node_a->child[1] = null_node;
		node_a -> update();
	}
	
public:

	void initalize() {
		memoryManager.initalize();
		root = null_node = memoryManager.new_node();
		null_node -> clear(null_node);
	}
	
	void insert(int index, int val) {
		Node *node = memoryManager.new_node();
		node -> clear(null_node);
		node -> val = val;
		node -> update();
		
		Node *tmp_node;
		split(root, index, tmp_node);
		root = merge(root, node);
		root = merge(root, tmp_node);
	}
	
	void remove(int index) {
		root = splay(root, index);
		root = merge(root->child[0], root->child[1]);
	}
	
	void reverse(int st, int en) {
		Node *node_a, *node_b;
		split(root, en, node_b);
		split(root, st - 1, node_a);
		node_a -> set_buffer(true);
		root = merge(merge(root, node_a), node_b);
	}
	
	int64 get_hash(int index, int len) {
        int64 ans = 0;
        
        root -> clear_buffer();
		if (index == 1) 
			stack.clear(root);
		else {
			root = splay(root, index - 1);
			stack.clear(root);
			stack.push_child(1);
		}
		index = 0;
		while (stack.top_node() != null_node) {
            stack.top_node() -> clear_buffer();
			int size_l = stack.top_node()->child[0]->size;
			if (len <= size_l)
				stack.push_child(0);
			else {
                int64 key1 = stack.top_node()->child[0]->hash[0] * power[index] % MODULE;
                int64 key2 = stack.top_node()->val * power[index + size_l] % MODULE;
                ans = (ans + key1 + key2) % MODULE;
                index += size_l + 1;
                len -= size_l + 1;
				stack.push_child(1);
			}
		}
		stack.popup_top();
		root = stack.splay_nodes();
		return ans;
    }
	
	int query_lcp(int index_a, int index_b) {
        int le = 0, ri = root->size - max(index_a, index_b) + 1;
        while (le < ri) {
            int mid = (le + ri + 1) / 2;
            if (get_hash(index_a, mid) == get_hash(index_b, mid))
                le = mid;
            else
                ri = mid - 1;
        }
        return le;
	}
	
} splay;

bool mainProcedure() {
    int jewels_length;
    int operation_count;
    
    if (scanf("%d%d", &jewels_length, &operation_count) == EOF)
        return false;
    power[0] = 1;
    for (int i = 1; i <= jewels_length + operation_count; i ++)
        power[i] = power[i - 1] * MULTI % MODULE;
    
    splay.initalize();
    for (int i = 0; i < jewels_length; i ++) {
        char c = getchar();
        while (c!='0' && c!='1') c = getchar();
        splay.insert(i, c=='0' ? 0 : 1);
    }
    while (operation_count --) {
        int operation, p1, p2, c;
        scanf("%d", &operation);
        switch (operation) {
            case 1:
                scanf("%d%d", &p1, &c);
                splay.insert(p1, c);
                break;
            case 2:
                scanf("%d", &p1);
                splay.remove(p1);
                break;
            case 3:
                scanf("%d%d", &p1, &p2);
                splay.reverse(p1, p2);
                break;
            case 4:
                scanf("%d%d", &p1, &p2);
                printf("%d\n", splay.query_lcp(p1, p2));
                break;             
        }
    }
    return true;
}

int main() {
    freopen("j.in", "r", stdin);
    freopen("j.out", "w", stdout);
    while (mainProcedure());
    return 0;
}
