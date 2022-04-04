#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

int MAX_ID = 1;

struct Node {
public:
    vector<int> num_vec;
    const int max_size = 10;
    Node* next = NULL;
    Node* prev = NULL;
    int ID = 0;
    void get_vals() {
        int num;
        cout << "\n Enter the number: ";
        cin >> num;
        num_vec.push_back(num);
    }

    void get_rand_vals() {
        num_vec.push_back(rand() % 30 + 1);
    }

    void get_id() {
        ID = MAX_ID;
        MAX_ID++;
    }
};


Node * insert_first(Node** beg, bool is_auto) {
    if ((*beg)->num_vec.size() >= (*beg)->max_size) {
        Node* first = new Node;
        first->next = *beg;
        (*beg)->prev = first;
        *beg = first;
        if (!is_auto) {
            first->get_vals();
        }
        else {
            first->get_rand_vals();
        }
        first->get_id();
        return first;
    }
    else {
        if (!is_auto) {
            if ((*beg)->num_vec.size() == 0) {
                (*beg)->get_vals();
            }
            else {
                vector<int>::iterator iter = (*beg)->num_vec.begin();
                int val;
                cout << "\n Enter value: ";
                cin >> val;
                (*beg)->num_vec.insert(iter, val);
            }
        }
        else {
            if ((*beg)->num_vec.size() == 0) {
                (*beg)->get_rand_vals();
            }
            else {
                vector<int>::iterator iter = (*beg)->num_vec.begin();
                (*beg)->num_vec.insert(iter, rand()%30+1);
            }
        }
        return *beg;
    }
}

void append(Node** beg, bool is_auto) {
    Node* temp = *beg;
    while (temp->next) {
        temp = temp->next;
    }

    if (temp->num_vec.size() < temp->max_size) {
        if (!is_auto) {
            temp->get_vals();
        }
        else {
            temp->get_rand_vals();
        }
    }
    else {
        Node* last = new Node;
        last->prev = temp;
        temp->next = last;
        if (!is_auto) {
            last->get_vals();
        }
        else {
            last->get_rand_vals();
        }
        last->get_id();
    }
}

Node* find_id(Node** beg, int id) {
    Node* temp = *beg;
    while (temp && temp->ID != id) {
        temp = temp->next;
    }
    return temp;
}

void insert(int id, Node ** beg, bool is_auto) {
    Node* temp = find_id(beg, id);
    if (temp) {
        if (temp->num_vec.size() < temp->max_size) {
            if (!is_auto) {
                temp->get_vals();
            }
            else {
                temp->get_rand_vals();
            }
        }
        else {
            Node* new_node = new Node;
            if (temp->next) {
                temp->next->prev = new_node;
            }
            new_node->next = temp->next;
            temp->next = new_node;
            new_node->prev = temp;
           
            new_node->get_id();
            int N = (new_node->max_size) / 2;
            for (int i = N; i < new_node->max_size; i++) {
                new_node->num_vec.push_back(temp->num_vec[N]);
                vector<int>::iterator iter = temp->num_vec.begin() + N;
                temp->num_vec.erase(iter);
            }
            if (!is_auto) {
                new_node->get_vals();
            }
            else {
                new_node->get_rand_vals();
            }
        }
    }
    else {
        cout << "\n ERROR: Invalid ID. Enter a valid ID.";
    }
}

void find_val(int val, Node ** beg, bool is_bench) {
    Node* temp = *beg;
    int t_size;
    while (temp) {
        t_size = temp->num_vec.size();
        for (int i = 0; i < t_size; i++) {
            if (val == temp->num_vec[i] && !is_bench) {
                cout << "\n Element " << val << " is in node " << temp->ID << " in position " << i;
            }
        }
        temp = temp->next;
    }
}

void show_list(Node** beg) {
    Node* temp = *beg;
    int vec_size;
    while (temp) {
        cout << "\n ID: " << temp->ID;
        vec_size = temp->num_vec.size();
        cout << "\n Numbers: ";
        for (int i = 0; i < vec_size; i++) {
            cout << temp->num_vec[i] << " ";
        }
        temp = temp->next;
    }
    cout << "\n ***___________________________________________________***";
}

void show_list_rev(Node ** beg) {
    Node* temp = *beg;
    while (temp->next) {
        temp = temp->next;
    }
    int vec_size;
    while (temp) {
        cout << "\n ID: " << temp->ID;
        vec_size = temp->num_vec.size();
        cout << "\n Numbers: ";
        for (int i = vec_size - 1; i >= 0; i--) {
            cout << temp->num_vec[i] << " ";
        }
        temp = temp->prev;
    }
    cout << "\n ***___________________________________________________***";
}

void n_delete_el(Node** beg, int id, int val) {
    Node* temp = find_id(beg, id);
    if (temp) {
        int v_size = temp->num_vec.size();
        for (int i = 0; i < v_size; i++) {
            if (temp->num_vec[i] == val) {
                vector<int>::iterator iter = temp->num_vec.begin() + i;
                temp->num_vec.erase(iter);
                break;
            }
        }
        if (temp->next) {
            int half_size = (temp->max_size) / 2;
            if (temp->num_vec.size() < half_size) {
                int N = half_size - temp->num_vec.size();
                for (int i = 0; i < N; i++) {
                    temp->num_vec.push_back(temp->next->num_vec[0]);
                    vector<int>::iterator iter = temp->next->num_vec.begin();
                    temp->next->num_vec.erase(iter);
                }
                if (temp->next->num_vec.size() < half_size) {
                    N = temp->next->num_vec.size();
                    for (int i = 0; i < N; i++) {
                        temp->num_vec.push_back(temp->next->num_vec[i]);
                    }
                    temp = temp->next;
                    if (temp->next) {
                        temp->next->prev = temp->prev;
                    }
                    temp->prev->next = temp->next;
                    delete temp;
                }
              
            }
        }
    }
    else {
        cout << "\nERROR: Invalid ID";
    }
}

void delete_all(Node** beg) {
    Node* temp = *beg;
    while (temp) {
        (*beg) = (*beg)->next;
        delete temp;
        temp = *beg;
    }
    MAX_ID = 1;
}

void demo() {
    cout << "\n Starting demonstration: ";
    cout << "\n Create first node with random number of random elements: ";
    Node* beg = new Node;
    int N = rand() % 10 + 1;
    for (int i = 0; i < N; i++) {
        append(&beg, true);
    }
    show_list(&beg);
    cout << "\n Inserting in the head random number of random elements: ";
    N = rand() % 40 + 10;
    for (int i = 0; i < N; i++) {
        insert_first(&beg, true);
    }
    show_list(&beg);
    cout << "\n Inserting in the end random number of random elements: ";
    N = rand() % 40 + 10;
    for (int i = 0; i < N; i++) {
        append(&beg, true);
    }
    show_list(&beg);
    cout << "\n Inserting a random number of random elements into random nodes: ";
    N = rand() % (MAX_ID - 1);
    for (int i = 0; i < N; i++) {
        int N_Node = rand() % (MAX_ID - 1);
        int N_el = rand() % 10 + 1;
        for (int j = 0; j < N_el; j++) {
            insert(N_Node, &beg, true);
        }
    }
    show_list(&beg);
    cout << "\n Searching for random elements: ";
    N = rand() % (MAX_ID - 1);
    for (int i = 0; i < N; i++) {
        int rand_num = rand() % 30 + 1;
        find_val(rand_num, &beg, false);
    }
    cout << "\n Deleting random elements in random nodes: ";
    N = rand() % (MAX_ID - 1);
    for (int i = 0; i < N; i++) {
        int N_Node = rand() % (MAX_ID - 1);
        Node* temp = find_id(&beg, N_Node);
        if (temp) {
            n_delete_el(&beg, N_Node, temp->num_vec[rand() % (temp->num_vec.size())]);
        }
    }
    cout << "\n Final list: ";
    show_list(&beg);
    cout << "\n Final list in reverse order: ";
    show_list_rev(&beg);
    delete_all(&beg);
}

void bench() {
    cout << "\n Starting benchmark: ";
    int N = 10;
    int cur_t = 0;
    while (true) {
        Node* beg = new Node;
        int half_N = N / 2;
        int el_n = half_N * beg->max_size;
        cout << "\n Creating " << half_N << " nodes with " << el_n << " random elements ";
        auto t_beg = chrono::high_resolution_clock::now();
        for (int i = 0; i < el_n; i++) {
            beg = insert_first(&beg, true);
        }
        auto t_end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << "completed in " << duration.count() << " milliseconds";
        cout << "\n Inserting " << half_N << " nodes in random positions with " << el_n << " random elements ";
        t_beg = chrono::high_resolution_clock::now();
        int rand_num;
        for (int i = 0; i < half_N; i++) {
            rand_num = rand() % (MAX_ID - 1);
            for (int j = 0; j < beg->max_size; j++) {
                insert(rand_num, &beg, true);
            }
        }
        t_end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << "completed in " << duration.count() << " milliseconds";
        cout << "\n Searching for " << N <<" random elements ";
        t_beg = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            rand_num = rand() % 30 + 1;
            find_val(rand_num, &beg, true);
        }
        t_end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << " completed in " << duration.count() << " milliseconds";
        cout << "\n Deleting " << N << " random elements ";
        t_beg = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < N; i++) {
            rand_num = rand() % 30 + 1;
            int rand_id = rand() % N;
            n_delete_el(&beg, rand_id, rand_num);
        }
        t_end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << " completed in " << duration.count() << " milliseconds";
        cout << "\n Benchmark for " << N << " random elements completed in " << cur_t << " milliseconds";
        delete_all(&beg);
        MAX_ID = 1;
        if (cur_t < 10000) {
            N *= 10;
        }
        else {
            break;
        }
    }
}

void show_help(bool is_manual) {
    cout << "\n start - enter the data manually;\n demo - start demonstration;\n bench - start benchmarking;\n exit_mode - exit the current app mode;\n exit - exit app\n";
    if (is_manual) {
        cout << "\n IN 'START' MODE: ";
        cout << "\n append - add element in the end;\n first - add element in the front;\n insert - insert element in the node with certain ID;\n show - show the list;\n show_reverse - shoe the list reversed;\n delete - delete element in the node;\n find - find all the elements with certain property\n";
    }
}

int main()
{
    srand(time(NULL));
    
    string input = "";
    while (input != "exit") {
        show_help(false);
        cin >> input;
        if (input == "start") {
            Node* beg = new Node;
            while (input != "exit_mode") {
                show_help(true);
                cin >> input;
                if (input == "append") {
                    append(&beg, false);
                }
                else if (input == "first") {
                    beg = insert_first(&beg, false);
                }
                else if (input == "insert") {
                    int id;
                    cout << "\n Enter ID: ";
                    cin >> id;
                    insert(id, &beg, false);
                }
                else if (input == "find") {
                    int val;
                    cout << "\n Enter value: ";
                    cin >> val;
                    find_val(val, &beg, false);
                }
                else if (input == "delete") {
                    int id, val;
                    cout << "\n Enter ID: ";
                    cin >> id;
                    cout << "\n Enter value: ";
                    cin >> val;
                    n_delete_el(&beg, id, val);
                }
                else if (input == "show") {
                    show_list(&beg);
                }
                else if (input == "show_reverse") {
                    show_list_rev(&beg);
                }
            }
            delete_all(&beg);
        }
        else if (input == "demo") {
            demo();
        }
        else if (input == "bench") {
            bench();
        }
    }

}
