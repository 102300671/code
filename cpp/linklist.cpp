#include <iostream>
#define ElemType int
#define OK 1
#define ERROR 0
using namespace std;
typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *LinkList;
int InitList(LinkList &L) {
    L = new LNode;
    L->next = NULL;
    return OK;
}
int ListInsert(LinkList &L, int i, ElemType e) {
    if (i < 1)
        return ERROR;
    LNode *p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p)
        return ERROR;
    LNode *s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
int ListDelete(LinkList &L, int i, ElemType &e) {
    if (i < 1)
        return ERROR;
    LNode *p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next))
        return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
    return OK;
}
int GetElem(LinkList L, int i, ElemType &e) {
    if (i < 1)
        return ERROR;
    LNode *p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p)
        return ERROR;
    e = p->data;
    return OK;
}
int LocateElem(LinkList L, ElemType e) {
    LNode *p = L->next;
    int i = 1;
    while (p) {
        if (p->data == e)
            return i;
        p = p->next;
        i++;
    }
    return 0;
}
int main() {
    LinkList L;
    InitList(L);
    while (1) {
        cout << "1.插入元素" << endl;
        cout << "2.删除元素" << endl;
        cout << "3.查找元素" << endl;
        cout << "4.查找位置" << endl;
        cout << "5.退出" << endl;
        int op;
        cin >> op;
        if (op == 1) {
            cout << "请输入插入位置和元素值" << endl;
            int i, e;
            cin >> i >> e;
            ListInsert(L, i, e);
        } else if (op == 2) {
            cout << "请输入删除位置" << endl;
            int i, e;
            cin >> i;
            ListDelete(L, i, e);
            cout << "删除元素为" << e << endl;
        } else if (op == 3) {
            cout << "请输入查找位置" << endl;
            int i, e;
            cin >> i;
            GetElem(L, i, e);
            cout << "查找元素为" << e << endl;
        } else if (op == 4) {
            cout << "请输入查找元素" << endl;
            int e;
            cin >> e;
            int i = LocateElem(L, e);
            cout << "查找位置为" << i << endl;
        } else if (op == 5) {
            break;
        }
    }
    return 0;
}