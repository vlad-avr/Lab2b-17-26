#include <random>
#include <chrono>
#include <iostream>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int num;
};

Node* create_list(int N) {
    Node* beg = new Node;
    beg->next = NULL;
    beg->prev = NULL;
    beg->num = 1;
    Node* res = beg;
    for (int i = 2; i <= N; i++) {
        Node* temp = new Node;
        temp->num = i;
        temp->prev = beg;
        beg->next = temp;
        beg = beg->next;
    }
    res->prev = beg;
    beg->next = res;
    return res;
}


void show_list(Node ** main) {
    Node* temp = *main;
    cout << temp->num << "\t";
    temp = temp->next;
    while (temp != *main) {
        cout << temp->num << "\t";
        temp = temp->next;
    }
    cout << endl;
}


void delete_node(Node** node) {
    (*node)->next->prev = (*node)->prev;
    (*node)->prev->next = (*node)->next;
    delete *node;
}

int * delete_list(bool is_demo, Node ** beg, int res_size) {
    int* res_list = new int[res_size];
    if (!is_demo) {
        int KK_size;
        cout << "\n Enter size of sequence: ";
        cin >> KK_size;
        int* KK = new int[KK_size];
        int k = 0;
        cout << "\n Enter the sequence: ";
        for (k; k < KK_size; k++) {
            cin >> KK[k];
        }
        k = 0;
        int res_counter = 0;
        Node* temp = *beg;
        while (temp) {
            int KK_el = KK[k];
            for (KK_el; KK_el > 0; KK_el--) {
                temp = temp->next;
            }
            Node* t_temp = temp;
            res_list[res_counter] = temp->num;
            res_counter++;
            temp = temp->next;
            delete_node(&t_temp);
            k++;
            if (k >= KK_size) {
                k = 0;
            }
            if (res_counter >= res_size) {
                break;
            }
        }
        delete KK;
    }
    else {
        int KK_size = rand() % 8 + 1;
        int* KK = new int[KK_size];
        int k = 0;
        for (k; k < KK_size; k++) {
            KK[k] = rand() % 10 + 1;
        }
        k = 0;
        int res_counter = 0;
        Node* temp = *beg;
        while (temp) {
            int KK_el = KK[k];
            for (KK_el; KK_el > 0; KK_el--) {
                temp = temp->next;
            }
            Node* t_temp = temp;
            res_list[res_counter] = temp->num;
            res_counter++;
            temp = temp->next;
            delete_node(&t_temp);
            k++;
            if (k >= KK_size) {
                k = 0;
            }
            if (res_counter >= res_size) {
                break;
            }
        }
        delete KK;
    }
    return res_list;
}

void show_del_seq(int* r_list, int r_size, bool is_demo, bool is_bench) {
    if (!is_demo) {
        cout << "\n Delete sequence:";
        for (int i = 0; i < r_size; i++) {
            cout << "\t" << r_list[i];
        }
        cout << "\n Get position of a number in delete sequence: ";
        int del_num = 1;
        while (del_num != 0) {
            cout << "\n Enter the number (from 1 to " << r_size << ") or enter 0 to exit: ";
            cin >> del_num;
            if (del_num > r_size || del_num <= 0) {
                cout << "\n Invalid number";
            }
            else {
                for (int i = 0; i < r_size; i++) {
                    if (r_list[i] == del_num) {
                        cout << i+1;
                    }
                }
            }
        }
        cout << "\n Get number by its position from the end in delete sequence: ";
        del_num = 0;
        while (del_num != -1) {
            cout << "\n Enter the number (from 0 to " << r_size-1 << ") or enter -1 to exit: ";
            cin >> del_num;
            if (del_num >= r_size || del_num <= -1) {
                cout << "\n Invalid position";
            }
            else {
                del_num++;
                cout << r_list[r_size - del_num];
            }
        }

    }
    else {
        if (!is_bench) {
            cout << "\n Delete sequence:";
            for (int i = 0; i < r_size; i++) {
                cout << "\t" << r_list[i];
            }
        }
        cout << "\n Get position of a number in delete sequence: ";
        int del_num = rand()%(r_size-1) + 1;
        cout << "\n Position of number " << del_num << " : ";
        for (int i = 0; i < r_size; i++) {
            if (r_list[i] == del_num) {
                cout << i + 1;
            }
        }
        cout << "\n Get number by its position from the end in delete sequence: ";
        del_num = rand() % r_size;
        cout << "\n Number in position " << del_num << " : ";
        cout << r_list[r_size - del_num];
    }
}

void demo() {
    cout << "\n Starting Demonstration: ";
    cout << "\n Creating list of random values: ";
    int N = rand() % 50 + 10;
    Node* demo_Node = create_list(N);
    int r_size = demo_Node->prev->num;
    show_list(&demo_Node);
    cout << "\n Deleting list in random sequence: ";
    int* r_list = delete_list(true, &demo_Node, r_size);
    show_del_seq(r_list, r_size, true, false);
}

void benchmark() {
    cout << "\n Starting benchmark: ";
    int N = 10;
    int cur_t = 0;
    while (true) {
        cout << "\n Creating " << N << " random elements ";
        auto t_beg = chrono::high_resolution_clock::now();
        Node* beg = create_list(N);
        auto t_end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << "completed in " << duration.count() << " milliseconds";
        cout << "\n Deleting " << N << " elements: ";
        t_beg = chrono::high_resolution_clock::now();
        int* r_list = delete_list(true, &beg, N);
        t_end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << "completed in " << duration.count() << " milliseconds";
        cout << "\n Searching for random elements: ";
        t_beg = chrono::high_resolution_clock::now();
        show_del_seq(r_list, N, true, true);
        t_end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(t_end - t_beg);
        cur_t += duration.count();
        cout << " completed in " << duration.count() << " milliseconds";
        cout << "\n Benchmark for " << N << " random elements completed in " << cur_t << " milliseconds";
        if (cur_t < 10000) {
            N *= 10;
        }
        else {
            break;
        }
    }
}

int main()
{
    string input;
    while (input != "exit") {
        cout << "\n HELP: \n manual - input data manual; \n demo - start demonstration; \n bench - start benchmarking; \n exit - exit app \n ";
        cin >> input;
        if (input == "manual") {
            int N = 0;
            cout << "\n Enter number of elements: ";
            cin >> N;
            Node* main_Node = create_list(N);
            int r_size = main_Node->prev->num;
            show_list(&main_Node);
            int* res_list = delete_list(false, &main_Node, r_size);
            show_del_seq(res_list, r_size, false, false);
        }
        else if (input == "demo") {
            demo();
        }
        else if (input == "bench") {
            benchmark();
        }
    }
    
}
 
