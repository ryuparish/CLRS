#ifndef HEAP.H
#define HEAP.H

class headNode{

    public:
        headNode(heapNode* parent, int value, heapNode lchild, heapNode rchild);
        headNode(heapNode* parent, int value){
            parent_node = parent;
            node_value = value;
            lchild_node = NULL;
            rchild_node = NULL;
        }

        // Setters and getters for the heap node object
        set_value(int value){node_value = value;}

        int get_value(){return node_value;}

        set_parent(headNode* newparent){parent_node = parent_node;}

        headNode* get_parent(){return parent_node;}

        set_lchild(headNode* newlchild){lchild_node = newlchild;}

        headNode* get_lchild(){return heapNode* lchild_node;}

        set_rchild(headNode* newrchild){rchild_node = newrchild;}

        headNode* get_rchild(){return heapNode* rchild_node;}

    private:

        headNode* parent_node, lchild_node, rchild_node;

        int node_value;

};

#endif
